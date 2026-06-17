#!/usr/bin/env node

import { copyFile, mkdir, readdir, readFile, rm, stat, writeFile } from "node:fs/promises"
import crypto from "node:crypto"
import path from "node:path"
import process from "node:process"
import YAML from "yaml"

const repoRoot = process.cwd()
const args = parseArgs(process.argv.slice(2))
const vaultRoot = path.resolve(args.vault ?? process.env.OBSIDIAN_VAULT ?? "")
const contentRoot = path.resolve(args.out ?? "content/notes/public")
const assetRoot = path.resolve(args.assets ?? "content/assets")
const reportPath = path.resolve(args.report ?? "sync-report.json")
const dryRun = Boolean(args["dry-run"])

const allowedTopLevel = new Set(["data-center", "手记"])
const hardIgnoredTopLevel = new Set([".agents", ".git", ".obsidian", ".trash", "node_modules"])
const forbiddenTopLevel = new Set([...hardIgnoredTopLevel, "execution-system", "system"])
const requiredFrontmatter = ["title", "date", "tags"]

const supportedAssetExtensions = new Set([
  ".avif",
  ".gif",
  ".jpeg",
  ".jpg",
  ".mp4",
  ".pdf",
  ".png",
  ".svg",
  ".webp",
])

const report = {
  generatedAt: new Date().toISOString(),
  dryRun,
  vaultRoot,
  contentRoot: path.relative(repoRoot, contentRoot),
  assetRoot: path.relative(repoRoot, assetRoot),
  copiedNotes: [],
  copiedAssets: [],
  skippedNotes: 0,
  failures: [],
  warnings: [],
}

if (!args.vault && !process.env.OBSIDIAN_VAULT) {
  console.error("Usage: npm run sync:content -- --vault /path/to/Obsidian")
  process.exit(2)
}

if (!(await exists(vaultRoot))) {
  console.error(`Vault path does not exist: ${vaultRoot}`)
  process.exit(2)
}

const allFiles = await walk(vaultRoot)
const markdownFiles = allFiles.filter((file) => file.endsWith(".md"))
const markdownRecords = await Promise.all(
  markdownFiles.map(async (file) => {
    const sourceText = await readFile(file, "utf8")
    return {
      sourcePath: file,
      sourceText,
      relative: path.relative(vaultRoot, file),
      frontmatter: parseFrontmatter(sourceText),
    }
  }),
)

const assetFiles = allFiles.filter((file) => {
  const relative = path.relative(vaultRoot, file)
  const topLevel = topLevelOf(relative)
  return (
    allowedTopLevel.has(topLevel) && supportedAssetExtensions.has(path.extname(file).toLowerCase())
  )
})
const assetIndex = buildAssetIndex(assetFiles)
const publicPlans = []

for (const record of markdownRecords) {
  if (record.frontmatter?.publish !== true) {
    report.skippedNotes += 1
    continue
  }

  const topLevel = topLevelOf(record.relative)
  if (forbiddenTopLevel.has(topLevel)) {
    report.failures.push(`${record.relative}: publish true note is in forbidden source directory`)
    continue
  }
  if (!allowedTopLevel.has(topLevel)) {
    report.failures.push(
      `${record.relative}: publish true note is outside allowed source directories`,
    )
    continue
  }

  const missing = requiredFrontmatter.filter((field) => record.frontmatter[field] == null)
  if (missing.length > 0) {
    report.failures.push(
      `${record.relative}: missing required frontmatter fields: ${missing.join(", ")}`,
    )
    continue
  }
  if (!Array.isArray(record.frontmatter.tags)) {
    report.failures.push(`${record.relative}: tags must be a YAML list`)
    continue
  }

  const outputRelative = outputRelativePath(record)
  const outputPath = path.join(contentRoot, outputRelative)
  publicPlans.push({ ...record, outputRelative, outputPath })
}

const duplicateOutputs = findDuplicates(
  publicPlans.map((plan) => plan.outputRelative.toLowerCase()),
)
for (const duplicate of duplicateOutputs) {
  const sources = publicPlans
    .filter((plan) => plan.outputRelative.toLowerCase() === duplicate)
    .map((plan) => plan.relative)
    .join(", ")
  report.failures.push(`duplicate output path ${duplicate}: ${sources}`)
}

const publicLinkIndex = buildPublicLinkIndex(publicPlans, report)

for (const plan of publicPlans) {
  const rewritten = await rewriteAssets(plan.sourceText, plan.sourcePath, assetIndex, report)
  report.failures.push(...findPrivateWikilinks(rewritten, plan.relative, publicLinkIndex))
  report.failures.push(...findForbiddenLeaks(rewritten, plan.relative))

  plan.outputText = rewritten
  report.copiedNotes.push({
    from: plan.relative,
    to: path.relative(repoRoot, plan.outputPath),
    title: plan.frontmatter.title,
    slug: plan.frontmatter.slug ?? null,
  })
}

await writeReport()

if (report.failures.length > 0) {
  console.error(`Public note sync failed with ${report.failures.length} issue(s).`)
  for (const failure of report.failures) {
    console.error(`- ${failure}`)
  }
  process.exit(1)
}

if (!dryRun) {
  await rm(contentRoot, { recursive: true, force: true })
  await mkdir(contentRoot, { recursive: true })
  await mkdir(assetRoot, { recursive: true })

  for (const plan of publicPlans) {
    await mkdir(path.dirname(plan.outputPath), { recursive: true })
    await writeFile(plan.outputPath, plan.outputText)
  }

  await copyPlannedAssets(report)
}

await writeReport()

console.log(
  `${dryRun ? "Dry-run checked" : "Synced"} ${report.copiedNotes.length} public note(s), ${report.copiedAssets.length} asset(s); skipped ${report.skippedNotes} private note(s). Report: ${path.relative(repoRoot, reportPath)}`,
)

function parseArgs(argv) {
  const parsed = {}
  for (let index = 0; index < argv.length; index += 1) {
    const item = argv[index]
    if (!item.startsWith("--")) {
      continue
    }
    const key = item.slice(2)
    if (key === "dry-run") {
      parsed[key] = true
      continue
    }
    parsed[key] = argv[index + 1]
    index += 1
  }
  return parsed
}

async function exists(filePath) {
  try {
    await stat(filePath)
    return true
  } catch {
    return false
  }
}

async function walk(dir) {
  const entries = await readdir(dir, { withFileTypes: true })
  const files = []
  for (const entry of entries) {
    if (hardIgnoredTopLevel.has(entry.name)) {
      continue
    }
    const fullPath = path.join(dir, entry.name)
    if (entry.isDirectory()) {
      files.push(...(await walk(fullPath)))
    } else if (entry.isFile()) {
      files.push(fullPath)
    }
  }
  return files
}

function parseFrontmatter(text) {
  const normalized = text.replace(/\r\n/g, "\n")
  if (!normalized.startsWith("---\n")) {
    return {}
  }
  const end = normalized.indexOf("\n---", 4)
  if (end === -1) {
    return {}
  }
  try {
    return YAML.parse(normalized.slice(4, end), { logLevel: "silent" }) ?? {}
  } catch {
    return {}
  }
}

function topLevelOf(relativePath) {
  return relativePath.split(path.sep)[0]
}

function buildAssetIndex(files) {
  const index = new Map()
  for (const file of files) {
    const key = path.basename(file).toLowerCase()
    const matches = index.get(key) ?? []
    matches.push(file)
    index.set(key, matches)
  }
  return index
}

function outputRelativePath(record) {
  if (record.frontmatter.slug) {
    const slug = String(record.frontmatter.slug)
      .split("/")
      .map((segment) => sanitizeSegment(segment) || "note")
      .join("/")
    return `${slug}.md`
  }

  return sanitizeRelativeMarkdownPath(record.relative)
}

function sanitizeSegment(segment) {
  return segment
    .normalize("NFKD")
    .replace(/[^\w.-]+/g, "-")
    .replace(/^-+|-+$/g, "")
    .toLowerCase()
}

function sanitizeRelativeMarkdownPath(relativePath) {
  return relativePath
    .split(path.sep)
    .map((segment) => sanitizeSegment(segment) || "note")
    .join(path.sep)
}

function findDuplicates(values) {
  const counts = new Map()
  for (const value of values) {
    counts.set(value, (counts.get(value) ?? 0) + 1)
  }
  return [...counts.entries()].filter(([, count]) => count > 1).map(([value]) => value)
}

function buildPublicLinkIndex(plans, report) {
  const index = new Map()
  const add = (key, plan) => {
    const clean = normalizeLinkKey(key)
    if (!clean) {
      return
    }
    const matches = index.get(clean) ?? []
    matches.push(plan)
    index.set(clean, matches)
  }

  for (const plan of plans) {
    add(plan.relative, plan)
    add(plan.relative.replace(/\.md$/i, ""), plan)
    add(path.basename(plan.relative, ".md"), plan)
    add(plan.frontmatter.title, plan)
    add(plan.frontmatter.slug, plan)
    add(plan.outputRelative, plan)
    add(plan.outputRelative.replace(/\.md$/i, ""), plan)
    for (const alias of plan.frontmatter.aliases ?? []) {
      add(alias, plan)
    }
  }

  for (const [key, matches] of index) {
    const uniqueOutputs = new Set(matches.map((plan) => plan.outputRelative))
    if (uniqueOutputs.size > 1) {
      report.failures.push(
        `ambiguous public wikilink key "${key}" maps to: ${[...uniqueOutputs].join(", ")}`,
      )
    }
  }

  return index
}

function normalizeLinkKey(value) {
  if (!value) {
    return ""
  }
  return String(value).replace(/\\/g, "/").replace(/\.md$/i, "").trim().toLowerCase()
}

async function rewriteAssets(text, notePath, assetIndex, report) {
  let rewritten = text

  const obsidianImagePattern = /!\[\[([^\]|#]+)(?:#[^\]|]+)?(?:\|[^\]]+)?\]\]/g
  rewritten = await replaceAsync(rewritten, obsidianImagePattern, async (match, target) => {
    const resolved = await resolveAsset(target, notePath, assetIndex)
    if (!resolved) {
      report.failures.push(`${path.relative(vaultRoot, notePath)}: unresolved asset ${target}`)
      return match
    }
    const publicTarget = await planAssetCopy(resolved, report)
    return `![[${publicTarget}]]`
  })

  const markdownImagePattern = /!\[([^\]]*)\]\(([^)]+)\)/g
  rewritten = await replaceAsync(rewritten, markdownImagePattern, async (match, alt, rawTarget) => {
    if (/^https?:\/\//i.test(rawTarget) || rawTarget.startsWith("#")) {
      return match
    }
    const target = decodeURIComponent(rawTarget.split(/\s+/)[0])
    const resolved = await resolveAsset(target, notePath, assetIndex)
    if (!resolved) {
      report.failures.push(`${path.relative(vaultRoot, notePath)}: unresolved image ${rawTarget}`)
      return match
    }
    const publicTarget = await planAssetCopy(resolved, report)
    return `![${alt}](/${publicTarget})`
  })

  return rewritten
}

async function replaceAsync(text, regex, replacer) {
  const replacements = []
  text.replace(regex, (...match) => {
    replacements.push(replacer(...match))
    return match[0]
  })
  const resolved = await Promise.all(replacements)
  return text.replace(regex, () => resolved.shift())
}

async function resolveAsset(target, notePath, assetIndex) {
  const decoded = decodeURIComponent(target).replace(/\\/g, "/")
  const directCandidates = [
    path.resolve(path.dirname(notePath), decoded),
    path.resolve(vaultRoot, decoded),
  ]

  for (const candidate of directCandidates) {
    if (await exists(candidate)) {
      return candidate
    }
  }

  const basename = path.basename(decoded).toLowerCase()
  const matches = assetIndex.get(basename) ?? []
  if (matches.length > 1) {
    report.failures.push(
      `${path.relative(vaultRoot, notePath)}: ambiguous asset ${target}: ${matches.map((file) => path.relative(vaultRoot, file)).join(", ")}`,
    )
    return null
  }
  return matches[0] ?? null
}

async function planAssetCopy(sourcePath, report) {
  const content = await readFile(sourcePath)
  const digest = crypto.createHash("sha256").update(content).digest("hex").slice(0, 10)
  const outputName = `${digest}-${sanitizeSegment(path.basename(sourcePath))}`
  const outputPath = path.join(assetRoot, outputName)
  const publicTarget = `assets/${outputName}`

  if (!report.copiedAssets.some((item) => item.to === publicTarget)) {
    report.copiedAssets.push({
      from: path.relative(vaultRoot, sourcePath),
      to: publicTarget,
      outputPath,
    })
  }
  return publicTarget
}

async function copyPlannedAssets(report) {
  for (const item of report.copiedAssets) {
    const sourcePath = path.join(vaultRoot, item.from)
    const outputPath = item.outputPath
    if (!(await exists(outputPath))) {
      await mkdir(path.dirname(outputPath), { recursive: true })
      await copyFile(sourcePath, outputPath)
    }
    delete item.outputPath
  }
}

function findPrivateWikilinks(text, relativeNotePath, publicLinkIndex) {
  const issues = []

  for (const match of text.matchAll(/(?<!!)\[\[([^\]|#]+)(?:#[^\]|]+)?(?:\|[^\]]+)?\]\]/g)) {
    const target = match[1].trim()
    const key = normalizeLinkKey(target)
    const matches = publicLinkIndex.get(key) ?? []
    const uniqueOutputs = new Set(matches.map((plan) => plan.outputRelative))
    if (uniqueOutputs.size !== 1) {
      issues.push(`${relativeNotePath}: wikilink points outside public allowlist: ${target}`)
    }
  }
  return issues
}

function findForbiddenLeaks(text, relativeNotePath) {
  const patterns = [
    { label: "local macOS user path", pattern: /\/Users\/[A-Za-z0-9._-]+/ },
    { label: "file URL", pattern: /file:\/\//i },
    { label: "iCloud Obsidian path", pattern: /Library\/Mobile Documents\/iCloud~md~obsidian/i },
    { label: "execution-system path", pattern: /execution-system\//i },
    { label: "system control-plane path", pattern: /(^|[^A-Za-z0-9_-])system\//i },
    { label: "agent skill path", pattern: /\.agents\//i },
    { label: "Obsidian config path", pattern: /\.obsidian\//i },
    { label: "private key", pattern: /-----BEGIN [A-Z ]*PRIVATE KEY-----/ },
    { label: "env secret assignment", pattern: /\b[A-Z0-9_]*(TOKEN|SECRET|API_KEY|PASSWORD)\s*=/ },
  ]
  return patterns
    .filter((rule) => rule.pattern.test(text))
    .map((rule) => `${relativeNotePath}: matched ${rule.label}`)
}

async function writeReport() {
  const publicReport = {
    ...report,
    copiedAssets: report.copiedAssets.map(({ outputPath, ...item }) => item),
  }
  await mkdir(path.dirname(reportPath), { recursive: true })
  await writeFile(reportPath, `${JSON.stringify(publicReport, null, 2)}\n`)
}

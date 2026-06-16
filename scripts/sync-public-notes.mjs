#!/usr/bin/env node

import { copyFile, mkdir, readdir, readFile, rm, stat, writeFile } from "node:fs/promises"
import crypto from "node:crypto"
import path from "node:path"
import process from "node:process"
import YAML from "yaml"

const repoRoot = process.cwd()
const args = parseArgs(process.argv.slice(2))
const vaultRoot = path.resolve(args.vault ?? process.env.OBSIDIAN_VAULT ?? "")
const contentRoot = path.resolve(args.out ?? "content/notes")
const assetRoot = path.resolve(args.assets ?? "content/assets")
const reportPath = path.resolve(args.report ?? "sync-report.json")
const dryRun = Boolean(args["dry-run"])

const allowedTopLevel = new Set(["data-center", "\u624b\u8bb0"])
const hardIgnoredTopLevel = new Set([".agents", ".git", ".obsidian", ".trash", "node_modules"])

const forbiddenTopLevel = new Set([...hardIgnoredTopLevel, "execution-system", "system"])

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
  markdownFiles.map(async (file) => ({
    sourcePath: file,
    relative: path.relative(vaultRoot, file),
    frontmatter: parseFrontmatter(await readFile(file, "utf8")),
  })),
)
const publicMarkdownFiles = markdownRecords
  .filter(({ relative, frontmatter }) => {
    const topLevel = relative.split(path.sep)[0]
    return frontmatter?.publish === true && allowedTopLevel.has(topLevel)
  })
  .map(({ sourcePath }) => sourcePath)
const assetFiles = allFiles.filter((file) => {
  const topLevel = path.relative(vaultRoot, file).split(path.sep)[0]
  return (
    allowedTopLevel.has(topLevel) && supportedAssetExtensions.has(path.extname(file).toLowerCase())
  )
})
const assetIndex = buildAssetIndex(assetFiles)

const report = {
  copiedNotes: [],
  copiedAssets: [],
  skippedNotes: 0,
  failures: [],
  warnings: [],
}

if (!dryRun) {
  await rm(contentRoot, { recursive: true, force: true })
  await mkdir(contentRoot, { recursive: true })
  await mkdir(assetRoot, { recursive: true })
}

for (const { sourcePath, relative, frontmatter } of markdownRecords) {
  if (frontmatter?.publish !== true) {
    report.skippedNotes += 1
    continue
  }

  const topLevel = relative.split(path.sep)[0]
  if (forbiddenTopLevel.has(topLevel)) {
    report.failures.push(`${relative}: publish true note is in forbidden source directory`)
    continue
  }
  if (!allowedTopLevel.has(topLevel)) {
    report.failures.push(`${relative}: publish true note is outside allowed source directories`)
    continue
  }

  const missing = ["title", "date", "tags"].filter((field) => frontmatter[field] == null)
  if (missing.length > 0) {
    report.failures.push(`${relative}: missing required frontmatter fields: ${missing.join(", ")}`)
    continue
  }

  const sourceText = await readFile(sourcePath, "utf8")
  const rewritten = await rewriteAssets(sourceText, sourcePath, assetIndex, report)
  report.failures.push(...findPrivateWikilinks(rewritten, relative, publicMarkdownFiles, vaultRoot))

  const outputPath = path.join(contentRoot, sanitizeRelativeMarkdownPath(relative))
  report.copiedNotes.push({ from: relative, to: path.relative(repoRoot, outputPath) })

  if (!dryRun) {
    await mkdir(path.dirname(outputPath), { recursive: true })
    await writeFile(outputPath, rewritten)
  }
}

if (!dryRun) {
  await writeFile(reportPath, `${JSON.stringify(report, null, 2)}\n`)
}

if (report.failures.length > 0) {
  console.error(`Public note sync failed with ${report.failures.length} issue(s).`)
  for (const failure of report.failures) {
    console.error(`- ${failure}`)
  }
  process.exit(1)
}

console.log(
  `Synced ${report.copiedNotes.length} public note(s), ${report.copiedAssets.length} asset(s); skipped ${report.skippedNotes} private note(s).`,
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
  if (!text.startsWith("---\n")) {
    return {}
  }
  const end = text.indexOf("\n---", 4)
  if (end === -1) {
    return {}
  }
  try {
    return YAML.parse(text.slice(4, end), { logLevel: "silent" }) ?? {}
  } catch {
    return {}
  }
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

async function rewriteAssets(text, notePath, assetIndex, report) {
  let rewritten = text

  const obsidianImagePattern = /!\[\[([^\]|#]+)(?:#[^\]|]+)?(?:\|[^\]]+)?\]\]/g
  rewritten = await replaceAsync(rewritten, obsidianImagePattern, async (match, target) => {
    const resolved = await resolveAsset(target, notePath, assetIndex)
    if (!resolved) {
      report.failures.push(`${path.relative(vaultRoot, notePath)}: unresolved asset ${target}`)
      return match
    }
    const publicTarget = await copyAsset(resolved, report)
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
    const publicTarget = await copyAsset(resolved, report)
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
  return matches.length === 1 ? matches[0] : null
}

async function copyAsset(sourcePath, report) {
  const digest = crypto.createHash("sha256").update(sourcePath).digest("hex").slice(0, 10)
  const outputName = `${digest}-${sanitizeSegment(path.basename(sourcePath))}`
  const outputPath = path.join(assetRoot, outputName)
  const publicTarget = `assets/${outputName}`

  if (!dryRun && !(await exists(outputPath))) {
    await mkdir(path.dirname(outputPath), { recursive: true })
    await copyFile(sourcePath, outputPath)
  }

  if (!report.copiedAssets.some((item) => item.to === publicTarget)) {
    report.copiedAssets.push({ from: path.relative(vaultRoot, sourcePath), to: publicTarget })
  }
  return publicTarget
}

function findPrivateWikilinks(text, relativeNotePath, publicMarkdownFiles, vaultRootPath) {
  const issues = []
  const publicStems = new Set(
    publicMarkdownFiles
      .map((file) => ({ file, fm: null }))
      .map(({ file }) => {
        const relative = path.relative(vaultRootPath, file)
        return path.basename(relative, ".md").toLowerCase()
      }),
  )

  for (const match of text.matchAll(/(?<!!)\[\[([^\]|#]+)(?:#[^\]|]+)?(?:\|[^\]]+)?\]\]/g)) {
    const target = match[1].trim()
    const stem = path.basename(target, ".md").toLowerCase()
    if (!publicStems.has(stem)) {
      issues.push(`${relativeNotePath}: wikilink points outside public allowlist: ${target}`)
    }
  }
  return issues
}

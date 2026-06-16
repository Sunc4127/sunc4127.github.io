#!/usr/bin/env node

import { readdir, readFile, stat } from "node:fs/promises"
import path from "node:path"
import process from "node:process"
import YAML from "yaml"

const repoRoot = process.cwd()
const scanRoots = ["content", "public"]

const forbiddenPatterns = [
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

const failures = []

async function exists(filePath) {
  try {
    await stat(filePath)
    return true
  } catch {
    return false
  }
}

async function walk(dir) {
  if (!(await exists(dir))) {
    return []
  }

  const entries = await readdir(dir, { withFileTypes: true })
  const files = []
  for (const entry of entries) {
    const fullPath = path.join(dir, entry.name)
    if (entry.isDirectory()) {
      if (["node_modules", ".git", ".quartz", ".quartz-cache"].includes(entry.name)) {
        continue
      }
      files.push(...(await walk(fullPath)))
    } else if (entry.isFile()) {
      files.push(fullPath)
    }
  }
  return files
}

function parseFrontmatter(text) {
  if (!text.startsWith("---\n")) {
    return null
  }

  const end = text.indexOf("\n---", 4)
  if (end === -1) {
    return null
  }

  try {
    return YAML.parse(text.slice(4, end), { logLevel: "silent" }) ?? {}
  } catch {
    return null
  }
}

function rel(filePath) {
  return path.relative(repoRoot, filePath)
}

for (const root of scanRoots) {
  const files = await walk(path.join(repoRoot, root))
  for (const file of files) {
    const relative = rel(file)
    const text = await readFile(file, "utf8").catch(() => "")

    for (const rule of forbiddenPatterns) {
      if (rule.pattern.test(text)) {
        failures.push(`${relative}: matched ${rule.label}`)
      }
    }

    if (root === "content" && relative.endsWith(".md")) {
      const data = parseFrontmatter(text)
      if (!data || data.publish !== true) {
        failures.push(`${relative}: missing required publish: true frontmatter`)
      }
      if (!data?.title || !data?.date || !data?.tags) {
        failures.push(`${relative}: missing one of title/date/tags`)
      }
    }
  }
}

if (failures.length > 0) {
  console.error("Public content safety scan failed:")
  for (const failure of failures) {
    console.error(`- ${failure}`)
  }
  process.exit(1)
}

console.log("Public content safety scan passed.")

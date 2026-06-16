#!/usr/bin/env node

import { readdir, readFile, stat } from "node:fs/promises"
import path from "node:path"
import process from "node:process"

const repoRoot = process.cwd()
const publicRoot = path.join(repoRoot, "public")
const homepagePath = path.join(publicRoot, "index.html")

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
      files.push(...(await walk(fullPath)))
    } else if (entry.isFile()) {
      files.push(fullPath)
    }
  }
  return files
}

function fail(message) {
  failures.push(message)
}

function assertAbsent(html, pattern, label) {
  if (pattern.test(html)) {
    fail(`homepage still renders ${label}`)
  }
}

function assertPresent(text, pattern, label) {
  if (!pattern.test(text)) {
    fail(`homepage smoke missing ${label}`)
  }
}

function publicTargetForHref(href) {
  const cleanHref = href.replace(/^\.?\//, "").replace(/\/$/, "")
  if (!cleanHref || cleanHref.startsWith("#")) {
    return null
  }

  if (path.extname(cleanHref)) {
    return path.join(publicRoot, cleanHref)
  }

  return path.join(publicRoot, `${cleanHref}.html`)
}

if (!(await exists(homepagePath))) {
  fail("public/index.html is missing; run npm run build before check:homepage")
} else {
  const html = await readFile(homepagePath, "utf8")
  assertPresent(html, /class="garden-hero"/, "garden hero markup")
  assertPresent(html, /class="topic-grid"/, "topic grid markup")
  assertAbsent(html, /<h1 class="article-title">/, "default article title before custom hero")
  assertAbsent(html, /class="content-meta"/, "content meta before custom hero")
  assertAbsent(html, /class="note-properties\b/, "note properties on index page")

  const hrefs = [...html.matchAll(/<a\b[^>]*\bhref="(\.\/[^"#?]+)"/g)].map((match) => match[1])
  for (const href of hrefs) {
    const target = publicTargetForHref(href)
    if (target && !(await exists(target))) {
      fail(`homepage link ${href} does not resolve to ${path.relative(repoRoot, target)}`)
    }
  }
}

const cssFiles = (await walk(publicRoot)).filter((file) => file.endsWith(".css"))
const cssText = (await Promise.all(cssFiles.map((file) => readFile(file, "utf8")))).join("\n")
assertPresent(cssText, /\.garden-hero\b/, "compiled garden hero CSS")
assertPresent(
  cssText,
  /body\[data-slug=index\]\s*\.sidebar\.right\{display:none\}/,
  "index right sidebar suppression",
)

if (failures.length > 0) {
  console.error("Homepage render smoke scan failed:")
  for (const failure of failures) {
    console.error(`- ${failure}`)
  }
  process.exit(1)
}

console.log("Homepage render smoke scan passed.")

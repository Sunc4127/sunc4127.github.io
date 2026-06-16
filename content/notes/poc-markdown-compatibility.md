---
title: POC Markdown Compatibility
date: 2026-06-16
tags:
  - quartz
  - obsidian
  - markdown
publish: true
description: A small note used to verify Quartz 5 support for common Obsidian Markdown features.
---

This note verifies the Markdown features expected by the first Quartz 5 POC.

## Wikilinks

This note links back to [[topics/ai|AI]], [[topics/hci|HCI]], and
[[topics/tools|Tools]].

## Callout

> [!note]
> Quartz should render Obsidian-style callouts without custom content changes.

## Mermaid

```mermaid
flowchart LR
  A[Obsidian note] --> B[publish true]
  B --> C[Quartz content]
  C --> D[GitHub Pages]
```

## Code

```ts
type PublicNote = {
  title: string
  date: string
  tags: string[]
  publish: true
}
```

## Tasks

- [x] Explicit publish frontmatter
- [x] Wikilink rendering
- [x] Callout rendering
- [x] Mermaid rendering

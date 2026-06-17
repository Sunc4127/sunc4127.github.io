# Scott's Garden

This repository powers the Quartz 5 version of `https://sunc4127.github.io`.
It replaces the old VuePress/Vdoing implementation while keeping the legacy
site recoverable from the `legacy/vuepress-vdoing-2026-06-16` tag.

## Content Contract

The public site is allowlist-only. A note is publishable only when its
frontmatter includes:

```yaml
---
title: Example Note
date: 2026-06-16
tags:
  - ai
publish: true
---
```

Optional fields: `description`, `slug`, `updated`.

The local Obsidian vault is not deployed as a public repository. The sync script
copies only explicitly public notes into `content/notes/public/` and reports
unresolved private links or assets before writing public files.

## Local Commands

```sh
npm ci
npm run build
npm run check:public
```

To sync public notes from the local vault:

```sh
npm run sync:content -- --vault "/path/to/Obsidian" --dry-run
npm run sync:content -- --vault "/path/to/Obsidian"
npm run validate
```

External image URLs, including historical jsDelivr image-hosting links, are
kept unchanged. Local Obsidian attachments referenced by public notes are copied
into `content/assets/`.

`sync:content` is fail-closed: notes outside `data-center/` and `手记/`, missing
required frontmatter, unresolved private wikilinks, ambiguous local assets, or
local absolute path leaks stop the sync and write a `sync-report*.json` report.

## Deployment

GitHub Pages is deployed with GitHub Actions from `main`. Feature branches run
CI checks, while production changes go live after they are merged or pushed to
`main`.

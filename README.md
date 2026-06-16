# Scott's Garden

This branch is a Quartz 5 proof of concept for `https://sunc4127.github.io`.
It replaces the old VuePress/Vdoing implementation only on this POC branch.
The legacy site remains recoverable from `main`, `gh-pages`, and the
`legacy/vuepress-vdoing-2026-06-16` tag.

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
copies only explicitly public notes into `content/` and reports unresolved
private links or assets.

## Local Commands

```sh
npm ci
npm run build
npm run check:public
```

To sync public notes from the local vault:

```sh
npm run sync:content -- --vault "/path/to/Obsidian"
npm run validate
```

External image URLs, including historical jsDelivr image-hosting links, are
kept unchanged. Local Obsidian attachments referenced by public notes are copied
into `content/assets/`.

## Deployment

GitHub Pages is deployed with GitHub Actions from `main`. The POC branch builds
in CI but does not publish over the live site until the branch is merged or the
deployment workflow is manually adjusted.

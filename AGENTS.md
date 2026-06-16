# AGENTS.md

This repository hosts the Quartz 5 POC for `sunc4127.github.io`.

## Rules

- Do not copy the full Obsidian vault into this repository.
- Public content must live under `content/` and include `publish: true`.
- Do not commit local vault paths, raw private notes, execution logs, financial,
  family, health, career application, Dida, Notion governance, or daily-log
  material.
- Generated output in `public/` is not committed.
- Use `npm run build` and `npm run check:public` before calling the branch ready.

## Content Sources

The intended local source is Scott's Obsidian vault. Use
`scripts/sync-public-notes.mjs` to copy allowlisted notes and assets into
Quartz. The sync script is conservative by design: unresolved private wikilinks,
unresolved local assets, missing required frontmatter, or forbidden source
directories are build blockers for published notes.

## Deployment

GitHub Pages uses Actions. The POC branch should pass CI first; production
deployment remains tied to `main` until the final cutover is approved.

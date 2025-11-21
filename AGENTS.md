# Agent Guidelines

This repository hosts the VuePress-based blog for **Sunc4127** using the `vuepress-theme-vdoing` theme. Follow the guidance below when making changes:

- Use `npm` (or `yarn`) scripts defined in `package.json` for development (`npm run dev`) and production builds (`npm run build`). Run a build before committing major content or configuration changes to ensure the site still compiles.
- Keep Markdown content in `docs/` tidy: prefer fenced code blocks, avoid trailing whitespace, and maintain existing front-matter fields. The helper script `npm run editFm` can normalize front matter metadata when needed.
- When updating deployment automation or shell scripts under the repository root, stick to POSIX-compliant shell syntax (the current scripts use `/usr/bin/env sh`).
- Avoid committing generated artifacts such as `docs/.vuepress/dist` or local caches. They should be produced during deployment via `deploy.sh`.

If you add new directories with their own conventions, include nested `AGENTS.md` files to document any additional, directory-specific rules.

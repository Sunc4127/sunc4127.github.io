#!/usr/bin/env sh

# 确保脚本抛出遇到的错误
set -e

# 生成静态文件
npm run build

# 进入生成的文件夹
cd docs/.vuepress/dist

# deploy to github pages
#git push -f git@github.com:<Sunc4127>/<Sunc4127>.github.io.git master

if [ -z "$GITHUB_TOKEN" ]; then
  msg='deploy'
  githubUrl=git@github.com:Sunc4127/Sunc4127.github.io.git
else
  msg='来自github actions的自动部署'
  githubUrl=https://Sunc4127:${GITHUB_TOKEN}@git@github.com:Sunc4127/Sunc4127.github.io.git
  git config --global user.name "Sunc4127"
  git config --global user.email "sccplay888@gmail.com"
fi
git init
git add -A
git commit -m "${msg}"
git push -f $githubUrl HEAD:gh-pages # 推送到github gh-pages分支


cd -
rm -rf docs/.vuepress/dist

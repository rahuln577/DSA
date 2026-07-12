#!/usr/bin/env bash
set -euo pipefail

cd "$(git rev-parse --show-toplevel)"

if ! git rev-parse --is-inside-work-tree >/dev/null 2>&1; then
  echo "Error: not inside a git repository."
  exit 1
fi

current_branch="$(git rev-parse --abbrev-ref HEAD)"
if [[ "$current_branch" != "main" ]]; then
  echo "Error: current branch is '$current_branch'. Switch to 'main' before running this script."
  exit 1
fi

latest_commit_message="$(git log -1 --pretty=%B)"
if [[ "$latest_commit_message" =~ [Dd]ay[[:space:]]*([0-9]+) ]]; then
  latest_day="${BASH_REMATCH[1]}"
else
  echo "Error: latest commit message does not contain 'day N'."
  echo "Latest commit message:\n$latest_commit_message"
  exit 1
fi

next_day=$((latest_day + 1))

if git diff --quiet --ignore-submodules -- && git diff --cached --quiet --ignore-submodules --; then
  echo "No changes to commit."
  exit 0
fi

get_tomorrow_date() {
  if date -v+1d "+%Y-%m-%dT%H:%M:%S%z" >/dev/null 2>&1; then
    date -v+1d "+%Y-%m-%dT%H:%M:%S%z"
  else
    date -d "tomorrow" "+%Y-%m-%dT%H:%M:%S%z"
  fi
}

commit_date="$(get_tomorrow_date)"
export GIT_AUTHOR_DATE="$commit_date"
export GIT_COMMITTER_DATE="$commit_date"

git add --all

if git commit -m "day $next_day"; then
  echo "Committed 'day $next_day' with date $commit_date."
  git push origin main
else
  echo "Error: commit failed."
  exit 1
fi

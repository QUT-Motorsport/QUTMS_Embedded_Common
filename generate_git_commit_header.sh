#!/bin/bash
# Fetch the current git commit hash and shorten it
GIT_COMMIT_HASH=$(git rev-parse --short HEAD)

# Check for local changes
if [ -n "$(git status --porcelain)" ]; then
    GIT_DIRTY_FLAG=1
else
    GIT_DIRTY_FLAG=0
fi

# Write to a header file
echo "#define GIT_COMMIT_HASH \"${GIT_COMMIT_HASH}\"" > Inc/git_commit.h
echo "#define GIT_DIRTY_FLAG ${GIT_DIRTY_FLAG}" >> Inc/git_commit.h

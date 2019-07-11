#!/bin/bash

# Print the usage message
function printHelp () {
  echo "Usage: "
  echo "  generateXDR.sh <branch_or_commit_hash>"
  echo
  echo "Example of using"
  echo
  echo "	generateXDR.sh master"
  echo "	generateXDR.sh 84135ed642bff4965ce69f9a91f566d6d525188d"
  echo
}

if [ -z "$1" ]; then
    echo "please select branch or commit hash"
    printHelp
    exit 1
fi

docker pull registry.gitlab.com/tokend/xdrgen-docker:ee57633df7911b7ecfba99c96326ddff81a30d63
docker run --rm -v $PWD/src/xdr:/opt/generated registry.gitlab.com/tokend/xdrgen-docker:ee57633df7911b7ecfba99c96326ddff81a30d63 c++ $1

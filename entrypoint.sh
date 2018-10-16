#!/usr/bin/env bash
set -e

CONFIG=$1
BIN=/usr/local/bin/core
HISTORY=/history

start() {
    $BIN --conf $CONFIG --forcescp
    $BIN --conf $CONFIG
}

init() {
    rm -rf $HISTORY/*
    $BIN --conf $CONFIG --newdb
    $BIN --conf $CONFIG --newhist vs
}

case "$2" in
    "init")
        init
        ;;
    "start")
        start
        ;;
    *)
        start
esac

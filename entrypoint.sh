#!/usr/bin/env bash
set -e

CONFIG=/config.ini
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

case "$1" in
    "init")
        init
        ;;
    "start")
        start
        ;;
    *)
        start
esac

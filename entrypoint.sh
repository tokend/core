#!/usr/bin/env bash

export CONFIG=${CONFIG:-/config.ini}
BIN=/usr/local/bin/core

# will make init if core thinks history does not exist.
# USE AT YOUR ON OWN RISK
ensuredb() {
    # vs history is hard-coded as a de facto standard
    $BIN --conf $CONFIG --histexists vs
    exit_code=$?
    [[ $exit_code -eq 0 ]] && return
    [[ $exit_code -eq 42 ]] && init && return
    echo "histexists failed with $exit_code"
    return $exit_code
}

start() {
    $BIN --conf $CONFIG --forcescp
    $BIN --conf $CONFIG
}

init() {
    $BIN --conf $CONFIG --newdb
    $BIN --conf $CONFIG --newhist vs
}

catchup() {
  $BIN --conf $CONFIG --catchup-complete
}

# Environment variable explanation:
# ENSUREDB - create new history for node, then start node (if no other env var provided)
# DOCATCHUP - do complete catchup, then start node

case "$1" in
    "ensuredb")
        ensuredb
        ;;
    "init")
        init
        ;;
    "start")
        start
        ;;
    "catchup")
        catchup
        ;;
    *)

    echo "ensuredb=$ENSUREDB"
    echo "docatchup=$DOCATCHUP"

    if [ -z "$ENSUREDB" ]; then
        echo "ensuring history will not be done"
    else
        echo "ensuring history..."
        ensuredb
    fi

    if [ -z "$DOCATCHUP" ]; then
        echo "catchup will not be done"
    else
        echo "catchuping history..."
        catchup
    fi

    echo "starting node"
    start

esac

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
    *)

    echo "ensuredb=$ENSUREDB"

    if [ -z "$ENSUREDB" ]; then
        echo "starting node"
        start
    else 
        echo "ensuring history and starting node"
        ensuredb && start
    fi

esac

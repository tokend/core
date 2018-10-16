#!/usr/bin/dumb-init /bin/bash
set -eax

pg-entrypoint.sh postgres &

while ! pg_isready -U$POSTGRES_USER > /dev/null 2> /dev/null; do
    echo "postgres not ready yet"
    sleep 3
done
core-entrypoint.sh $@

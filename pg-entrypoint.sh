#!/usr/bin/dumb-init /bin/bash
set -e

pg-entrypoint.sh postgres &

while ! pg_isready -U$POSTGRES_USER -hlocalhost > /dev/null 2> /dev/null; do
    echo "postgres not ready yet"
    sleep 3
done

core-entrypoint.sh $@

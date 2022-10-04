#!/usr/bin/env bash
set -Eeo pipefail

if [[ "$1" == postgres* ]]; then
 echo "trying to init pgdata"
 BIN=/usr/lib/postgresql/$PG_MAJOR/bin
 mkdir -p "$PGDATA"
 chown -R postgres "$PGDATA"
 chmod 700 "$PGDATA"

 if [ ! -s "$PGDATA/PG_VERSION" ]; then
  su postgres -c 'initdb --username="$POSTGRES_USER" --pwfile=<(echo "$POSTGRES_PASSWORD")'
  su postgres -c 'PGUSER="$POSTGRES_USER" pg_ctl -D "$PGDATA" -o "-c listen_addresses=''" -w start'
  su postgres -c 'PGUSER="$POSTGRES_USER" createdb -O $POSTGRES_USER $POSTGRES_DB'
  su postgres -c 'PGUSER="$POSTGRES_USER" pg_ctl -D "$PGDATA" -m fast -w stop'
  {
   echo
   echo "host all all all trust"
  } >> "$PGDATA/pg_hba.conf"
  echo
  echo 'PostgreSQL init process complete; ready for start up.'
  echo
 fi
fi

su postgres -c "$@"

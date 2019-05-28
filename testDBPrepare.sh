#!/bin/bash

psql -U postgres -c "drop database if exists stellar_test10;"
psql -U postgres -c "create database stellar_test10;"

for i in $(seq 1 15) ''; do
    psql -U postgres -c "drop database if exists stellar_test10$i;"
    psql -U postgres -c "create database stellar_test10$i;"
done

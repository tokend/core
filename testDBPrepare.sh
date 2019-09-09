#!/bin/bash

sudo -u postgres psql -c "drop database if exists stellar_test10;"
sudo -u postgres psql -c "create database stellar_test10;"

for i in $(seq 1 15) ''; do
    sudo -u postgres psql -c "drop database if exists stellar_test10$i;"
    sudo -u postgres psql -c "create database stellar_test10$i;"
done

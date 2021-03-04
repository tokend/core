---
    title: Runing test core network instructions
    author: olegfomenko 
    date: 4 January 2021 
---

# HOWTO Run testnet (with safe quorum) on local machine using docker

## Step 1
### Generate private/public keys pair for prepare nodes launch config

Build locally and run
```commandline
core gen-seed
```

## Step 2
### Create docker network for nodes launch 
Run
```commandline
docker network create --subnet 172.20.0.0/16 --ip-range 172.20.240.0/20 core_bridge
```

## Step 3
### Create docker volumes to save database data locally

Run (creating volume for ledger)
```commandline
docker volume create node001_data
docker volume create node002_data
docker volume create node003_data
```

Run (creating volume for history)
```commandline
docker volume create node001_his
docker volume create node002_his
docker volume create node003_his
```

## Step 4
### Create Dockerfile
```dockerfile
FROM ubuntu:18.04

WORKDIR /build
COPY . /build

ENV VERSION=a81c0ad6

RUN true \
 && apt-get update \
 && apt-get install -y \
      autoconf \
      automake \
      bison \
      flex \
      git \
      gcc \
      g++ \
      libtool \
      libstdc++6 \
      libpq-dev \
      zlib1g-dev \
      libcurl4-openssl-dev \
      pkg-config \
      cmake \
      make

RUN CORE_REVISION=${VERSION} cmake CMakeLists.txt -DPostgreSQL_INCLUDE_DIRS=/usr/include/postgresql/ -DPostgreSQL_LIBRARIES=/usr/lib/x86_64-linux-gnu/libpq.so \
 && make -j4
```

Run
```commandline
docker build . -f Dockerfile -t corebuild
```

Edit pg.dockerfile as in example below
```dockerfile
FROM registry.gitlab.com/tokend/deployment/postgres-ubuntu:9.6

ARG CONF

RUN true \
 && apt-get update \
 && apt-get install -y --no-install-recommends libpq5 libssl1.0.0 awscli s3cmd dumb-init libcurl4 curl \
 && rm -rf /var/lib/apt/lists/* /var/log/*.log /var/log/*/*.log \
 && mkdir /data

COPY --from=corebuild /build/src/core /usr/local/bin/core
COPY $CONF /config.ini
COPY entrypoint.sh /usr/local/bin/core-entrypoint.sh
COPY pg-entrypoint.sh /usr/local/bin/entrypoint.sh
RUN true \
 && mv /usr/bin/entrypoint.sh /usr/local/bin/pg-entrypoint.sh \
 && chmod +x /usr/local/bin/core-entrypoint.sh \
 && chmod +x /usr/local/bin/entrypoint.sh \
 && chmod +x /usr/local/bin/pg-entrypoint.sh

ENV CONFIG=/config.ini
ENV POSTGRES_USER=core
ENV POSTGRES_PASSWORD=core
ENV POSTGRES_DB=core
ENV PGDATA=/data/pgdata

ENTRYPOINT ["entrypoint.sh"]
```

## Step 5
### Node 1 configuration (./config1.ini)
```ini
HTTP_PORT=8081
PEER_PORT=8091

PUBLIC_HTTP_PORT=true
RUN_STANDALONE=false
NODE_IS_VALIDATOR=true
CATCHUP_COMPLETE=true
BUCKET_DIR_PATH="/node_001/buckets"

NETWORK_PASSPHRASE="TokenD Developer Network"
BASE_EXCHANGE_NAME="TokenD"

DATABASE="postgresql://dbname=core user=core password=core host=localhost port=5432"

NODE_SEED="SDO6ESS63ONLCJ2UPFCI4VMBN2SDKYTZNXR5VXRH2CIKVURJ63NUIQFR self"
MASTER_ACCOUNT_ID="GBA4EX43M25UPV4WIE6RRMQOFTWXZZRIPFAI5VPY6Z2ZVVXVWZ6NEOOB"

TX_EXPIRATION_PERIOD=604800

FAILURE_SAFETY=1
UNSAFE_QUORUM=false

NODE_NAMES=[
           "GDXSTPBFJ34CELDV64NAO7OIN6T7LDVFUU7QYKXCP4RPJPPTOC6Q5M5K node_2",
           "GDM67Y33JP4IVTVUMZNB5PUYXZ7D5ZKJQQKTG4DOI4QDR3VHMWVKVKE3 node_3"
]

KNOWN_PEERS=[
            "172.20.0.2:8092",
            "172.20.0.3:8093"
]

[QUORUM_SET]
THRESHOLD_PERCENT=66
VALIDATORS=[
           "$self",
           "$node_2",
           "$node_3"
]

[HISTORY.vs]
get="cp /node_001/history/{0} {1}"
put="cp {0} /node_001/history/{1}"
mkdir="mkdir -p /node_001/history/{0}"

[HISTORY.n2]
get="cp /node_002/history/{0} {1}"

# Secret seed: SDO6ESS63ONLCJ2UPFCI4VMBN2SDKYTZNXR5VXRH2CIKVURJ63NUIQFR
# Public: GBKP6NPFVBTUMJ5RDATFOVHTCCAHNI4YPT5K7BQPNPRIUN5XMGILXANP
```

### Node 2 configuration (./config2.ini)
```ini
HTTP_PORT=8082
PEER_PORT=8092

PUBLIC_HTTP_PORT=true
RUN_STANDALONE=false
NODE_IS_VALIDATOR=true
CATCHUP_COMPLETE=true

BUCKET_DIR_PATH="/node_002/buckets"

NETWORK_PASSPHRASE="TokenD Developer Network"
BASE_EXCHANGE_NAME="TokenD"

DATABASE="postgresql://dbname=core user=core password=core host=localhost port=5432"

NODE_SEED="SCYVAF63FZTFMDGFOAFPDXD5MDZ5V5CGZAN2YMLGGFU65DMGY5LIVRM4 self"
MASTER_ACCOUNT_ID="GBA4EX43M25UPV4WIE6RRMQOFTWXZZRIPFAI5VPY6Z2ZVVXVWZ6NEOOB"

TX_EXPIRATION_PERIOD=604800

FAILURE_SAFETY=1
UNSAFE_QUORUM=false

NODE_NAMES=[
   "GBKP6NPFVBTUMJ5RDATFOVHTCCAHNI4YPT5K7BQPNPRIUN5XMGILXANP node_1",
   "GDM67Y33JP4IVTVUMZNB5PUYXZ7D5ZKJQQKTG4DOI4QDR3VHMWVKVKE3 node_3"
]

KNOWN_PEERS=[
    "172.20.0.1:8091",
    "172.20.0.3:8093"
]

[QUORUM_SET]
THRESHOLD_PERCENT=66
VALIDATORS=[
   "$self",
   "$node_1",
   "$node_3"
]

[HISTORY.vs]
get="cp /node_002/history/{0} {1}"
put="cp {0} /node_002/history/{1}"
mkdir="mkdir -p /node_002/history/{0}"

# Secret seed: SCYVAF63FZTFMDGFOAFPDXD5MDZ5V5CGZAN2YMLGGFU65DMGY5LIVRM4
# Public: GDXSTPBFJ34CELDV64NAO7OIN6T7LDVFUU7QYKXCP4RPJPPTOC6Q5M5K
```

### Node 3 configuration (./config3.ini)
```ini
HTTP_PORT=8083
PEER_PORT=8093

PUBLIC_HTTP_PORT=true
RUN_STANDALONE=false
NODE_IS_VALIDATOR=true
CATCHUP_COMPLETE=true

BUCKET_DIR_PATH="/node_003/buckets"

NETWORK_PASSPHRASE="TokenD Developer Network"
BASE_EXCHANGE_NAME="TokenD"

DATABASE="postgresql://dbname=core user=core password=core host=localhost port=5432"

NODE_SEED="SCNBXATLI6OHGDVML62E5QXVB5PBR6BPTFGTC42HEHB7GHZFVY4WCFZY self"
MASTER_ACCOUNT_ID="GBA4EX43M25UPV4WIE6RRMQOFTWXZZRIPFAI5VPY6Z2ZVVXVWZ6NEOOB"

TX_EXPIRATION_PERIOD=604800

FAILURE_SAFETY=1
UNSAFE_QUORUM=false

NODE_NAMES=[
   "GBKP6NPFVBTUMJ5RDATFOVHTCCAHNI4YPT5K7BQPNPRIUN5XMGILXANP node_1",
   "GDXSTPBFJ34CELDV64NAO7OIN6T7LDVFUU7QYKXCP4RPJPPTOC6Q5M5K node_2"
]

KNOWN_PEERS=[
    "172.20.0.1:8091",
    "172.20.0.2:8092"
]

[QUORUM_SET]
THRESHOLD_PERCENT=66
VALIDATORS=[
   "$self",
   "$node_1",
   "$node_2"
]

[HISTORY.vs]
get="cp /node_003/history/{0} {1}"
put="cp {0} /node_003/history/{1}"
mkdir="mkdir -p /node_003/history/{0}"

# Secret seed: SCNBXATLI6OHGDVML62E5QXVB5PBR6BPTFGTC42HEHB7GHZFVY4WCFZY
# Public: GDM67Y33JP4IVTVUMZNB5PUYXZ7D5ZKJQQKTG4DOI4QDR3VHMWVKVKE3
```

## Step 6
### Node image building
```commandline
docker build . -f pg.dockerfile -t node001 --build-arg CONF=./config1.in
docker build . -f pg.dockerfile -t node002 --build-arg CONF=./config2.ini
docker build . -f pg.dockerfile -t node003 --build-arg CONF=./config3.ini
```

### First start (with creating new ledger history)

Run two nodes (node002 & node003) to start system
```commandline
docker run --network core_bridge --ip 172.20.0.2 -p 8082:8082 -v node002_data:/data -v node002_his:/node_002 -e ENSUREDB=1 node002
docker run --network core_bridge --ip 172.20.0.3 -p 8083:8083 -v node003_data:/data -v node003_his:/node_003 -e ENSUREDB=1 node003
```

Add third node to system. __-v node002_his:/node_002/history__ links containers history for node catchup
```commandline
docker run --network core_bridge --ip 172.20.0.1 -p 8081:8081 -v node001_data:/data -v node001_his:/node_001 -v node002_his:/node_002 -e ENSUREDB=1 node001
```

## Notes

### Next launch
Dont forget to remove ENSUREDB=1 environment variable for next launches (this variable used to initiate new database and history) 

### Creating bound to local filesystem volume
```commandline
docker volume create -o type=none -o device=/Users/olegfomenko/node_001/ -o o=bind node001_his
```

### Adding local run node to containerised-run network
- For first you should create bound docker volume from one node to local filesystem with command in previous paragraph
- Don't forget to expose peer port from chosen containerised node with -p 8091:8091 flag (example for node001)
- Run database (easiest way - using container)
```commandline
docker run -e POSTGRES_PASSWORD=core -e POSTGRES_USER=core -e POSTGRES_DB=core -p 5432:5432 postgres
```
- Yse config file config4.local.ini (my local example)

```ini
HTTP_PORT=8084
PEER_PORT=8094

PUBLIC_HTTP_PORT=true
RUN_STANDALONE=false
NODE_IS_VALIDATOR=true
CATCHUP_COMPLETE=true

BUCKET_DIR_PATH="/Users/olegfomenko/node_004/buckets"

NETWORK_PASSPHRASE="TokenD Developer Network"
BASE_EXCHANGE_NAME="TokenD"

DATABASE="postgresql://dbname=core user=core password=core host=localhost port=5432"

NODE_SEED="SBOQ6B4N5AOBUB2EJOWKD3BLQUEO2BGP3HFX2FJBCTIH35CXA6767US3 self"
MASTER_ACCOUNT_ID="GBA4EX43M25UPV4WIE6RRMQOFTWXZZRIPFAI5VPY6Z2ZVVXVWZ6NEOOB"

TX_EXPIRATION_PERIOD=604800

FAILURE_SAFETY=1
UNSAFE_QUORUM=false

NODE_NAMES=[
   "GBKP6NPFVBTUMJ5RDATFOVHTCCAHNI4YPT5K7BQPNPRIUN5XMGILXANP node_1",
   "GDM67Y33JP4IVTVUMZNB5PUYXZ7D5ZKJQQKTG4DOI4QDR3VHMWVKVKE3 node_3"
]

KNOWN_PEERS=[
    "localhost:8091",
    "localhost:8093"
]

[QUORUM_SET]
THRESHOLD_PERCENT=66
VALIDATORS=[
   "$self",
   "$node_1",
   "$node_3"
]

[HISTORY.vs]
get="cp /Users/olegfomenko/node_004/history/{0} {1}"
put="cp {0} /Users/olegfomenko/node_004/history/{1}"
mkdir="mkdir -p /Users/olegfomenko/node_004/history/{0}"

[HISTORY.n1]
get="cp /Users/olegfomenko/node_001/history/{0} {1}"

# Secret seed: SBOQ6B4N5AOBUB2EJOWKD3BLQUEO2BGP3HFX2FJBCTIH35CXA6767US3
# Public: GDGPFGVIERX3GMGKL3L47T7TW54TOF357NOYKISRJ7PMOMPEBKS4YX7Y
```

- Note, that TX_EXPIRATION_PERIOD is mandatory, because first ledger creation depends on it

- _get="cp /Users/olegfomenko/node_001/history/{0} {1}"_ - path to bound volume for node001 history 

- Run
```commandline
core --conf ./config4.local.ini --newdb --newhist vs --forcescp
core --conf ./config4.local.ini
```

- Also, you can use --catchup-complete command 

### Automatic catchup during container starting

- Run command with -e DOCATCHUP=1. Example:
```commandline
docker run --network core_bridge --ip 172.20.0.2 -p 8082:8082 -v node002_data:/data -v node002_his:/node_002 -e ENSUREDB=1 -e DOCATCHUP=1 node002
```
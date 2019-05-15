# Core

Core is a replicated state machine that maintains a local copy of a cryptographic ledger and processes transactions against it, in consensus with a set of peers (forked from [stellar-core](https://github.com/stellar/stellar-core)).
It implements the [Stellar Consensus Protocol](https://github.com/stellar/stellar-core/blob/master/src/scp/readme.md), a _federated_ consensus protocol.
It is written in C++14 and runs on Linux, OSX and Windows.
Learn more by reading the [overview document](https://gitlab.com/tokend/core/blob/master/docs/readme.md).

## Changelog

All notable changes to this project will be documented in [this file](https://gitlab.com/tokend/core/blob/master/docs/changelog.md). This project adheres to Semantic Versioning.

## Documentation

Documentation of the code's layout and abstractions, as well as for the
functionality available, can be found in
[`./docs`](https://gitlab.com/tokend/core/tree/master/docs).

## Builiding 

### On newer distributions with OpenSSL 1.1:

```sh
git submodule update --init
cmake CMakeLists.txt -DPostgreSQL_INCLUDE_DIRS=/usr/include/postgresql/ -DPostgreSQL_LIBRARIES=/usr/lib/libpq.so -DOPENSSL_ROOT_DIR=/usr/lib/openssl-1.0 -DOPENSSL_LIBRARIES=/usr/lib/openssl-1.0 -DOPENSSL_INCLUDE_DIR=/usr/include/openssl-1.0
make -j8
```

Expect warning:

```
warning: libcrypto.so.1.1, needed by /usr/lib/libpq.so, may conflict with libcrypto.so.1.0.0
```

Make sure You typed correct paths to the libs. Consider replacing `-j8` according to the number outputed by:

```sh
# nproc
```

### On older distributions with OpenSSL 1.0:

```sh
git submodule update --init
cmake CMakeLists.txt -DPostgreSQL_INCLUDE_DIRS=/usr/include/postgresql/ -DPostgreSQL_LIBRARIES=/usr/lib/libpq.so
make -j8
```

## TokenD vs stellar-core

The core of **TokenD** is based on the open-source project [stellar-core](github.com/stellar/stellar-core).
TokenD uses SCP as consensus protocol, concept of ledger
and have the data flow process as stellar-core.
However there are several important improvements.

### Account and signer types

Basically, accounts in **stellar-core** all have equal 
possibilities for performing any kind of operation. 
**TokenD**'s core introduces account types (e.g. master account, general account etc).
Any operation falls restrictions about account types which 
could perform it. As an example, this change makes it possible to create very easily 
certain system operations which should not be performed by ordinary accounts. 
TokenD going farther and introduces signer types.
Both together this feature contributes to flexibility of how operations are performed.

### Issuance

One of the most noticeable change is the process of issuance of new assets.
In order to issue some amount of a new asset in **stellar-core**, the receiver must 
hold a trust line in corresponding asset. The amount can be transferred to receiver via 
payment operation.
**TokenD** uses more sophisticated approach and divides this process into  
processing of pre-issuance and issuance requests. Durring asset creation (which is two step process for syndicates),
syndicate is able to provide information like max issuance amount and pre-issuance signer, which restrict total amount of that asset available in the system.
After asset request is approved, syndicate is able to send pre-issuance request (which includes signature of pre-issuance signer).
As soon as this request is approve by the admin of the system (signer of master account), syndicate is able to send issuance request which must include unique reference of such request
(if pre-issued amount is not sufficient, pending issuance request will be created
which can be approved by the syndicate, when sufficient pre-issued amount is available or reject it).
Such an approach is much more safe and reliable and makes integrations with **TokenD** much easier.

### Flexible fee

**Stellar-core** have only a constant fee per transaction.
In **TokenD** it was implemented a reach system of fee charging which 
gives and opportunity to set different fees for different operations (by introducing fee type),
set fees for each account type or even for certain account.
Also it is possible to charge a percent fee from an amount.

### New operations

**TokenD** contains a big list of operations 
comparing to **stellar-core** which is enough to fulfill needs encountered by tokens management systems.

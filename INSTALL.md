Installation Instructions
==================
These are instructions for building stellar-core from source.

For a potentially quicker set up, the following projects could be good alternatives:

* stellar-core in a [docker container](https://github.com/stellar/docker-stellar-core-horizon)
* pre-compiled [packages](https://github.com/stellar/packages)

## Picking a version to run

Best is to use the latest *stable* release that can be downloaded from https://github.com/stellar/stellar-core/releases


Alternatively, branches are organized in the following way:

| branch name | description | quality bar |
| ----------- | ----------- | ----------- |
| master      | development branch | all unit tests passing |
| testnet     | version deployed to testnet | acceptance tests passing |
| prod        | version currently deployed on the live network | no recall class issue found in testnet and staging |

For convenience, we also keep a record in the form of release tags of the
 versions that make it to production:
 * pre-releases are versions that get deployed to testnet
 * releases are versions that made it all the way in prod

When running a node, the best bet is to go with the latest release.

## Build Dependencies

- c++ toolchain and headers that supports c++14
    - `clang` >= 5.0
    - `g++` >= 6.0
- `pkg-config`
- `bison` and `flex`
- `libpq-devel` unless you `./configure --disable-postgres` in the build step below.


### Ubuntu 14.04

    # sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    # apt-get update
    # sudo apt-get install git build-essential pkg-config autoconf automake libtool bison flex libpq-dev libssl-dev clang++-3.5 gcc-4.9 g++-4.9 cpp-4.9


See [installing gcc 4.9 on ubuntu 14.04](http://askubuntu.com/questions/428198/getting-installing-gcc-g-4-9-on-ubuntu)

### OS X
1) When building on OSX, here's some dependencies you'll need:
    - Install xcode or Clion
    - Install homebrew
    - brew install libsodium
    - brew install libtool
    - brew install automake
    - brew install pkg-config
    - brew install libpqxx *(If ./configure later complains about libpq missing, try PKG_CONFIG_PATH='/usr/local/lib/pkgconfig')* 
    - brew install openssl
    - brew install gcc

2) Set build Cmake options
    
    ```
    -DOPENSSL_LIBRARIES=/usr/local/opt/openssl@1.1 
    -DOPENSSL_INCLUDE_DIR=/usr/local/opt/openssl@1.1 
    -DPostgreSQL_INCLUDE_DIRS=/usr/local/include 
    -DPostgreSQL_LIBRARIES=/usr/local/lib/libpq.so
    ```

3) Edit or create new config file using ./docs/example.core.ini

    __Recommendation:__ change all paths in config file to local directory (for example change /deta to ./data)

4) If you using Clion config Preferences->BuildTools->Toolchain for using GNU G++ compiler (standard path is /usr/local/Cellar/gcc/10.2.0/bin/g++-10)

5) Build project

6) Launch PG database. Docker usage example:
    ```commandline
    docker run -e POSTGRES_PASSWORD=core -e POSTGRES_USER=core -e POSTGRES_DB=core -p 5432:5432 postgres
    ```
7) Launch built application (commands example execution in project root)
    ```commandline
        ./src/core --conf ./docs/example.core.ini --newdb --ll DEBUG
        ./src/core --conf ./docs/example.core.ini --ll DEBUG
    ```

### Windows 
See [INSTALL-Windows.txt](INSTALL-Windows.txt)

## Basic Installation

- `git clone https://github.com/stellar/stellar-core.git`
- `cd stellar-core`
- `git submodule init`
- `git submodule update`
- Type `./autogen.sh`.
- Type `./configure`   *(If configure complains about compiler versions, try `CXX=clang-5.0 ./configure` or `CXX=g++-6 ./configure` or similar, depending on your compiler.)*
- Type `make` or `make -j` (for aggressive parallel build)
- Type `make check` to run tests.
- Type `make install` to install.

## Building with clang and libc++

On some systems, building with `libc++`, [LLVM's version of the standard library](https://libcxx.llvm.org/) can be done instead of `libstdc++` (typically used on Linux).

NB: there are newer versions available of both clang and libc++, you will have to use the versions suited for your system.

You may need to install additional packages for this, for example, on Linux Ubuntu:

    # install libc++ headers
    sudo apt-get install libc++-dev libc++abi-dev

Here are sample steps to achieve this:

    export CC=clang-5.0
    export CXX=clang++-5.0
    export CFLAGS="-O3 -g1 -fno-omit-frame-pointer"
    export CXXFLAGS="$CFLAGS -stdlib=libc++ -isystem /usr/include/libcxxabi"
    git clone https://github.com/stellar/stellar-core.git
    cd stellar-core/
    ./autogen.sh && ./configure && make -j6

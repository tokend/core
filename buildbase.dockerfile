FROM ubuntu:18.04

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

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
      zlib1g-dev \
      libstdc++6 \
      libpq-dev \
      libssl1.0-dev \
      pkg-config \
      cmake \
      make

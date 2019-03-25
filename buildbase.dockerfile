FROM golang:1.12 as healthcheck

ADD healthcheck.go .
RUN go get gopkg.in/ini.v1
RUN CGO_ENABLED=0 GOOS=linux go build -o /usr/local/bin/healthcheck ./healthcheck.go

#
#
#

FROM ubuntu:18.04

COPY --from=healthcheck /usr/local/bin/healthcheck /usr/local/bin/healthcheck
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

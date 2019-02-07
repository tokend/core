FROM golang:1.11-stretch as healthcheck_builder
ADD healthcheck.go .
RUN true \
    && go get gopkg.in/ini.v1 \
    && go build -o /healthcheck ./healthcheck.go \
    && true

FROM registry.gitlab.com/tokend/core/buildbase:latest

COPY --from=healthcheck_builder /healthcheck /healthcheck

ARG RSA_KEY
WORKDIR /build
COPY . $PWD

RUN true \
 && mkdir -p ~/.ssh \
 && echo "$RSA_KEY" > ~/.ssh/id_rsa \
 && chmod 600 ~/.ssh/id_rsa \
 && echo "Host *\n\tStrictHostKeyChecking no\n\n" > ~/.ssh/config \
 && echo "Host gitlab\n\tHostName gitlab.com\n\tIdentityFile ~/.ssh/id_rsa\n\tUser git\n" >> ~/.ssh/config \
 && git config --global url.ssh://git@gitlab.com/.insteadOf https://gitlab.com/ \
 && GIT_SSH_COMMAND="ssh -i ~/.ssh/id_rsa" git submodule update --init \
 && cmake CMakeLists.txt -DPostgreSQL_INCLUDE_DIRS=/usr/include/postgresql/ -DPostgreSQL_LIBRARIES=/usr/lib/x86_64-linux-gnu/libpq.so \
 && make -j2 \
 && rm ~/.ssh/id_rsa

FROM ubuntu:18.04

RUN true \
 && apt-get update \
 && apt-get install -y --no-install-recommends libpq5 libssl1.0.2 awscli s3cmd libcurl4 curl \
 && rm -rf /var/lib/apt/lists/* /var/log/*.log /var/log/*/*.log \
 && mkdir /data

VOLUME /data

COPY --from=corebuild /build/src/core /usr/local/bin/core
COPY --from=corebuild /usr/local/bin/healthcheck /usr/local/bin/healthcheck
COPY entrypoint.sh /usr/local/bin/entrypoint.sh

ENV CONFIG=/config.ini

HEALTHCHECK --interval=30s --timeout=3s --start-period=30s --retries=3 CMD ["healthcheck"]

ENTRYPOINT [ "entrypoint.sh" ]


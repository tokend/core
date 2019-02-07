FROM registry.gitlab.com/tokend/deployment/postgres-ubuntu:9.6

RUN true \
 && apt-get update \
 && apt-get install -y --no-install-recommends libpq5 libssl1.0.0 awscli s3cmd dumb-init \
 && rm -rf /var/lib/apt/lists/* /var/log/*.log /var/log/*/*.log \
 && mkdir /data

VOLUME /data

COPY --from=corebuild /build/src/core /usr/local/bin/core
COPY --from=corebuild /healthcheck /healthcheck
COPY entrypoint.sh /usr/local/bin/core-entrypoint.sh
COPY pg-entrypoint.sh /usr/local/bin/entrypoint.sh
RUN true \
 && mv /usr/bin/entrypoint.sh /usr/local/bin/pg-entrypoint.sh \
 && chmod +x /usr/local/bin/core-entrypoint.sh \
 && chmod +x /usr/local/bin/entrypoint.sh \ 
 && chmod +x /usr/local/bin/pg-entrypoint.sh

HEALTHCHECK --interval=5m --timeout=3s --start-period=30s --retries=3 CMD ["/healthcheck"]

ENTRYPOINT ["entrypoint.sh"]



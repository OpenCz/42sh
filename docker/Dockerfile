FROM alpine
WORKDIR /app
RUN apk add --no-cache clang20 git make gcovr sudo \
	&& git clone --depth 1 --single-branch https://github.com/lukas-sgx/Epifaster.git \
	&& cd /app/Epifaster \
	&& ./setup.sh \
	&& apk del git sudo \
	&& rm -rf /app/Epifaster/.git /var/cache/apk/*
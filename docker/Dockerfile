FROM alpine
LABEL maintainer="Lukas Soigneux <lukas.soigneux@epitech.eu>"

WORKDIR /app
RUN apk add --no-cache clang20 clang20-rtlib git make gcovr build-base cmake meson ninja libffi-dev libgit2-dev bash \
	&& git clone --depth 1 --single-branch https://github.com/lukas-sgx/Epifaster.git
RUN git clone --recursive https://github.com/Snaipe/Criterion

WORKDIR /app/Criterion
RUN meson setup build && \
	ninja -C build && \
	ninja -C build install && \
	mv /usr/local/include/criterion /usr/include/ && \
	ldconfig /usr/lib

WORKDIR /app/Epifaster
RUN ln -s /usr/bin/clang-20 /usr/bin/clang

RUN mkdir -p /usr/lib/epiclang/ && \
    cp -r ./plugins /usr/lib/epiclang/ && \
    make install && \
    chmod +x epiclang && \
    cp epiclang /usr/bin/epiclang

RUN apk del git build-base meson ninja \
	&& rm -rf /app/Epifaster/.git /var/cache/apk/* /app/Criterion

COPY banana-check-repo.sh /usr/bin/banana-check-repo
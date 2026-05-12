#!/bin/sh

apk add --no-cache clang20 clang20-rtlib git make build-base cmake meson ninja libffi-dev libgit2-dev cargo

git clone https://github.com/lukas-sgx/Epifaster.git
git clone https://github.com/Snaipe/Criterion

cd /app/Criterion
meson setup build
ninja -C build
ninja -C build install
mv /usr/local/include/criterion /usr/include/
ldconfig /usr/lib

cd /app/Epifaster
ln -s /usr/bin/clang-20 /usr/bin/clang
./setup.sh

cd /app
mv banana-check-repo.sh /github/home/.local/bin/banana-check-repo

apk del git build-base meson ninja cargo
rm -rf /app/Epifaster/.git /var/cache/apk/* /app/Criterion $HOME/.cargo $HOME/.rustup /root/.cargo /root/.rustup
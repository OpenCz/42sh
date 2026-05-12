FROM alpine
LABEL maintainer="Lukas Soigneux <lukas.soigneux@epitech.eu>"

WORKDIR /app

ENV HOME=/github/home
ENV PATH=/github/home/.local/bin:$PATH

COPY dependencies.sh /app/ 
COPY banana-check-repo.sh /app/

RUN ./dependencies.sh
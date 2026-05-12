FROM alpine
LABEL maintainer="Lukas Soigneux <lukas.soigneux@epitech.eu>"

WORKDIR /app
ENV PATH=/root/.local/bin:$PATH
COPY dependencies.sh /app/ 
RUN ./dependencies.sh
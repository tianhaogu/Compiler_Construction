FROM ubuntu:latest
RUN apt-get update -y \
  && apt-get install -y  build-essential bison flex\
  && rm -rf /var/lib/apt/lists/*
VOLUME /home
WORKDIR /home
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update --fix-missing && apt-get install -y \
      git \
      build-essential \
      wget \
      autoconf \
      m4 \
      libtool \
      g++ \
      cmake \
      libgmp-dev \
      libssl-dev \
      bison \
      flex \
      unzip \
      libglib2.0-dev \
      doxygen \
      python3-setuptools \
      python3-dev \
      python3-pip \
      nodejs \
      npm \
      libboost-all-dev=1.71.0.0ubuntu2 \
      libgtest-dev \
      nano \
      sudo 
#    && ldconfig \
#    && rm -rf /var/lib/apt/lists/*

# Copy patches and scripts
COPY patches/openabe.patch /patches/openabe.patch
COPY scripts/ /scripts/

# Clone repository, apply patch and build
RUN git clone https://github.com/zeutro/openabe.git /openabe
WORKDIR /openabe
RUN git checkout b8f9d3c \
    && git apply /patches/openabe.patch \
    && bash -c ". ./env && make && make install" \
    && ldconfig

# Compile and run benchmarks
WORKDIR /scripts
RUN chmod +x compile_bench.sh bench.sh \
    && ./compile_bench.sh

RUN ./bench.sh
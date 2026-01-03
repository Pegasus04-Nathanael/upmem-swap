FROM ubuntu:20.04

RUN apt update && \
    DEBIAN_FRONTEND=noninteractive apt install -y \
    software-properties-common \
    wget \
    libedit-dev \
    libxml2 \
    python3.8-dev \
    libelf-dev \
    libnuma-dev \
    python3-pip \
    pkg-config \
    git \
    vim \
    build-essential && \
    pip3 install six && \
    wget http://sdk-releases.upmem.com/2021.4.0/ubuntu_20.04/upmem-2021.4.0-Linux-x86_64.tar.gz && \
    tar xf upmem-2021.4.0-Linux-x86_64.tar.gz && \
    rm upmem-2021.4.0-Linux-x86_64.tar.gz && \
    mv upmem-2021.4.0-Linux-x86_64/ /upmem-sdk

# Source UPMEM env automatically
RUN echo 'source /upmem-sdk/upmem_env.sh simulator' >> /root/.bashrc

WORKDIR /workspace

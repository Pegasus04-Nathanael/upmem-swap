FROM ubuntu:20.04

RUN apt update && \
    DEBIAN_FRONTEND=noninteractive apt install -y \
    software-properties-common \
    wget \
    curl \
    git \
    libedit-dev \
    libxml2 \
    python3.8-dev \
    libelf-dev \
    libnuma-dev \
    python3-pip \
    pkg-config \
    make \
    gcc \
    g++ && \
    pip3 install six && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

# Install UPMEM SDK from community archive
# Source: https://github.com/kagandikmen/upmem-sdk
RUN apt-get update && \
    apt-get install -y git git-lfs && \
    rm -rf /var/lib/apt/lists/* && \
    mkdir -p /opt && \
    cd /opt && \
    git clone https://github.com/kagandikmen/upmem-sdk.git upmem-sdk-archive && \
    cd upmem-sdk-archive && \
    git lfs install && \
    git lfs pull && \
    cd /opt/upmem-sdk-archive/2025.1.0/ubuntu-20.04 && \
    tar xzf upmem-2025.1.0-Linux-x86_64.tar.gz && \
    mv upmem-2025.1.0-Linux-x86_64 /opt/upmem-sdk-2025.1.0 && \
    rm -rf /opt/upmem-sdk-archive && \
    echo "✓ UPMEM SDK 2025.1.0 installed successfully"

# Set environment for UPMEM SDK
ENV UPMEM_HOME=/opt/upmem-sdk-2025.1.0
ENV PATH="${UPMEM_HOME}/bin:${PATH}"

# Clone UPMEM demo examples
RUN cd /opt && \
    git clone https://github.com/upmem/dpu_demo.git dpu_demo

WORKDIR /workspaces/upmem-swap

CMD bash

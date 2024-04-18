FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    python3 \
    python3-dev \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

ARG BUILD_TESTS=OFF
ARG BUILD_PYTHON=OFF
RUN if [ "$BUILD_PYTHON" = "ON" ]; then \
        cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DBUILD_PYTHON=ON -DBUILD_TESTS=$BUILD_TESTS && cmake --build build -j8; \
    elif [ "$BUILD_TESTS" = "ON" ]; then \
        cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DBUILD_TESTS=ON && cmake --build build -j8; \
    else \
        cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && cmake --build build -j8; \
    fi

RUN chmod +x ./build/gRPCNvidia

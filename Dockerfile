FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

ARG BUILD_TESTS=OFF
RUN if [ "$BUILD_TESTS" = "ON" ]; then \
        cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DBUILD_TESTS=ON && cmake --build build -j8; \
    else \
        cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && cmake --build build -j8; \
    fi

RUN chmod +x ./build/gRPCNvidia

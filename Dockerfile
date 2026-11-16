# syntax=docker/dockerfile:1

ARG UBUNTU_VERSION=24.04
ARG LIBSTDCXX_VERSION=15
ARG LLVM_VERSION=23

# ------------------------------------------------------------------------------
# Base
# ------------------------------------------------------------------------------
FROM ubuntu:${UBUNTU_VERSION} AS base

ARG DEBIAN_FRONTEND=noninteractive

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN apt-get update \
  && apt-get install -y --no-install-recommends \
  ca-certificates \
  cmake \
  curl \
  file \
  git \
  gnupg \
  make \
  ninja-build \
  python3 \
  && rm -rf /var/lib/apt/lists/*

RUN git config --system --add safe.directory '*'

# ------------------------------------------------------------------------------
# Toolchain
# ------------------------------------------------------------------------------
FROM base AS toolchain

ARG DEBIAN_FRONTEND=noninteractive
ARG LIBSTDCXX_VERSION
ARG LLVM_VERSION

# Newer libstdc++ (C++23 support) from the ubuntu-toolchain-r test PPA. Only the
# standard library is installed, not the GCC compiler; Clang picks it up.
RUN . /etc/os-release \
  && install -d -m 0755 /etc/apt/keyrings \
  && curl -fsSL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x60C317803A41BA51845E371A1E9377A2BA9EF27F" \
  -o /etc/apt/keyrings/ubuntu-toolchain-r.asc \
  && printf '%s\n' \
  "Types: deb" \
  "URIs: https://ppa.launchpadcontent.net/ubuntu-toolchain-r/test/ubuntu/" \
  "Suites: ${VERSION_CODENAME}" \
  "Components: main" \
  "Signed-By: /etc/apt/keyrings/ubuntu-toolchain-r.asc" \
  > /etc/apt/sources.list.d/ubuntu-toolchain-r.sources \
  && apt-get update \
  && apt-get install -y --no-install-recommends \
  "libstdc++-${LIBSTDCXX_VERSION}-dev" \
  && rm -rf /var/lib/apt/lists/*

# LLVM/Clang from apt.llvm.org
RUN . /etc/os-release \
  && curl -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key -o /etc/apt/keyrings/llvm.asc \
  && printf '%s\n' \
  "Types: deb" \
  "URIs: https://apt.llvm.org/${VERSION_CODENAME}/" \
  "Suites: llvm-toolchain-${VERSION_CODENAME}-${LLVM_VERSION}" \
  "Components: main" \
  "Signed-By: /etc/apt/keyrings/llvm.asc" \
  > /etc/apt/sources.list.d/llvm.sources \
  && apt-get update \
  && apt-get install -y --no-install-recommends \
  "clang-${LLVM_VERSION}" \
  "clang-format-${LLVM_VERSION}" \
  "clang-tidy-${LLVM_VERSION}" \
  "clang-tools-${LLVM_VERSION}" \
  "clangd-${LLVM_VERSION}" \
  "libclang-rt-${LLVM_VERSION}-dev" \
  "lld-${LLVM_VERSION}" \
  "llvm-${LLVM_VERSION}" \
  && rm -rf /var/lib/apt/lists/*

ENV PATH="/usr/lib/llvm-${LLVM_VERSION}/bin:${PATH}"

RUN update-alternatives --install /usr/bin/cc cc "/usr/lib/llvm-${LLVM_VERSION}/bin/clang" 100 \
  && update-alternatives --install /usr/bin/c++ c++ "/usr/lib/llvm-${LLVM_VERSION}/bin/clang++" 100

# ------------------------------------------------------------------------------
# CI
# ------------------------------------------------------------------------------
FROM toolchain AS ci

ARG LIBSTDCXX_VERSION
ARG LLVM_VERSION

LABEL org.opencontainers.image.title="Aegis CI" \
  org.opencontainers.image.description="Build environment for Aegis (LLVM ${LLVM_VERSION}, libstdc++ ${LIBSTDCXX_VERSION})" \
  org.opencontainers.image.source="https://github.com/Aegis-Origin/Aegis" \
  org.opencontainers.image.licenses="Apache-2.0"

ENV CC=clang \
  CXX=clang++ \
  AG_LLVM_VERSION="${LLVM_VERSION}" \
  AG_LIBSTDCXX_VERSION="${LIBSTDCXX_VERSION}"

WORKDIR /workspace

CMD ["/bin/bash"]

FROM centos:stream9

#Install deps
RUN dnf update -y && \
    dnf install -y epel-release && \
    dnf update -y && \
    dnf install -y --best --nodocs --setopt install_weak_deps=false git \
    gcc \
    g++ \
    cmake \
    make \
    gdb \
    redhat-rpm-config \
    gperf \
    gperftools-libs \
    gperftools-devel \
    curl-devel \
    thrift \
    thrift-devel \
    abseil-cpp-devel \
    bash-completion \
    vim

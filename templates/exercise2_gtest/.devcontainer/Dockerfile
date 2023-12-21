FROM gcc:11

ENV REFRESHED_AT 2021-10-19

RUN apt-get update && apt-get install -y google-mock \
      git \
      cmake \
      cppcheck \
      valgrind \
      libgtest-dev \
      ninja-build \
      python3-pip \
      bzr \
      lib32z1 \
      gdb \
      && pip3 install meson \
      && pip3 install gcovr

RUN adduser feabhas

WORKDIR /home/feabhas
FROM gcc:11.3 as build_scanner

RUN apt update && \
    apt install -y \
      python3-pip \
      cmake \
    && \
    pip3 install conan==1.*

COPY conanfile.txt /app/
RUN mkdir /app/build-release && cd /app/build-release && \
        conan install .. --build=missing -s build_type=Release -s compiler.libcxx=libstdc++11

COPY ./src /app/src
COPY ./tests /app/tests
COPY CMakeLists.txt /app/
COPY config.json /app/

RUN cd /app/build-release && \
        cmake .. -DCMAKE_BUILD_TYPE=Release && \
        cmake --build . --target all

FROM ubuntu:22.04 as run_scanner

COPY --from=build_scanner /app/build-release/bin/trivial_port_scanner /app/bin/
COPY --from=build_scanner /app/build-release/bin/parser_test /app/bin/
COPY --from=build_scanner /app/tests/test_configs/ /app/tests/test_configs/
COPY config.json /app/config.json

ENTRYPOINT ["bash", "-c", "cd /app/bin && exec bash"]
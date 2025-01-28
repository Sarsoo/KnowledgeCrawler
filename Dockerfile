FROM alpine:latest as build
RUN apk add cmake make clang build-base llvm-static llvm-dev clang-static clang-dev openssl-dev git

WORKDIR /kc
COPY . ./

RUN mkdir build && cd build && ../cbuildrel

FROM alpine:latest as run

RUN apk add libstdc++

COPY --from=build /kc/build/kc /kc/kc
RUN mkdir /kc/log

WORKDIR /kc

ENTRYPOINT ["/kc/kc"]
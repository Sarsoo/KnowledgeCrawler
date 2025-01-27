FROM alpine:latest as build
RUN apk add cmake make clang build-base llvm-static llvm-dev clang-static clang-dev

WORKDIR /kc
COPY . ./

RUN mkdir build && cd build && ../cbuild

FROM alpine:latest as run
COPY --from=build /kc/build/kc /kc/kc

WORKDIR /kc

ENTRYPOINT ["kc"]
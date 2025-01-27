FROM alpine:latest as build
RUN apk add make cmake

WORKDIR /kc
COPY . ./

RUN mkdir build && cd build && ../cbuild

FROM alpine:latest as run
COPY --from=build /kc/build/kc /kc/kc

WORKDIR /kc

ENTRYPOINT ["kc"]
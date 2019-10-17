FROM gcc:7.4
COPY ./ /usr/src/dsmr-parser-api
WORKDIR /usr/src/dsmr-parser-api
RUN cmake . && make
CMD ["./dsmr-parser-api"]

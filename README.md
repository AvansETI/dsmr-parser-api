# DSMR parser API

This project implements a micro service to parse Dutch Smart Meter
datagrams. Both the v2 and v4 datagrams are supported. This project
supports the following operating systems:

* Debian 9
* Ubuntu 18.04
* Windows (*using WSL*)

## Dependencies
This project has the following dependencies:

* Boost
    * system
    * thread
    * log
    * chrono
* cpprestsdk
* libdsmr

All depencies have to be preinstalled on both the target machine
and the build machine. Standalone deployments are currently not
supported.

## Endpoints

The following endpoints are published by this micro service:

`POST http://localhost:5000/parser`

Expected body:

```json
{
  "datagram": "<datagram>"
}
```

`GET http://localhost:5000/parser`

## Compiling
Follow the following tutorial in order to succesfully build `dsmr-parser-api`.

### Boost
Install the required boost libraries:

`$ sudo apt-get install libboost-log-dev libboost-thread-dev libboost-chrono-dev libboost-system-dev`

### libdsmr
Start by cloning the DSMR parser library needs to be compiled from source.

```bash
$ git clone --recursive https://github.com/AvansETI/libdsmr.git
$ cd libdsmr
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

### cpprestsdk
The CPP rest SDK can be installed from the Debian/Ubuntu package libraries:

`$ sudo apt-get install libcpprest-sdk`

### Building the micro service
Build the micro service using the following steps:

```bash
$ git clone https://github.com/AvansETI/dsmr-parser-api.git
$ cd dsmr-parser-api
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./dsmr-parser-api
```

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

Example response (`HTTP 200`):
```json
{
  "electricity_tariff":"0001",
  "energy_delivered_tariff1":185,
  "energy_delivered_tariff2":84,
  "energy_returned_tariff1":13,
  "energy_returned_tariff2":19,
  "equipment_id":"205C4D246333034353537383234323121",
  "gas_device_type":3,
  "gas_equipment_id":"3238313031453631373038389930337131",
  "identification":"KMP5ZABF001587315111",
  "p1_version":"",
  "power_delivered":0,
  "power_delivered_l1":156561,
  "power_delivered_l2":3355452,
  "power_delivered_l3":0,
  "power_returned":0,
  "power_returned_l1":156560,
  "power_returned_l2":239516,
  "power_returned_l3":156560,
  "timestamp":""
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

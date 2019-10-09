cmake_minimum_required(VERSION 3.7)
project(dsmr-parser-api)

set (CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexceptions -frtti")
set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)

find_package(cpprestsdk REQUIRED NAMES cpprestsdk cpprest)
find_package(Boost REQUIRED system thread log chrono)
find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(dsmr-parser-api
	source/network_utils.cpp
	source/main.cpp
	source/basic_controller.cpp
	source/parser_controller.cpp
)

target_link_libraries(dsmr-parser-api PRIVATE dsmr cpprestsdk::cpprest ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES})

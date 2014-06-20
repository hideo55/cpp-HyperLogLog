SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3")

SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -D_DEBUG")

SET(CMAKE_BUILD_TYPE Release)

PROJECT(HyperLogLog CXX)

SET(serial "1.0.0")

SET(soserial "1")

INCLUDE_DIRECTORIES(include extlib/igloo extlib/igloo-TapTestListener)

# Testing
ENABLE_TESTING()

ADD_EXECUTABLE(t/test_hyperloglog t/HyperLogLogTest.cpp)

ADD_TEST(NAME test_hyperloglog COMMAND ./t/test_hyperloglog)


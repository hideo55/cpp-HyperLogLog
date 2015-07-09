SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3")

SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -D_DEBUG")

SET(CMAKE_BUILD_TYPE Release)

SET(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)

PROJECT(HyperLogLog CXX)

SET(serial "1.0.0")

SET(soserial "1")

INCLUDE_DIRECTORIES(include extlib/igloo extlib/igloo-TapTestListener)

# Testing
ENABLE_TESTING()

ADD_EXECUTABLE(test_hyperloglog t/HyperLogLogTest.cpp)
ADD_EXECUTABLE(test_hyperloglog_hip t/HyperLogLogHIPTest.cpp)

ADD_TEST(NAME test_hyperloglog COMMAND test_hyperloglog)
ADD_TEST(NAME test_hyperloglog_hip COMMAND test_hyperloglog_hip)


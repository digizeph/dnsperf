cmake_minimum_required(VERSION 3.6)
project(dnsperf)

file(GLOB_RECURSE MainSources "src/*.cpp")
file(GLOB_RECURSE MainHeaders "src/*.h")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread")

#include_directories(src)

add_executable(dnsperf ${MainSources})
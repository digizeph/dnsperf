cmake_minimum_required(VERSION 3.5)
project(dnsperf)

set (CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE MainSources "src/*.cpp")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lldns -lpthread -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include/mysql++ -I/usr/local/include/mysql -I/usr/include/mysql++ -I/usr/include/mysql")

find_package (Threads)

#add_executable(dnsperf dnsperf)
add_executable(dnsperf ${MainSources} )
target_link_libraries (dnsperf ${CMAKE_THREAD_LIBS_INIT} ldns mysqlpp)

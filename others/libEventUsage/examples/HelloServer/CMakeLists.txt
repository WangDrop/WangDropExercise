cmake_minimum_required(VERSION 3.5)
project(HelloServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES helloServer.c helloClient.c TimerTest/timer.c.cpp)
add_executable(HelloServer ${SOURCE_FILES})
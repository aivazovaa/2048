cmake_minimum_required(VERSION 3.10)
project(Game2048)

set(CMAKE_CXX_STANDARD 17)


include_directories(src include)


file(GLOB SOURCE_FILES
    src/*.cpp
)

add_executable(Game2048 ${SOURCE_FILES})


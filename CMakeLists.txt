cmake_minimum_required(VERSION 3.24)
project(CaRinge)

set(CMAKE_CXX_STANDARD 17)

add_executable(CaRinge main.cpp)

include_directories(/usr/local/include)

find_package(SFML 2.6 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(CaRinge sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
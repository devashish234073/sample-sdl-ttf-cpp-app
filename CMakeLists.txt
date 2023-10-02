cmake_minimum_required(VERSION 3.12)
project(SDL2_TTF_Example)

set(CMAKE_CXX_STANDARD 14)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Specify SDL2_ttf include directories and libraries manually
set(SDL2_ttf_INCLUDE_DIRS "/usr/include/SDL2")
set(SDL2_ttf_LIBRARIES "-lSDL2_ttf")

add_executable(SDL2_TTF_Example main.cpp)

target_include_directories(SDL2_TTF_Example PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
target_link_libraries(SDL2_TTF_Example ${SDL2_LIBRARIES} ${SDL2_ttf_LIBRARIES})

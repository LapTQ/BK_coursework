cmake_minimum_required(VERSION 3.22)
project(helloworldmpi C)

set(CMAKE_C_STANDARD 99)

find_package(MPI REQUIRED)

add_executable(helloworldmpi main.c)
target_link_libraries(helloworldmpi PUBLIC MPI::MPI_C)


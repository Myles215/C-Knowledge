cmake_minimum_required (VERSION 3.5)
project (Bench)

set(BENCHMARK_ENABLE_TESTING off)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

include(FetchContent)
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG main
)
FetchContent_MakeAvailable(googletest benchmark)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (CMAKE_CXX_FLAGS "-O3 -Wall")

add_subdirectory(DataStructures)
add_subdirectory(Functions)
add_subdirectory(Types)
add_subdirectory(Polymorphism)
add_subdirectory(IO)
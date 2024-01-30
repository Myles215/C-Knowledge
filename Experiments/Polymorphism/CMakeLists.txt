include_directories (${CMAKE_SOURCE_DIR}/src)

add_executable(
  StaticVsDynamic
  StaticVsDynamic.cpp
)

target_link_libraries(
  StaticVsDynamic
  benchmark::benchmark
)
include_directories (${CMAKE_SOURCE_DIR}/src)

add_executable(
  CvsCa
  CvsC&.cpp
)

target_link_libraries(
  CvsCa
  benchmark::benchmark
)
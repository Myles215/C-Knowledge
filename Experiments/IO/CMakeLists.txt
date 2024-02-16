include_directories (${CMAKE_SOURCE_DIR}/src)

add_executable(
  CvsCPP
  CvsCPP.cpp
)

target_link_libraries(
  CvsCPP
  benchmark::benchmark
)
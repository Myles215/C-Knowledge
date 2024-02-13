include_directories (${CMAKE_SOURCE_DIR}/src)

add_executable(
  CvsCa
  CvsC&.cpp
)

target_link_libraries(
  CvsCa
  benchmark::benchmark
)

add_executable(
  HeapVsStackVec
  HeapVsStackVec.cpp
)

target_link_libraries(
  HeapVsStackVec
  benchmark::benchmark
)

add_executable(
  HeapVsStack
  HeapVsStack.cpp
)

target_link_libraries(
  HeapVsStack
  benchmark::benchmark
)
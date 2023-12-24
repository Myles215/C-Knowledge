include_directories (${CMAKE_SOURCE_DIR}/src)

add_executable(
  ListVsVector
  ListVsVector.cpp
)

target_link_libraries(
  ListVsVector
  benchmark::benchmark
)

add_executable(
  SetVsVector
  SetVsVector.cpp
)

target_link_libraries(
  SetVsVector
  benchmark::benchmark
)

add_executable(
  MapVsVector
  MapVsVectorStructs.cpp
)

target_link_libraries(
  MapVsVector
  benchmark::benchmark
)

add_executable(
  ListVsVectorDelete
  ListVsVectorDelete.cpp
)

target_link_libraries(
  ListVsVectorDelete
  benchmark::benchmark
)
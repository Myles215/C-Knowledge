include_directories (${CMAKE_SOURCE_DIR}/src)

add_executable(
  TemplateMethod
  TemplateMethod.cpp
)

target_link_libraries(
  TemplateMethod
  benchmark::benchmark
)

add_executable(
  Coroutine
  Coroutine.cpp
)

target_link_libraries(
  Coroutine
  benchmark::benchmark
)
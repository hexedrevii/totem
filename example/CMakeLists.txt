cmake_minimum_required(VERSION 3.16)

project(totem_example LANGUAGES CXX)
add_executable(totem_example
  main.cpp
)

target_link_libraries(totem_example PRIVATE
  totem::totem
)

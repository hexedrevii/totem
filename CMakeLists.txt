cmake_minimum_required(VERSION 3.16)

option(TOTEM_COMPILE_EXAMPLE "Compile the transform example." OFF)

set(CMAKE_CXX_STANDARD 20)

project(totem LANGUAGES CXX DESCRIPTION "Small ECF Library.")

add_library(${PROJECT_NAME} STATIC
  src/object.cpp
  include/totem/signal.hpp
  include/totem/object.hpp
  include/totem/component.hpp

  include/totem/totem.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  include
)

add_library(totem::totem ALIAS totem)

if (TOTEM_COMPILE_EXAMPLE)
  add_subdirectory(example)
endif()

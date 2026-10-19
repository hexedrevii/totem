# Totem

A simple, Unity-like Entity-Component framework for C++20.

Does not come with components! You have to do those yourself. ;)

## Example
An example on how to build a basic component and scene can be found in the `example` directory.

## Docs
The headers in `include/totem` should examplain most of what this simple library does.

## Using in your project
To easily link the library, you can use FetchContent for CMake (Available for CMake 3.26 and above)

```bash
cmake_minimum_required(VERSION 3.26)

# ...

include(FetchContent)

find_package(totem QUIET)
if (NOT totem_FOUND)
  FetchContent_Declare(
    totem
    GIT_REPOSITORY https://github.com/hexedrevii/totem
    GIT_TAG main
    GIT_SHALLOW TRUE
  )

  FetchContent_MakeAvailable(totem)
endif()

# ...

target_link_libraries(${PROJECT_NAME} PRIVATE
  totem::totem
)
```

## LICENSE
GPL 3.0

# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(LIBGETTER_VERSION "0.0.0-alpha")

# Extract MAJOR.MINOR.PATCH from version
string(
  REGEX MATCH
  "([0-9])+\\.([0-9])+\\.([0-9])+"
  LIBGETTER_VERSION_SHORT ${LIBGETTER_VERSION}
)

set(LIBGETTER_VERSION_MAJOR ${CMAKE_MATCH_1})
set(LIBGETTER_VERSION_MINOR ${CMAKE_MATCH_2})
set(LIBGETTER_VERSION_PATCH ${CMAKE_MATCH_3})

project(libgetter VERSION ${LIBGETTER_VERSION_SHORT} LANGUAGES C CXX)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Builds shared version of libgetter and its dependencies")
option(LIBGETTER_BUILD_TESTS "Builds libgetter's tests" ON)

set(CMAKE_C_STANDARD 11) # TODO: convert project to be C89 compatible

if(BUILD_SHARED_LIBS)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON) # -fPIC is recommended while building shared libs
endif()

add_subdirectory(lib)
add_subdirectory(src)

if(LIBGETTER_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

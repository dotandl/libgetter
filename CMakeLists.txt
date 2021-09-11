# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

cmake_minimum_required(VERSION 3.12)

set(LIBGETTER_VERSION "0.0.0-alpha")

string(
  REGEX MATCH
  "([0-9])+\\.([0-9])+\\.([0-9])+"
  LIBGETTER_VERSION_SHORT ${LIBGETTER_VERSION}
)

set(LIBGETTER_VERSION_MAJOR ${CMAKE_MATCH_1})
set(LIBGETTER_VERSION_MINOR ${CMAKE_MATCH_2})
set(LIBGETTER_VERSION_PATCH ${CMAKE_MATCH_3})

project(libgetter VERSION ${LIBGETTER_VERSION_SHORT} LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11) # Required by GoogleTest

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)

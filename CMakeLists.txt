# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(libgetter_VERSION 0.0.0)

cmake_minimum_required(VERSION 3.10)
project(libgetter VERSION ${libgetter_VERSION} LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)

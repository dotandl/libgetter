# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

find_path(ZIP_INCLUDE zip.h)
find_library(ZIP_LIB zip)

if(NOT ZIP_INCLUDE OR NOT ZIP_LIB)
  message(FATAL_ERROR "Could not find libzip")
endif()

add_library(zip INTERFACE)
target_include_directories(zip INTERFACE ${ZIP_INCLUDE})
target_link_libraries(zip INTERFACE ${ZIP_LIB})

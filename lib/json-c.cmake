# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

find_path(JSONC_INCLUDE json-c/json.h)
find_library(JSONC_LIB json-c)

if(NOT JSONC_INCLUDE OR NOT JSONC_LIB)
  message(FATAL_ERROR "Could not find json-c")
endif()

add_library(json-c INTERFACE)
target_include_directories(json-c INTERFACE ${JSONC_INCLUDE})
target_link_libraries(json-c INTERFACE ${JSONC_LIB})

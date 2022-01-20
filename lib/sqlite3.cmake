# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021-2022 dotandl                          |
# +----------------------------------------------------------+

find_path(SQLITE3_INCLUDE sqlite3.h)
find_library(SQLITE3_LIB sqlite3)

if(NOT SQLITE3_INCLUDE OR NOT SQLITE3_LIB)
  message(FATAL_ERROR "Could not find sqlite3")
endif()

add_library(sqlite3 INTERFACE)
target_include_directories(sqlite3 INTERFACE ${SQLITE3_INCLUDE})
target_link_libraries(sqlite3 INTERFACE ${SQLITE3_LIB})

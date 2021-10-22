# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

find_path(PCRE2_INCLUDE pcre2.h)
find_library(PCRE2_LIB pcre2-8)

if(NOT PCRE2_INCLUDE OR NOT PCRE2_LIB)
  message(FATAL_ERROR "Could not find pcre2 library")
endif()

add_library(pcre2 INTERFACE)
target_include_directories(pcre2 INTERFACE ${PCRE2_INCLUDE})
target_link_libraries(pcre2 INTERFACE ${PCRE2_LIB})

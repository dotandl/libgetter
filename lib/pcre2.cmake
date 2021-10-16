# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(PCRE2_BUILD_TESTS OFF)

add_subdirectory(pcre2)

set(PCRE2_TARGETS
  pcre2-8-static
  pcre2-8-shared
)

foreach(TARGET ${PCRE2_TARGETS})
  target_include_directories(${TARGET}
    PUBLIC "${PCRE2_BINARY_DIR}" # for pcre2.h (generated from pcre2.h.in)
    PUBLIC "${PCRE2_SOURCE_DIR}/src" # for other internal .h files
  )
endforeach()

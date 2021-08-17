# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

add_library(tiny-regex-c STATIC tiny-regex-c/re.c tiny-regex-c/re.h)
target_include_directories(tiny-regex-c PUBLIC ${PROJECT_SOURCE_DIR}/lib/tiny-regex-c)

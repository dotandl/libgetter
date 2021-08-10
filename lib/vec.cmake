# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

add_library(vec STATIC vec/src/vec.c vec/src/vec.h)
target_include_directories(vec PUBLIC ${PROJECT_SOURCE_DIR}/lib/vec/src)

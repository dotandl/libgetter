# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

add_library(c-vector INTERFACE)
target_include_directories(c-vector INTERFACE ${PROJECT_SOURCE_DIR}/lib/c-vector)

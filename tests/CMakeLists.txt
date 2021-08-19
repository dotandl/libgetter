# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(SOURCE_FILES
  box/info.cpp
  release/info.cpp
  release/release.cpp
  release/version.cpp
  types/pkvf.cpp
  types/vector.cpp
)

add_executable(libgetter_test ${SOURCE_FILES})
target_link_libraries(libgetter_test libgetter_static gtest_main)

include(GoogleTest)
gtest_discover_tests(libgetter_test)

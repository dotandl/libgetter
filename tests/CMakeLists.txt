# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(CMAKE_CXX_STANDARD 11)

set(LIBGETTER_TESTS_SOURCES
  box/info.cpp
  box/box.cpp
  release/info.cpp
  release/release.cpp
  release/version.cpp
  types/pkvf.cpp
  files/zip/box_info.cpp
)

add_executable(libgetter_test ${LIBGETTER_TESTS_SOURCES})
target_link_libraries(libgetter_test getter gtest_main)
target_compile_options(libgetter_test PRIVATE "-fpermissive")

target_compile_definitions(libgetter_test
  PRIVATE GTT_TESTS_DIR="${PROJECT_SOURCE_DIR}/tests"
)

include(GoogleTest)
gtest_discover_tests(libgetter_test)

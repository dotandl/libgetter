# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(LIBGETTER_TESTS_SOURCES
  # Tests
  box/info.cpp
  box/box.cpp
  release/info.cpp
  release/release.cpp
  release/version.cpp
  types/pkvf.cpp
  tools/tmp.cpp
  files/zip/box_info.cpp
  files/zip/box.cpp

  # Tools
  cppvector.c
)

add_executable(libgetter_test ${LIBGETTER_TESTS_SOURCES})
target_link_libraries(libgetter_test getter gtest_main)

set_target_properties(libgetter_test PROPERTIES
  C_STANDARD 90
  CXX_STANDARD 17 # for std::filesystem
)

target_compile_definitions(libgetter_test
  PRIVATE GTT_TESTS_DIR="${PROJECT_SOURCE_DIR}/tests"
)

include(GoogleTest)
gtest_discover_tests(libgetter_test)

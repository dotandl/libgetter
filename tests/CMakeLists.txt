# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(LIBGETTER_TESTS_SOURCES
  box/info.cpp
  box/box.cpp
  release/info.cpp
  release/release.cpp
  release/version.cpp
  release/extracted_release.cpp
  tools/tmp.cpp
  files/zip/box_info.cpp
  files/zip/box.cpp
  files/zip/release_extract.cpp
  files/zip/package.cpp
  db/init.cpp
  script/script_runner.cpp
)

# TODO: files/zip/release_info test

# Platform-specific source files
if(WIN32)
  list(APPEND LIBGETTER_TESTS_SOURCES
    script/runners/cmd.cpp
  )
else()
  list(APPEND LIBGETTER_TESTS_SOURCES
    script/runners/sh.cpp
  )
endif()

add_executable(libgetter_test ${LIBGETTER_TESTS_SOURCES})
target_link_libraries(libgetter_test getter gtest_main)

set_target_properties(libgetter_test PROPERTIES
  # For Windows: Test executable has to be in the same directory as DLL is
  RUNTIME_OUTPUT_DIRECTORY ${LIBGETTER_OUTDIR}
  CXX_STANDARD 17 # for std::filesystem
)

target_compile_definitions(libgetter_test
  PRIVATE GTT_TESTS_DIR="${PROJECT_SOURCE_DIR}/tests"
)

include(GoogleTest)
gtest_discover_tests(libgetter_test)

# +----------------------------------------------------------+
# | libgetter - part of Getter Package Manager               |
# | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
# |                                                          |
# | Copyright (C) 2021 dotandl                               |
# +----------------------------------------------------------+

set(SOURCE_FILES
  test.cpp
)

add_executable(libgetter_test ${SOURCE_FILES})
target_link_libraries(libgetter_test gtest_main)

include(GoogleTest)
gtest_discover_tests(libgetter_test)

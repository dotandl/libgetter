/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/tmp.h>
#include <getter/types/array.h>
#include <gtest/gtest.h>

#include <filesystem>

namespace fs = std::filesystem;

TEST(Tmp, CreatesTempDir) {
  char buf[128];
  gtt_mktmpdir(buf, arrlen(buf));

  ASSERT_TRUE(fs::exists(buf));
  ASSERT_TRUE(fs::is_directory(buf));

  fs::remove(buf);
}

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
#include <fstream>
#include <string>

using std::ofstream;
using std::string;
namespace fs = std::filesystem;

TEST(Tmp, CreatesTempDir) {
  char buf[128];
  gtt_mktmpdir(buf, arrlen(buf));

  ASSERT_TRUE(fs::exists(buf));
  ASSERT_TRUE(fs::is_directory(buf));

  fs::remove(buf);
}

TEST(Tmp, RemovesTempDir) {
  char buf[128];
  gtt_mktmpdir(buf, arrlen(buf));

  fs::create_directory(string(buf) + "/dir/");

  ofstream file1(string(buf) + "/file1.txt");
  file1 << "lorem ipsum dolor sit amet";
  file1.close();

  ofstream file2(string(buf) + "/dir/file2.txt");
  file2 << "lorem ipsum dolor sit amet";
  file2.close();

  gtt_rmtmpdir(buf);

  ASSERT_FALSE(fs::exists(buf));
}

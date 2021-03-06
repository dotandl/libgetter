/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/script/runners/sh.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

using std::string;
using std::stringstream;
using std::vector;
using testing::internal::CaptureStdout;
using testing::internal::GetCapturedStdout;

TEST(ShScriptRunner, RunsPrepareFunc) {
  CaptureStdout();

  int err =
      sh_sr.prepare(GTT_TESTS_DIR "/script/GetterScript.sh", GTT_TESTS_DIR);

  stringstream stdout_stream(GetCapturedStdout());
  string line;
  vector<string> lines;

  while (getline(stdout_stream, line)) {
    lines.push_back(line);
  }

  EXPECT_EQ(err, 2);
  EXPECT_STREQ(lines[0].c_str(), "prepare()");
  EXPECT_STREQ(lines[1].c_str(), GTT_TESTS_DIR);
}

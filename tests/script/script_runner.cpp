/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#include <getter/script/script_runner.h>
#include <gtest/gtest.h>

#ifdef _WIN32
#include <getter/script/runners/cmd.h>
#else
#include <getter/script/runners/sh.h>
#endif

TEST(ScriptRunner, FindsScriptRunnerBasingOnScriptFileExtension) {
  const char *script_file =
#ifdef _WIN32
      "GetterScript.cmd"
#else
      "GetterScript.sh"
#endif
      ;

  GttScriptRunner *expected_sr =
#ifdef _WIN32
      &cmd_sr
#else
      &sh_sr
#endif
      ;

  GttScriptRunner *sr = gtt_script_runner_get(script_file);

  // Pointers in this case should hold the same address
  EXPECT_EQ(expected_sr, sr);
}

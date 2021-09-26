/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/files/zip/box_info.h>
#include <getter/tools/error.h>
#include <gtest/gtest.h>

#include <string>

using std::string;

TEST(Zip, ReadsBoxInfoFile) {
  string file = string(GTT_TESTS_DIR) + "/res/ExampleBox.zip";
  GttBoxInfo *bi;

  bi = gtt_zip_read_box_info(file.c_str());

  ASSERT_TRUE(bi != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  EXPECT_STREQ(bi->name, "example-box");
  EXPECT_STREQ(bi->full_name, "Example Box");
  EXPECT_STREQ(bi->summary, "testtest");
  EXPECT_STREQ(bi->authors[0], "dotandl");
  EXPECT_STREQ(bi->license_name, "MIT");

  gtt_box_info_delete(bi);
}

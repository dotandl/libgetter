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

TEST(Zip, ReadsBoxInfoFile) {
  const char *file = GTT_TESTS_DIR "/ExampleBox.zip";

  zip_t *zip = zip_open(file, 0, NULL);
  ASSERT_TRUE(zip != NULL);

  GttBoxInfo *bi = gtt_zip_read_box_info(zip);

  ASSERT_TRUE(bi != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  EXPECT_STREQ(bi->name, "example-box");
  EXPECT_STREQ(bi->full_name, "Example Box");
  EXPECT_STREQ(bi->summary, "testtest");
  EXPECT_STREQ(bi->authors.arr[0], "dotandl");
  EXPECT_STREQ(bi->license_name, "MIT");

  gtt_box_info_delete(bi);
  zip_close(zip);
}

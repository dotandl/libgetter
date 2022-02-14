/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#include <getter/files/zip/release_info.h>
#include <getter/release/release.h>
#include <getter/tools/error.h>
#include <gtest/gtest.h>

TEST(Zip, ReadsReleaseInfo) {
  const char *file = GTT_TESTS_DIR "/ExampleBox.zip";

  zip_t *zip = zip_open(file, 0, NULL);
  ASSERT_TRUE(zip != NULL);

  GttRelease *release = gtt_release_new("win32", "x86_64", "v1.0.0");

  ASSERT_TRUE(release != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  GttReleaseInfo *ri = gtt_zip_read_release_info(zip, release);

  EXPECT_TRUE(ri != NULL);
  EXPECT_EQ(gtt_last_error.code, GTT_OK);
  EXPECT_STREQ(ri->script, "GetterScript.cmd");

  gtt_release_info_delete(ri);
  gtt_release_delete(release);
  zip_close(zip);
}

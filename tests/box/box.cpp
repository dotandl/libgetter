/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/box/box.h>
#include <getter/tools/error.h>
#include <getter/tools/platform.h>
#include <gtest/gtest.h>

extern "C" void gtt_mock_platform(const char *platform);
extern "C" void gtt_mock_arch(const char *arch);

TEST(Box, IsAbleToSearchForAppropriateRelease) {
  gtt_mock_platform("win32");
  gtt_mock_arch("x86_64");

  const char *json =
      "{"
      "  \"name\": \"test\","
      "  \"full_name\": \"Test Box\","
      "  \"summary\": \"Just a test box\","
      "  \"authors\": [\"Jimmy\"],"
      "  \"license_name\": \"MIT\""
      "}";

  GttPtrArr releases = gtt_ptr_arr_new(4);

  releases.arr[0] = gtt_release_new("win32", "x86_64", "v1.0.0");
  releases.arr[1] = gtt_release_new("darwin", "arm64", "v1.1.0");
  releases.arr[2] = gtt_release_new("linux", "x86", "v1.1.5");
  releases.arr[3] = gtt_release_new("win32", "x86", "v2.2.0");

  GttBoxInfo *bi = gtt_box_info_new_from_json(json);
  GttBox *box = gtt_box_new(bi, releases);

  GttRelease *release = gtt_box_get_appropriate_release(box);

  ASSERT_TRUE(release != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  EXPECT_STREQ(release->version, "v1.0.0");
  EXPECT_STREQ(release->platform, "win32");
  EXPECT_STREQ(release->arch, "x86_64");

  gtt_box_delete(box);
}

TEST(Box, IsAbleToSearchForRelease) {
  const char *json =
      "{"
      "  \"name\": \"test\","
      "  \"full_name\": \"Test Box\","
      "  \"summary\": \"Just a test box\","
      "  \"authors\": [\"Jimmy\"],"
      "  \"license_name\": \"MIT\""
      "}";

  GttPtrArr releases = gtt_ptr_arr_new(7);

  releases.arr[0] = gtt_release_new("win32", "x86_64", "v0.9.0");
  releases.arr[1] = gtt_release_new("win32", "x86_64", "v1.0.0");
  releases.arr[2] = gtt_release_new("darwin", "arm64", "v1.0.5");
  releases.arr[3] = gtt_release_new("darwin", "arm64", "v1.1.0");
  releases.arr[4] = gtt_release_new("linux", "x86", "v1.1.5");
  releases.arr[5] = gtt_release_new("win32", "x86", "v2.2.0");
  releases.arr[6] = gtt_release_new("darwin", "arm64", "v2.2.0");

  GttBoxInfo *bi = gtt_box_info_new_from_json(json);
  GttBox *box = gtt_box_new(bi, releases);

  GttRelease *release = gtt_box_get_release(box, "v1.1.0", "darwin", "arm64");

  ASSERT_TRUE(release != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  EXPECT_STREQ(release->version, "v1.1.0");
  EXPECT_STREQ(release->platform, "darwin");
  EXPECT_STREQ(release->arch, "arm64");

  gtt_box_delete(box);
}

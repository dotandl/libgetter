/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/release/info.h>
#include <getter/tools/error.h>
#include <gtest/gtest.h>

TEST(ReleaseInfo, CreatesFromJSONAllFields) {
  const char json[] =
      "{"
      "  \"script\": \"GetterReleaseScript.sh\","
      "  \"repository\": \"example/release\","

      "  \"license_name\": \"MIT\","
      "  \"license\": \"LICENSE.txt\","
      "  \"readme\": \"README.txt\","
      "  \"changelog\": \"CHANGELOG.txt\","

      "  \"dependencies\": [\"box1\", \"box2\"],"
      "  \"build_dependencies\": [\"box3\", \"box4\", \"box5\"],"
      "  \"optional_dependencies\": [\"box6\"],"
      "  \"conflicts\": [\"box7\", \"box8\"],"
      "  \"replaces\": [\"box9\", \"box10\"]"
      "}";

  GttReleaseInfo *ri = gtt_release_info_new_from_json(json);

  ASSERT_TRUE(ri != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  EXPECT_STREQ(ri->script, "GetterReleaseScript.sh");
  EXPECT_STREQ(ri->repository, "example/release");

  EXPECT_STREQ(ri->license_name, "MIT");
  EXPECT_STREQ(ri->license, "LICENSE.txt");
  EXPECT_STREQ(ri->readme, "README.txt");
  EXPECT_STREQ(ri->changelog, "CHANGELOG.txt");

  EXPECT_STREQ(ri->dependencies.arr[0], "box1");
  EXPECT_STREQ(ri->dependencies.arr[1], "box2");
  EXPECT_STREQ(ri->build_dependencies.arr[0], "box3");
  EXPECT_STREQ(ri->build_dependencies.arr[1], "box4");
  EXPECT_STREQ(ri->build_dependencies.arr[2], "box5");
  EXPECT_STREQ(ri->optional_dependencies.arr[0], "box6");
  EXPECT_STREQ(ri->conflicts.arr[0], "box7");
  EXPECT_STREQ(ri->conflicts.arr[1], "box8");
  EXPECT_STREQ(ri->replaces.arr[0], "box9");
  EXPECT_STREQ(ri->replaces.arr[1], "box10");

  gtt_release_info_delete(ri);
}

TEST(ReleaseInfo, CreatesFromJSONRequiredFields) {
  const char json[] = "{ \"script\": \"GetterReleaseScript.sh\" }";
  GttReleaseInfo *ri = gtt_release_info_new_from_json(json);

  ASSERT_TRUE(ri != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);
  EXPECT_STREQ(ri->script, "GetterReleaseScript.sh");

  gtt_release_info_delete(ri);
}

TEST(ReleaseInfo, DoesNotCreateFromJSONMissingFields) {
  const char json[] =
      "{"
      "  \"license_name\": \"MIT\","
      "  \"license\": \"LICENSE.txt\","
      "}";

  GttReleaseInfo *ri = gtt_release_info_new_from_json(json);

  ASSERT_TRUE(ri == NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_PARSE_ERROR);
}

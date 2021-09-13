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

TEST(ReleaseInfo, CreatesFromPKVFAllFields) {
  const char pkvf[] =
      "repository@#@example/release\n"

      "license_name@#@MIT\n"
      "license@#@LICENSE.txt\n"
      "readme@#@README.txt\n"
      "changelog@#@CHANGELOG.txt\n"

      "dependencies@#@box1@,@box2@,@\n"
      "build_dependencies@#@box3@,@box4@,@box5@,@\n"
      "optional_dependencies@#@box6@,@\n"
      "conflicts@#@box7@,@box8@,@\n"
      "replaces@#@box9@,@box10@,@\n";

  GttReleaseInfo *ri = gtt_release_info_new_from_pkvf(pkvf);

  ASSERT_TRUE(ri != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  EXPECT_STREQ(ri->repository, "example/release");

  EXPECT_STREQ(ri->license_name, "MIT");
  EXPECT_STREQ(ri->license, "LICENSE.txt");
  EXPECT_STREQ(ri->readme, "README.txt");
  EXPECT_STREQ(ri->changelog, "CHANGELOG.txt");

  EXPECT_STREQ(gtt_vector_string_get(ri->dependencies, 0)->value, "box1");
  EXPECT_STREQ(gtt_vector_string_get(ri->dependencies, 1)->value, "box2");
  EXPECT_STREQ(gtt_vector_string_get(ri->build_dependencies, 0)->value, "box3");
  EXPECT_STREQ(gtt_vector_string_get(ri->build_dependencies, 1)->value, "box4");
  EXPECT_STREQ(gtt_vector_string_get(ri->build_dependencies, 2)->value, "box5");
  EXPECT_STREQ(gtt_vector_string_get(ri->optional_dependencies, 0)->value,
               "box6");
  EXPECT_STREQ(gtt_vector_string_get(ri->conflicts, 0)->value, "box7");
  EXPECT_STREQ(gtt_vector_string_get(ri->conflicts, 1)->value, "box8");
  EXPECT_STREQ(gtt_vector_string_get(ri->replaces, 0)->value, "box9");
  EXPECT_STREQ(gtt_vector_string_get(ri->replaces, 1)->value, "box10");

  gtt_release_info_delete(ri);
}

TEST(ReleaseInfo, DoesNotCreateFromPKVFInvalidField) {
  const char pkvf[] = "invalid@#@field\n";
  GttReleaseInfo *ri = gtt_release_info_new_from_pkvf(pkvf);

  ASSERT_TRUE(ri == NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_INVALID_DATA);
}

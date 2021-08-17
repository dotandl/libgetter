/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/release/release.h>
#include <gtest/gtest.h>

TEST(Release, CreatesValidVersion) {
  GttRelease *release = gtt_release_new("win32", "x86_64", "1.0.0");

  EXPECT_TRUE(release != NULL);
  EXPECT_STREQ(release->platform, "win32");
  EXPECT_STREQ(release->arch, "x86_64");
  EXPECT_STREQ(release->version, "1.0.0");

  gtt_release_delete(release);
}

TEST(Release, CreatesValidVersionWithPrefixAndSuffix) {
  GttRelease *release = gtt_release_new("win32", "x86_64", "prefix0.1.0suffix");

  EXPECT_TRUE(release != NULL);
  EXPECT_STREQ(release->platform, "win32");
  EXPECT_STREQ(release->arch, "x86_64");
  EXPECT_STREQ(release->version, "prefix0.1.0suffix");

  gtt_release_delete(release);
}

TEST(Release, DoesNotCreateInvalidVersion) {
  GttRelease *release = gtt_release_new("win32", "x86_64", "2.1-invalid");

  EXPECT_TRUE(release == NULL);
}

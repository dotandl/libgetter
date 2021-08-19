/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/release/version.h>
#include <getter/tools/platform.h>
#include <gtest/gtest.h>

TEST(ReleaseLatestVersionCalculator, ReturnsLatestRelease) {
  GttVector_release *releases = gtt_vector_release_new();

  gtt_vector_release_push(releases,
                          gtt_release_new(GTT_PLATFORM, GTT_ARCH, "v1.0.0"));
  gtt_vector_release_push(
      releases, gtt_release_new(GTT_PLATFORM, GTT_ARCH, "v1.11111.0"));
  gtt_vector_release_push(releases,
                          gtt_release_new(GTT_PLATFORM, GTT_ARCH, "v1.1.1"));

  GttRelease *latest = gtt_get_latest_release_version(releases);

  EXPECT_STREQ(latest->version, "v1.11111.0");

  gtt_release_delete(gtt_vector_release_get(releases, 0)->value);
  gtt_release_delete(gtt_vector_release_get(releases, 1)->value);
  gtt_release_delete(gtt_vector_release_get(releases, 2)->value);
  gtt_vector_release_delete(releases);
}

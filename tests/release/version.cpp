/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/release/version.h>
#include <getter/tools/error.h>
#include <getter/tools/platform.h>
#include <gtest/gtest.h>

#include <cstdlib>

TEST(ReleaseLatestVersionCalculator, ReturnsLatestRelease) {
  cvector_vector_type(GttRelease *) releases = NULL;

  cvector_push_back(releases, gtt_release_new("linux", "x86", "v1.0.0"));
  cvector_push_back(releases, gtt_release_new("linux", "x86", "v1.11111.0"));
  cvector_push_back(releases, gtt_release_new("linux", "x86", "v1.1.1"));

  GttRelease *latest = gtt_get_latest_release_version(releases);

  ASSERT_EQ(gtt_last_error.code, GTT_OK);
  ASSERT_STREQ(latest->version, "v1.11111.0");

  gtt_release_delete(releases[0]);
  gtt_release_delete(releases[1]);
  gtt_release_delete(releases[2]);
  cvector_free(releases);
}

/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/release/extracted_release.h>
#include <getter/tools/error.h>
#include <gtest/gtest.h>

TEST(ExtractedRelease, GeneratesSuccessfully) {
  const char *ri_json =
      "{"
      "  \"script\": \"GetterScript.sh\","
      "  \"repository\": \"https://github.com/foo/bar-macOS\","
      "  \"readme\": \"README-macOS.txt\","
      "  \"dependencies\": [\"qux\"]"
      "}";

  const char *bi_json =
      "{"
      "  \"name\": \"bar\","
      "  \"full_name\": \"Bar\","
      "  \"summary\": \"Example box\","
      "  \"homepage\": \"https://example.com\","
      "  \"repository\": \"https://github.com/foo/bar\","
      "  \"authors\": [\"foo\"],"
      "  \"license_name\": \"MIT\","
      "  \"dependencies\": [\"baz\"],"
      "  \"replaces\": [\"bar-legacy\"]"
      "}";

  GttRelease *r = gtt_release_new("macos", "arm64", "v3.2.1");
  GttReleaseInfo *ri = gtt_release_info_new_from_json(ri_json);
  GttBoxInfo *bi = gtt_box_info_new_from_json(bi_json);

  ASSERT_FALSE(r == NULL);
  ASSERT_FALSE(ri == NULL);
  ASSERT_FALSE(bi == NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  GttExtractedRelease *er = gtt_extracted_release_new(r, ri, bi);

  EXPECT_STREQ(er->platform, "macos");
  EXPECT_STREQ(er->arch, "arm64");
  EXPECT_STREQ(er->version, "v3.2.1");
  EXPECT_STREQ(er->script, "GetterScript.sh");
  EXPECT_STREQ(er->name, "bar");
  EXPECT_STREQ(er->full_name, "Bar");
  EXPECT_STREQ(er->summary, "Example box");
  EXPECT_STREQ(er->homepage, "https://example.com");
  EXPECT_STREQ(er->repository, "https://github.com/foo/bar-macOS");
  EXPECT_STREQ(er->authors.arr[0], "foo");
  EXPECT_STREQ(er->license_name, "MIT");
  EXPECT_STREQ(er->readme, "README-macOS.txt");
  EXPECT_STREQ(er->replaces.arr[0], "bar-legacy");

  int i, counter = 0;
  for (i = 0; i < er->dependencies.nmemb; i++) {
    if (strcmp(er->dependencies.arr[i], "baz") == 0) counter++;
    if (strcmp(er->dependencies.arr[i], "qux") == 0) counter++;
  }
  ASSERT_EQ(counter, 2);

  gtt_release_delete(r);
  gtt_release_info_delete(ri);
  gtt_box_info_delete(bi);
  gtt_extracted_release_delete(er);
}

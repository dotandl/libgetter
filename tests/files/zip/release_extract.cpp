/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/files/zip/box.h>
#include <getter/files/zip/release_extract.h>
#include <getter/tools/error.h>
#include <getter/tools/tmp.h>
#include <gtest/gtest.h>

#include <filesystem>

namespace fs = std::filesystem;

TEST(ReleaseExtractor, ExtractsRelease) {
  const char *file = GTT_TESTS_DIR "/ExampleBox.zip";

  zip_t *zip = zip_open(file, 0, NULL);
  ASSERT_FALSE(zip == NULL);

  GttBox *box = gtt_zip_read_box(zip);
  ASSERT_FALSE(box == NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);
  ASSERT_GE(box->releases.nmemb, 1);

  char buf[GTT_BUFLEN];
  const char *res = gtt_zip_extract_release(
      zip, (GttRelease *)box->releases.arr[0], buf, GTT_BUFLEN);

  ASSERT_FALSE(res == NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  ASSERT_TRUE(fs::exists(buf));
  ASSERT_TRUE(fs::is_directory(buf));
  ASSERT_FALSE(fs::is_empty(buf));

  gtt_rmtmpdir(res);
  gtt_box_delete(box);
  zip_close(zip);
}

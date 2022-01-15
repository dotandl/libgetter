/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/files/zip/box.h>
#include <getter/tools/error.h>
#include <gtest/gtest.h>

#include <string>

using std::string;

TEST(Zip, GeneratesBoxObject) {
  const char *file = GTT_TESTS_DIR "/ExampleBox.zip";

  zip_t *zip = zip_open(file, 0, NULL);
  ASSERT_TRUE(zip != NULL);

  GttBox *box = gtt_zip_read_box(zip);

  ASSERT_TRUE(box != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  GttBoxInfo *bi = box->info;
  GttPtrArr arr = box->releases;

  /* BoxInfo */
  EXPECT_STREQ(bi->name, "example-box");
  EXPECT_STREQ(bi->full_name, "Example Box");
  EXPECT_STREQ(bi->summary, "testtest");
  EXPECT_STREQ(bi->authors.arr[0], "dotandl");
  EXPECT_STREQ(bi->license_name, "MIT");

  /* Releases */
  int i, counter = 0;

  for (i = 0; i < arr.nmemb; i++) {
    if (string(((GttRelease *)arr.arr[i])->version) == "v1.0.0" &&
        string(((GttRelease *)arr.arr[i])->platform) == "win32" &&
        string(((GttRelease *)arr.arr[i])->arch) == "x86_64")
      counter++;

    if (string(((GttRelease *)arr.arr[i])->version) == "v1.0.0" &&
        string(((GttRelease *)arr.arr[i])->platform) == "linux" &&
        string(((GttRelease *)arr.arr[i])->arch) == "x86_64")
      counter++;

    if (string(((GttRelease *)arr.arr[i])->version) == "v1.0.0" &&
        string(((GttRelease *)arr.arr[i])->platform) == "linux" &&
        string(((GttRelease *)arr.arr[i])->arch) == "arm64")
      counter++;

    if (string(((GttRelease *)arr.arr[i])->version) == "v1.1.0" &&
        string(((GttRelease *)arr.arr[i])->platform) == "win32" &&
        string(((GttRelease *)arr.arr[i])->arch) == "x86_64")
      counter++;

    if (string(((GttRelease *)arr.arr[i])->version) == "v1.1.0" &&
        string(((GttRelease *)arr.arr[i])->platform) == "linux" &&
        string(((GttRelease *)arr.arr[i])->arch) == "x86_64")
      counter++;

    if (string(((GttRelease *)arr.arr[i])->version) == "v1.1.0" &&
        string(((GttRelease *)arr.arr[i])->platform) == "linux" &&
        string(((GttRelease *)arr.arr[i])->arch) == "arm64")
      counter++;
  }

  EXPECT_EQ(counter, 6);  // expect that each of 6 releases is found in the box

  gtt_box_delete(box);
  zip_close(zip);
}

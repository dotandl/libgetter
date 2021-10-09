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
  string file = string(GTT_TESTS_DIR) + "/res/ExampleBox.zip";
  GttBox *box;

  box = gtt_zip_read_box(file.c_str());

  ASSERT_TRUE(box != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  GttBoxInfo *bi = box->info;
  cvector_vector_type(GttRelease *) vec = box->releases;

  /* BoxInfo */
  EXPECT_STREQ(bi->name, "example-box");
  EXPECT_STREQ(bi->full_name, "Example Box");
  EXPECT_STREQ(bi->summary, "testtest");
  EXPECT_STREQ(bi->authors[0], "dotandl");
  EXPECT_STREQ(bi->license_name, "MIT");

  /* Releases */
  EXPECT_STREQ(vec[0]->version, "v1.1.0");
  EXPECT_STREQ(vec[0]->platform, "linux");
  EXPECT_STREQ(vec[0]->arch, "x86_64");

  EXPECT_STREQ(vec[1]->version, "v1.1.0");
  EXPECT_STREQ(vec[1]->platform, "linux");
  EXPECT_STREQ(vec[1]->arch, "arm64");

  EXPECT_STREQ(vec[2]->version, "v1.1.0");
  EXPECT_STREQ(vec[2]->platform, "win32");
  EXPECT_STREQ(vec[2]->arch, "x86_64");

  EXPECT_STREQ(vec[3]->version, "v1.0.0");
  EXPECT_STREQ(vec[3]->platform, "linux");
  EXPECT_STREQ(vec[3]->arch, "x86_64");

  EXPECT_STREQ(vec[4]->version, "v1.0.0");
  EXPECT_STREQ(vec[4]->platform, "linux");
  EXPECT_STREQ(vec[4]->arch, "arm64");

  EXPECT_STREQ(vec[5]->version, "v1.0.0");
  EXPECT_STREQ(vec[5]->platform, "win32");
  EXPECT_STREQ(vec[5]->arch, "x86_64");

  gtt_box_delete(box);
}

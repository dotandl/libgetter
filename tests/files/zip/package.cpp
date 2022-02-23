/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#include <getter/files/zip/package.h>
#include <getter/tools/error.h>
#include <gtest/gtest.h>

TEST(Zip, InstallsPackage) {
  zip_t *zip = zip_open(GTT_TESTS_DIR "/ExampleBox.zip", 0, NULL);

  gtt_zip_package_install(zip);

  ASSERT_EQ(gtt_last_error.code, GTT_OK);
}

/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/types/pkvf.h>
#include <gtest/gtest.h>

TEST(PKVF, ParsesValidPKVF) {
  const char pkvf[] =
      "1st key@#@first value\n"
      "second key@#@and the value\n";

  vec_keyval_t vec;
  bool res = gtt_parse_pkvf(pkvf, &vec);

  EXPECT_TRUE(res);
  EXPECT_STREQ(vec.data[0].key, "1st key");
  EXPECT_STREQ((char *)vec.data[0].val, "first value");
  EXPECT_STREQ(vec.data[1].key, "second key");
  EXPECT_STREQ((char *)vec.data[1].val, "and the value");

  vec_keyval_free(&vec);
}

TEST(PKVF, DoesNotCreateInvalidPKVF) {
  const char pkvf[] = "asjkdahs\najksdj\n\n";

  vec_keyval_t vec;
  bool res = gtt_parse_pkvf(pkvf, &vec);

  EXPECT_FALSE(res);

  vec_keyval_free(&vec);
}

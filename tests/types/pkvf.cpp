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

  GttVector_pkvf_token *vec;
  bool res = gtt_parse_pkvf(pkvf, &vec);

  EXPECT_TRUE(res);
  EXPECT_STREQ(gtt_vector_pkvf_token_get(vec, 0)->value.key, "1st key");
  EXPECT_STREQ(gtt_vector_pkvf_token_get(vec, 0)->value.val.str, "first value");
  EXPECT_STREQ(gtt_vector_pkvf_token_get(vec, 1)->value.key, "second key");
  EXPECT_STREQ(gtt_vector_pkvf_token_get(vec, 1)->value.val.str,
               "and the value");

  gtt_vector_pkvf_token_free(vec);
}

TEST(PKVF, DoesNotCreateInvalidPKVF) {
  const char pkvf[] = "asjkdahs\najksdj\n\n";

  GttVector_pkvf_token *vec;
  bool res = gtt_parse_pkvf(pkvf, &vec);

  EXPECT_FALSE(res);

  gtt_vector_pkvf_token_free(vec);
}

/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/error.h>
#include <getter/types/pkvf.h>
#include <gtest/gtest.h>

TEST(PKVF, ParsesValidPKVF) {
  const char pkvf[] =
      "1st key@#@first value\n"
      "second key@#@and the value\n";

  cvector_vector_type(GttPKVFToken) vec = gtt_parse_pkvf(pkvf);

  ASSERT_TRUE(vec != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  EXPECT_STREQ(vec[0].key, "1st key");
  EXPECT_STREQ(vec[0].val.str, "first value");
  EXPECT_STREQ(vec[1].key, "second key");
  EXPECT_STREQ(vec[1].val.str, "and the value");

  gtt_vector_pkvf_token_free(vec);
}

TEST(PKVF, ParsesValidPKVFWithArray) {
  const char pkvf[] =
      "1st key@#@string value\n"
      "2nd key@#@array@,@of@,@strings@,@\n";

  cvector_vector_type(GttPKVFToken) vec = gtt_parse_pkvf(pkvf);

  cvector_vector_type(char *) second_value = vec[1].val.vec;

  ASSERT_TRUE(vec != NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  EXPECT_STREQ(vec[0].key, "1st key");
  EXPECT_STREQ(vec[0].val.str, "string value");
  EXPECT_STREQ(vec[1].key, "2nd key");
  EXPECT_STREQ(second_value[0], "array");
  EXPECT_STREQ(second_value[1], "of");
  EXPECT_STREQ(second_value[2], "strings");

  gtt_vector_pkvf_token_free(vec);
}

TEST(PKVF, DoesNotCreateInvalidPKVF) {
  const char pkvf[] = "asjkdahs\najksdj\n\n";
  cvector_vector_type(GttPKVFToken) vec = gtt_parse_pkvf(pkvf);

  ASSERT_TRUE(vec == NULL);
  ASSERT_EQ(gtt_last_error.code, GTT_PARSE_ERROR);
}

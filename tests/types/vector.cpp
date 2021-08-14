/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <cstring>

#define GTT_VEC_TYPE char *
#define GTT_VEC_NAME string
#define gtt_vec_compare_elements(el1, el2) strcmp((el1), (el2)) == 0

#include <getter/types/vector.h>
#include <gtest/gtest.h>

TEST(StringVector, GetsElement) {
  const char *strings[] = {"Hello", "World", "!"};

  GttVector_string *vec = gtt_vector_string_new();
  gtt_vector_string_push(vec, (char *)strings[0]);
  gtt_vector_string_push(vec, (char *)strings[1]);
  gtt_vector_string_push(vec, (char *)strings[2]);

  EXPECT_STREQ(gtt_vector_string_get(vec, 0)->value, strings[0]);
  EXPECT_STREQ(gtt_vector_string_get(vec, 1)->value, strings[1]);
  EXPECT_STREQ(gtt_vector_string_get(vec, 2)->value, strings[2]);

  gtt_vector_string_delete(vec);
}

TEST(StringVector, GetsIndexOfElement) {
  const char *strings[] = {"the first element", "and the second one",
                           "and the last one"};

  GttVector_string *vec = gtt_vector_string_new();
  gtt_vector_string_push(vec, (char *)strings[0]);
  gtt_vector_string_push(vec, (char *)strings[1]);
  gtt_vector_string_push(vec, (char *)strings[2]);

  EXPECT_EQ(gtt_vector_string_index_of(vec, (char *)strings[0]), 0);
  EXPECT_EQ(gtt_vector_string_index_of(vec, (char *)strings[1]), 1);
  EXPECT_EQ(gtt_vector_string_index_of(vec, (char *)strings[2]), 2);

  gtt_vector_string_delete(vec);
}

TEST(StringVector, UnshiftsElement) {
  const char *strings[] = {"first", "second", "unshifted"};

  GttVector_string *vec = gtt_vector_string_new();
  gtt_vector_string_push(vec, (char *)strings[0]);
  gtt_vector_string_push(vec, (char *)strings[1]);
  gtt_vector_string_unshift(vec, (char *)strings[2]);

  EXPECT_STREQ(gtt_vector_string_get(vec, 0)->value, strings[2]);
  EXPECT_STREQ(gtt_vector_string_get(vec, 1)->value, strings[0]);
  EXPECT_STREQ(gtt_vector_string_get(vec, 2)->value, strings[1]);

  gtt_vector_string_delete(vec);
}

TEST(StringVector, InsertsElement) {
  const char *strings[] = {"first", "second", "inserted at index 1"};

  GttVector_string *vec = gtt_vector_string_new();
  gtt_vector_string_push(vec, (char *)strings[0]);
  gtt_vector_string_push(vec, (char *)strings[1]);
  gtt_vector_string_insert(vec, (char *)strings[2], 1);

  EXPECT_STREQ(gtt_vector_string_get(vec, 0)->value, strings[0]);
  EXPECT_STREQ(gtt_vector_string_get(vec, 1)->value, strings[2]);
  EXPECT_STREQ(gtt_vector_string_get(vec, 2)->value, strings[1]);

  gtt_vector_string_delete(vec);
}

TEST(StringVector, RemovesFirstElement) {
  const char *strings[] = {"first", "second", "third"};

  GttVector_string *vec = gtt_vector_string_new();
  gtt_vector_string_push(vec, (char *)strings[0]);
  gtt_vector_string_push(vec, (char *)strings[1]);
  gtt_vector_string_push(vec, (char *)strings[2]);
  gtt_vector_string_remove_first(vec);

  EXPECT_STREQ(gtt_vector_string_get(vec, 0)->value, strings[1]);
  EXPECT_STREQ(gtt_vector_string_get(vec, 1)->value, strings[2]);

  gtt_vector_string_delete(vec);
}

TEST(StringVector, RemovesLastElement) {
  const char *strings[] = {"first", "second", "third"};

  GttVector_string *vec = gtt_vector_string_new();
  gtt_vector_string_push(vec, (char *)strings[0]);
  gtt_vector_string_push(vec, (char *)strings[1]);
  gtt_vector_string_push(vec, (char *)strings[2]);
  gtt_vector_string_remove_last(vec);

  EXPECT_STREQ(gtt_vector_string_get(vec, 0)->value, strings[0]);
  EXPECT_STREQ(gtt_vector_string_get(vec, 1)->value, strings[1]);

  gtt_vector_string_delete(vec);
}

TEST(StringVector, RemovesElement) {
  const char *strings[] = {"first", "removed", "third"};

  GttVector_string *vec = gtt_vector_string_new();
  gtt_vector_string_push(vec, (char *)strings[0]);
  gtt_vector_string_push(vec, (char *)strings[1]);
  gtt_vector_string_push(vec, (char *)strings[2]);
  gtt_vector_string_remove(vec, 1);

  EXPECT_STREQ(gtt_vector_string_get(vec, 0)->value, strings[0]);
  EXPECT_STREQ(gtt_vector_string_get(vec, 1)->value, strings[2]);

  gtt_vector_string_delete(vec);
}

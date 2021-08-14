/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/box/info.h>
#include <gtest/gtest.h>

TEST(BoxInfo, CreatesFromJSONAllFields) {
  const char *json =
      "{"
      "  \"name\": \"example\","
      "  \"full_name\": \"Example\","
      "  \"summary\": \"Example box\","
      "  \"description\": \"Example box blah blah\","

      "  \"homepage\": \"https://example.com/\","
      "  \"repository\": \"example/box\","
      "  \"authors\": [\"Josh\", \"Jimmy\"],"
      "  \"categories\": [\"Utilities\"],"

      "  \"license_name\": \"MIT\","
      "  \"license\": \"LICENSE.txt\","
      "  \"readme\": \"README.txt\","
      "  \"changelog\": \"CHANGELOG.txt\","

      "  \"dependencies\": [\"box1\", \"box2\"],"
      "  \"build_dependencies\": [\"box3\", \"box4\", \"box5\"],"
      "  \"optional_dependencies\": [\"box6\"],"
      "  \"conflicts\": [\"box7\", \"box8\"],"
      "  \"replaces\": [\"box9\", \"box10\"]"
      "}";

  GttBoxInfo *bi = gtt_box_info_new_from_json(json);

  EXPECT_STREQ(bi->name, "example");
  EXPECT_STREQ(bi->full_name, "Example");
  EXPECT_STREQ(bi->summary, "Example box");
  EXPECT_STREQ(bi->description, "Example box blah blah");

  EXPECT_STREQ(bi->homepage, "https://example.com/");
  EXPECT_STREQ(bi->repository, "example/box");
  EXPECT_STREQ(gtt_vector_string_get(bi->authors, 0), "Josh");
  EXPECT_STREQ(gtt_vector_string_get(bi->authors, 1), "Jimmy");
  EXPECT_STREQ(gtt_vector_string_get(bi->categories, 0), "Utilities");

  EXPECT_STREQ(bi->license_name, "MIT");
  EXPECT_STREQ(bi->license, "LICENSE.txt");
  EXPECT_STREQ(bi->readme, "README.txt");
  EXPECT_STREQ(bi->changelog, "CHANGELOG.txt");

  EXPECT_STREQ(gtt_vector_string_get(bi->dependencies, 0), "box1");
  EXPECT_STREQ(gtt_vector_string_get(bi->dependencies, 1), "box2");
  EXPECT_STREQ(gtt_vector_string_get(bi->build_dependencies, 0), "box3");
  EXPECT_STREQ(gtt_vector_string_get(bi->build_dependencies, 1), "box4");
  EXPECT_STREQ(gtt_vector_string_get(bi->build_dependencies, 2), "box5");
  EXPECT_STREQ(gtt_vector_string_get(bi->optional_dependencies, 0), "box6");
  EXPECT_STREQ(gtt_vector_string_get(bi->conflicts, 0), "box7");
  EXPECT_STREQ(gtt_vector_string_get(bi->conflicts, 1), "box8");
  EXPECT_STREQ(gtt_vector_string_get(bi->replaces, 0), "box9");
  EXPECT_STREQ(gtt_vector_string_get(bi->replaces, 1), "box10");

  gtt_box_info_delete(bi);
}

TEST(BoxInfo, CreatesFromJSONRequiredFields) {
  const char *json =
      "{"
      "  \"name\": \"another-example\","
      "  \"full_name\": \"Another Example\","
      "  \"summary\": \"Yet another example box\","
      "  \"authors\": [\"Jack\"],"
      "  \"license_name\": \"GPLv3\""
      "}";

  GttBoxInfo *bi = gtt_box_info_new_from_json(json);

  EXPECT_STREQ(bi->name, "another-example");
  EXPECT_STREQ(bi->full_name, "Another Example");
  EXPECT_STREQ(bi->summary, "Yet another example box");
  EXPECT_STREQ(gtt_vector_string_get(bi->authors, 0), "Jack");
  EXPECT_STREQ(bi->license_name, "GPLv3");

  gtt_box_info_delete(bi);
}

TEST(BoxInfo, DoesNotCreateFromJSONMissingFields) {
  const char *json =
      "{"
      "  \"name\": \"incomplete-box\""
      "}";

  GttBoxInfo *bi = gtt_box_info_new_from_json(json);
  ASSERT_TRUE(bi == NULL);
}

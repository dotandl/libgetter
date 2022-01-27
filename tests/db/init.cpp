/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#include <getter/db/init.h>
#include <getter/tools/error.h>
#include <gtest/gtest.h>
#include <sqlite3.h>

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

using std::string;
using std::vector;
namespace fs = std::filesystem;

#define vector_has(vector, element) \
  (std::find((vector).begin(), (vector).end(), (element)) != (vector).end())

static int cb(void *data, int argc, char **argv, char **columns);

static bool cb_called = false, cb_assertion_failed = false;

TEST(Database, Initializes) {
  gtt_db_init("./getter.db");
  ASSERT_EQ(gtt_last_error.code, GTT_OK);

  sqlite3 *db;
  int err;
  char *errmsg;

  err = sqlite3_open("./getter.db", &db);
  ASSERT_FALSE(err);

  err = sqlite3_exec(
      db, "SELECT COUNT(*), name FROM sqlite_master WHERE type = 'table';", cb,
      NULL, &errmsg);
  if (err) {
    sqlite3_free(errmsg);
    sqlite3_close(db);
    FAIL();
  }

  while (!cb_called)
    ;  // Wait

  sqlite3_close(db);
  fs::remove("./getter.db");

  ASSERT_FALSE(cb_assertion_failed);
}

// Checks if tables have been created
static int cb(void *data, int argc, char **argv, char **columns) {
  vector<string> tables = {
      "packages", "dependency_types", "dependencies",
      "sqlite_sequence",  // Internal SQLite table
  };

  // Check number of found tables
  if (atoi(argv[0]) != tables.size()) {
    goto err;
  }

  // Check if table is in `tables`
  if (!vector_has(tables, string(argv[1]))) {
    goto err;
  }

  cb_called = true;
  return 0;

err:
  cb_assertion_failed = true;
  cb_called = true;
  return 0;
}

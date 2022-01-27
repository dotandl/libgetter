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
#include <sqlite3.h>

const char *const sql = ""
#include <incstr/init.sql>
    ;

void gtt_db_init(const char *db_file) {
  sqlite3 *db;
  int err;
  char *errmsg;

  err = sqlite3_open(db_file, &db);
  if (err) {
    gtt_error(GTT_DB_ERROR, "Error opening database");
    return;
  }

  err = sqlite3_exec(db, sql, NULL, NULL, &errmsg);
  if (err) {
    gtt_error(GTT_DB_ERROR, "Error initializing database");
    sqlite3_free(errmsg);
    sqlite3_close(db);
    return;
  }

  sqlite3_close(db);
  gtt_ok();
}

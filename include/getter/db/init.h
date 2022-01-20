/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021-2022 dotandl                          |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_DB_INIT_H_
#define INCLUDE_GETTER_DB_INIT_H_

GTT_HEADER_BEGIN

/**
 * Initializes the internal database (creates tables if they don't exist etc.).
 *
 * \param db_file Path to the database file.
 */
GTT_API GTT_ERROR_EMITTER void gtt_db_init(const char *db_file);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_DB_INIT_H_ */

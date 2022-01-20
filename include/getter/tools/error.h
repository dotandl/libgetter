/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_TOOLS_ERROR_H_
#define INCLUDE_GETTER_TOOLS_ERROR_H_

#include <stddef.h>

GTT_HEADER_BEGIN

/** List of possible errors. */
typedef enum GttErrorCode {
  GTT_UNIDENTIFIED_ERROR = -1,
  GTT_OK = 0,

  GTT_PARSE_ERROR,      ///< Error parsing any type of data (JSON, PKVF, etc.).
  GTT_INVALID_DATA,     ///< Invalid data found while parsing any type of data.
  GTT_INVALID_VERSION,  ///< Not a semantic versioned version.
  GTT_REGEXP_COMPILATION_FAILED,  ///< Error compiling regular expression.
  GTT_UNSUPPORTED_HOST,   ///< Unsupported platform or processor architecture.
  GTT_LIBGETTER_TOO_OLD,  ///< Box requires newer version of libgetter to
                          ///< install itself properly.
  GTT_ZIP_ERROR,          ///< Error opening/processing zip file.
  GTT_NOT_FOUND,          ///< Specified target (e.g. Release) not found.
  GTT_ARR_RESIZE_FAILED,  ///< Could not resize the array (new nmemb is too
                          ///< small).
  GTT_DB_ERROR,           ///< Error opening/querying internal database.
} GttErrorCode;

/** Representation of an error. */
typedef struct GttError {
  GttErrorCode code;
  char desc[GTT_BUFLEN];
} GttError;

/**
 * Stores the latest error (or success).
 *
 * \see GttError
 */
GTT_API extern GttError gtt_last_error;

/**
 * Shortcut for the `gtt_last_error.code != GTT_OK` condition checking whether
 * some operation has failed.
 *
 * Usage:
 * \code
 * gtt_do_some_stuff();
 * if (GTT_FAILED) {
 *   // handle error
 * }
 * \endcode
 *
 * \see GttError
 */
#define GTT_FAILED (gtt_last_error.code != GTT_OK)

/**
 * Sets an error.
 *
 * Note that this function is intended to use inside libgetter only. DO NOT USE
 * IT OUTSIDE LIBRARY!
 *
 * \param err_code Error type (code).
 * \param err_desc Additional information about the error or NULL.
 */
void gtt_error(GttErrorCode err_code, const char *err_desc);

/**
 * Sets OK error code.
 *
 * Note that this function is intended to use inside libgetter only. DO NOT USE
 * IT OUTSIDE LIBRARY!
 */
#define gtt_ok() gtt_error(GTT_OK, NULL)

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TOOLS_ERROR_H_ */

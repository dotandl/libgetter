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

HEADER_BEGIN

#define __BUFSIZE 64

/** List of possible errors. */
enum GttErrorCode {
  GTT_UNIDENTIFIED_ERROR = -1,
  GTT_OK = 0,

  GTT_PARSE_ERROR,      ///< Error parsing any type of data (JSON, PKVF, etc.).
  GTT_INVALID_DATA,     ///< Invalid data found while parsing any type of data.
  GTT_INVALID_VERSION,  ///< Not a semantic versioned version.
  GTT_REGEXP_COMPILATION_FAILED,  ///< Error compiling regular expression.
  GTT_UNSUPPORTED_HOST,   ///< Unsupported platform or processor architecture.
  GTT_LIBGETTER_TOO_OLD,  ///< Box requires newer version of libgetter to
                          ///< install itself properly.
};

typedef enum GttErrorCode GttErrorCode;

/** Representation of an error. */
struct GttError {
  GttErrorCode code;
  char desc[__BUFSIZE];
};

typedef struct GttError GttError;

/**
 * Stores the latest error (or success).
 *
 * \see GttError
 */
extern GttError gtt_last_error;

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

/** Sets OK error code. */
#define gtt_ok() gtt_error(GTT_OK, NULL)

#undef __BUFSIZE

HEADER_END

#endif /* INCLUDE_GETTER_TOOLS_ERROR_H_ */

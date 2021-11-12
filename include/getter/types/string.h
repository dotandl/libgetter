/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#ifndef INCLUDE_GETTER_TYPES_STRING_H_
#define INCLUDE_GETTER_TYPES_STRING_H_

#include <string.h>

GTT_HEADER_BEGIN

/**
 * Checks whether _haystack_ starts with _needle_.
 *
 * \param haystack The string to search in.
 * \param needle The string to search for in _haystack_.
 * \returns If _haystack_ starts with _needle_ or not.
 */
#define gtt_str_starts_with(haystack, needle) \
  strncmp((haystack), (needle), strlen((needle))) == 0

/**
 * Checks whether _haystack_ ends with _needle_.
 *
 * \param haystack The string to search in.
 * \param needle The string to search for in _haystack_.
 * \returns If _haystack_ ends with _needle_ or not.
 */
#define gtt_str_ends_with(haystack, needle) \
  strcmp((haystack) + strlen((haystack)) - strlen((needle)), (needle)) == 0

/**
 * Tries to find _needle_ char from the end of the _haystack_.
 *
 * \param haystack The string to search in.
 * \param needle The character to search for in _haystack_.
 * \returns Pointer to _needle_ in _haystack_ (or NULL if not found).
 */
GTT_API char *gtt_str_find_last(char *haystack, char needle);

/**
 * Tries ot find _needle_ char in the _haystack_ omitting _offset_ occurrences
 * of _needle_.
 *
 * \param haystack The string to search in.
 * \param needle The character to search for in _haystack_.
 * \param offset A number of _needle_ occurrences to omit.
 * \returns Pointer to _needle_ in _haystack_ (or NULL if not found).
 */
GTT_API char *gtt_str_find_first_off(char *haystack, char needle,
                                     size_t offset);

GTT_HEADER_END

#endif /* INCLUDE_GETTER_TYPES_STRING_H_ */

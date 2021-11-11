/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/types/string.h>

char *gtt_str_find_last(char *haystack, char needle) {
  char *ptr;

  for (ptr = haystack + strlen(haystack) - 1; ptr >= haystack; ptr--) {
    if (*ptr == needle) return ptr;
  }

  return NULL;
}

char *gtt_str_find_first_off(char *haystack, char needle, size_t offset) {
  char *ptr;
  size_t cur_off; /* current offset */

  cur_off = 0;

  for (ptr = haystack; ptr < haystack + strlen(haystack); ptr++) {
    if (*ptr == needle && cur_off++ == offset) return ptr;
  }

  return NULL;
}

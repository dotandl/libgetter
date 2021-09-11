/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/version.h>

bool gtt_is_newer(unsigned int c_major, unsigned int c_minor,
                  unsigned int c_patch, unsigned int major, unsigned int minor,
                  unsigned int patch) {
  return (c_major > major) || (c_minor > minor && c_major == major) ||
         (c_patch > patch && c_minor == minor && c_major == major);
}

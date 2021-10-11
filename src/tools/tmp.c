/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/tmp.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define __BUFSIZE 128

char *gtt_mktmpdir(char *buf, size_t bufsize) {
  char tmp_dir[__BUFSIZE] = {0};

#ifdef _WIN32
  GetTempPathA(__BUFSIZE, tmp_dir);
  /* no need to append a backslash - it's always present */
#else
  char *tmp_root = getenv("TMPDIR");

  /* fallback to /tmp/ if $TMPDIR isn't present or is empty */
  if (tmp_root == NULL || tmp_root[0] == 0) {
    tmp_root = "/tmp/";
  }

  strncpy(tmp_dir, tmp_root, __BUFSIZE - 1);

  /* make sure path ends with at least one slash (2 slashes aren't a problem) */
  strncat(tmp_dir, "/", __BUFSIZE - strlen(tmp_dir) - 1);
#endif

  /* temp folder will be named getter-XXXXXX, where each X is a random character
   * (see mkdtemp(3)) */
  strncat(tmp_dir, "getter-XXXXXX", __BUFSIZE - strlen(tmp_dir) - 1);
  mkdtemp(tmp_dir);

  strncpy(buf, tmp_dir, bufsize - 1);
  return buf;
}

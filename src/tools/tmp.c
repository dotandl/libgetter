/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <dirent.h>
#include <getter/tools/tmp.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#define mkdtemp(dir)                    \
  do {                                  \
    char *name = _mktemp((dir));        \
    mkdir(name);                        \
  } while (0)
#endif

#define __BUFSIZE 128

char *gtt_mktmpdir(char *buf, size_t bufsize) {
  char tmp_dir[__BUFSIZE] = {0};

#ifdef _WIN32
  GetTempPathA(__BUFSIZE, tmp_dir);
  /* no need to append a backslash - it's always present */
#else
  char *tmp_root = getenv("TMPDIR");

  /* fallback to /tmp if $TMPDIR isn't present or is empty */
  if (tmp_root == NULL || tmp_root[0] == 0) {
    tmp_root = "/tmp";
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

void gtt_rmtmpdir(const char *path) {
  char full_path[__BUFSIZE] = {0};
  DIR *dir;
  struct dirent *dir_ent;

  dir = opendir(path);

  if (dir == NULL) return;

  while ((dir_ent = readdir(dir)) != NULL) {
    if (strncmp(dir_ent->d_name, ".", __BUFSIZE) == 0 ||
        strncmp(dir_ent->d_name, "..", __BUFSIZE) == 0)
      continue;

    strncpy(full_path, path, __BUFSIZE - 1);

    /* `path` may or may not terminate with a slash, but 2 slashes aren't a
     * problem */
    strncat(full_path, "/", __BUFSIZE - strlen(full_path) - 1);
    strncat(full_path, dir_ent->d_name, __BUFSIZE - strlen(full_path) - 1);

#ifdef _WIN32
    DWORD attr = GetFileAttributesA(full_path);

    if (attr & FILE_ATTRIBUTE_DIRECTORY) {
      gtt_rmtmpdir(full_path);
    } else {
      /* regular file */
      unlink(full_path);
    }
#else
    switch (dir_ent->d_type) {
      case DT_DIR:
        gtt_rmtmpdir(full_path);
        break;

      default:
        /* regular file */
        unlink(full_path);
        break;
    }
#endif
  }

  closedir(dir);
  rmdir(path);
}

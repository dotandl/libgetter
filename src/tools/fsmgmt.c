/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/fsmgmt.h>
#include <getter/types/string.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h> /* _mkdir() */
#else
#include <sys/stat.h> /* mkdir() */
#define _mkdir(path) mkdir((path), S_IRWXU)
#endif

// BUG: may not work on Windows

static void gtt_mkdir_p(const char *path);

void gtt_new_file_mkdir_parents(const char *path, void *contents, size_t size) {
  char *ptr;
  char parent_dirs[128];
  FILE *fd;

  ptr = gtt_str_find_last((char *)path, '/');

  if (ptr != NULL) {
    snprintf(parent_dirs, ptr - path + 1, "%s", path);
    gtt_mkdir_p(parent_dirs);
  }

  fd = fopen(path, "w");
  fwrite(contents, 1, size, fd);
  fclose(fd);
}

void gtt_mkdir_p(const char *path) {
  char *ptr;
  char l_path[128]; /* local copy of path */
  char dir[128];
  size_t offset;

  offset = 0;
  snprintf(l_path, sizeof(l_path), "%s/", path);

  while ((ptr = gtt_str_find_first_off(l_path, '/', offset++)) != NULL) {
    snprintf(dir, ptr - path + 1, "%s", path);
    _mkdir(dir);
  }
}

/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/touch.h>
#include <getter/types/string.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h> /* _mkdir() */
#else
#include <sys/stat.h> /* mkdir() */
#define _mkdir(path) mkdir((path), S_IRWXU)
#endif

#define touch(file) fclose(fopen((file), "w"))

// TODO: implementation for Windows
// WINDLL void gtt_touch_mkpd(const char *path) {
//   /* local path (strtok cannot take string literals) */
//   char l_path[strlen(path) + 1];
//   char *ptr, *oldptr, *saveptr;
//   FILE *fd;

//   strcpy(l_path, path);
//   fd = fopen("/tmp/dupadupa", "w");

//   ptr = strtok_r(l_path, "/", &saveptr);
//   while (ptr != NULL) {
//     oldptr = ptr;
//     ptr = strtok_r(NULL, "/", &saveptr);

//     /* if next part of path is NULL, the current one is a file */
//     if (ptr == NULL) {
//       // fd = fopen(path, "w");
//       // fclose(fd);
//       fprintf(fd, "1 %s\n", path);
//     }
//     /* otherwise there's at least one another part of the path so the current
//      * one is a dir */
//     else {
//       fprintf(fd, "2 %s\n", saveptr);
//     }
//   }

//   fclose(fd);
// }

static void gtt_mkdir_p(const char *path);

void gtt_touch_mkpd(const char *path) {
  char *ptr;
  char parent_dirs[128];

  ptr = gtt_str_find_last((char *)path, '/');

  if (ptr != NULL) {
    snprintf(parent_dirs, ptr - path + 1, "%s", path);
    gtt_mkdir_p(parent_dirs);
  }

  touch(path);
}

void gtt_mkdir_p(const char *path) {
  char *ptr;
  char l_path[128]; /* local copy of path */
  char dir[128];
  size_t offset;

  snprintf(l_path, sizeof(l_path), "%s/", path);

  offset = 0;

  while ((ptr = gtt_str_find_first_off(l_path, '/', offset++)) != NULL) {
    snprintf(dir, ptr - path + 1, "%s", path);
    int x = _mkdir(dir);
    __asm__("nop");
  }
}

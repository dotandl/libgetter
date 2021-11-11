/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/files/zip/box.h>
#include <getter/files/zip/release_extract.h>
#include <getter/tools/error.h>
#include <getter/tools/tmp.h>
#include <getter/tools/touch.h>
#include <getter/types/string.h>
#include <string.h>

#define __BUFSIZE 128

const char *gtt_zip_extract_release(zip_t *zip, const char *version,
                                    const char *platform, const char *arch,
                                    char *buf, size_t bufsize) {
  unsigned int i;
  GttRelease *release;
  char release_path[__BUFSIZE];
  char tmpdir_path[__BUFSIZE];
  char tmpdir_entry_path[__BUFSIZE];
  char *entry_path, *release_relative_path;

  buf[0] = 0;

  if (zip == NULL) {
    gtt_error(GTT_ZIP_ERROR, "Zip object is NULL");
    return NULL;
  }

  gtt_mktmpdir(tmpdir_path, __BUFSIZE);

  GttBox *box = gtt_zip_read_box(zip);

  /* error will be passed on */
  if (GTT_FAILED) return NULL;

  release = NULL;
  for (i = 0; i < cvector_size(box->releases); i++) {
    if (strcmp(box->releases[i]->version, version) == 0 &&
        strcmp(box->releases[i]->platform, platform) == 0 &&
        strcmp(box->releases[i]->arch, arch) == 0) {
      release = box->releases[i];
      break;
    }
  }

  if (release == NULL) {
    gtt_box_delete(box);

    gtt_error(GTT_NOT_FOUND, "Specified Release has not been found in the Box");
    return NULL;
  }

  snprintf(release_path, __BUFSIZE, "Releases/%s/%s/%s/", version, platform,
           arch);

  FILE *dupa = fopen("/tmp/dupa1212", "w");

  int entries = zip_get_num_entries(zip, 0);
  for (i = 0; i < entries; i++) {
    entry_path = (char *)zip_get_name(zip, i, 0);

    /* if entry is a directory, ignore */
    if (gtt_str_ends_with(entry_path, "/")) continue;

    if (gtt_str_starts_with(entry_path, release_path)) {
      /* transform the entry path to be relative to the release dir in the zip
       * (just cut the `Release/x/y/z/` at the beginning) */
      release_relative_path = entry_path + strlen(release_path);

      /* transform the path relative to the release dir in the zip to the full
       * path in the tmpdir on the filesystem */
      snprintf(tmpdir_entry_path, __BUFSIZE, "%s/%s", tmpdir_path,
               release_relative_path);

      fprintf(dupa, "%s : %s\n", release_relative_path, tmpdir_entry_path);
      gtt_touch_mkpd(tmpdir_entry_path);

      zip_file_t *zfd = zip_fopen_index(zip, i, 0);
      zip_stat_t zfstat;
      zip_stat_index(zip, i, 0, &zfstat);

      void *buf = malloc(zfstat.size);
      zip_fread(zfd, buf, zfstat.size);

      FILE *fd = fopen(tmpdir_entry_path, "w");
      fwrite(buf, 1, zfstat.size, fd);
      fclose(fd);

      zip_fclose(zfd);
    }
  }

  fclose(dupa);

  gtt_box_delete(box);
  return "/tmp/dupa1212";
}

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
#include <getter/tools/fsmgmt.h>
#include <getter/tools/tmp.h>
#include <getter/types/string.h>
#include <string.h>

const char *gtt_zip_extract_release(zip_t *zip, const char *version,
                                    const char *platform, const char *arch,
                                    char *buf, size_t bufsize) {
  unsigned int i;
  GttRelease *release;

  /* paths */
  char release_path[GTT_BUFLEN];      /* path to the release in zip */
  char tmpdir_path[GTT_BUFLEN];       /* path to temp directory on disk */
  char *entry_path;                   /* path to file/dir in zip */
  char tmpdir_entry_path[GTT_BUFLEN]; /* path to file on disk */
  char *release_relative_path; /* path to file/dir relative to release path in
                                  zip */

  /* libzip */
  zip_file_t *zfd;
  zip_stat_t zfstat;
  void *fbuf;

  buf[0] = 0;

  if (zip == NULL) {
    gtt_error(GTT_ZIP_ERROR, "Zip object is NULL");
    return NULL;
  }

  gtt_mktmpdir(tmpdir_path, GTT_BUFLEN);

  GttBox *box = gtt_zip_read_box(zip);

  /* error will be passed on */
  if (GTT_FAILED) return NULL;

  /* find an appropriate release in the box */
  release = NULL;
  for (i = 0; i < box->releases.nmemb; i++) {
    if (strcmp(((GttRelease *)box->releases.arr[i])->version, version) == 0 &&
        strcmp(((GttRelease *)box->releases.arr[i])->platform, platform) == 0 &&
        strcmp(((GttRelease *)box->releases.arr[i])->arch, arch) == 0) {
      release = box->releases.arr[i];
      break;
    }
  }

  if (release == NULL) {
    gtt_box_delete(box);

    gtt_error(GTT_NOT_FOUND, "Specified Release has not been found in the Box");
    return NULL;
  }

  snprintf(release_path, GTT_BUFLEN, "Releases/%s/%s/%s/", version, platform,
           arch);

  int entries = zip_get_num_entries(zip, 0);
  for (i = 0; i < entries; i++) {
    entry_path = (char *)zip_get_name(zip, i, 0);

    /* if entry is a directory, ignore */
    if (gtt_str_ends_with(entry_path, "/")) continue;

    /* if the entry belongs to the release */
    if (gtt_str_starts_with(entry_path, release_path)) {
      /* transform the entry path to be relative to the release dir in the zip
       * (just cut the `Release/x/y/z/` at the beginning) */
      release_relative_path = entry_path + strlen(release_path);

      /* transform the path relative to the release dir in the zip to the full
       * path in the tmpdir on the filesystem */
      snprintf(tmpdir_entry_path, GTT_BUFLEN, "%s/%s", tmpdir_path,
               release_relative_path);

      zfd = zip_fopen_index(zip, i, 0);
      zip_stat_index(zip, i, 0, &zfstat);

      fbuf = malloc(zfstat.size);
      zip_fread(zfd, fbuf, zfstat.size);

      gtt_new_file_mkdir_parents(tmpdir_entry_path, fbuf, zfstat.size);

      free(fbuf);
      zip_fclose(zfd);
    }
  }

  gtt_box_delete(box);

  snprintf(buf, bufsize, "%s", tmpdir_path);
  return buf;
}

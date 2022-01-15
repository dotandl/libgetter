/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/box/box.h>
#include <getter/release/version.h>
#include <getter/tools/error.h>
#include <getter/tools/platform.h>
#include <stdio.h>
#include <string.h>

GttBox *gtt_box_new(GttBoxInfo *info, GttPtrArr releases) {
  GttBox *self;

  self = malloc(sizeof(GttBox));
  memset(self, 0, sizeof(GttBox));

  self->info = info;
  self->releases = releases;

  return self;
}

void gtt_box_delete(GttBox *self) {
  int i;

  if (self == NULL) return;

  for (i = 0; i < self->releases.nmemb; i++) {
    if (self->releases.arr[i] != NULL)
      gtt_release_delete(self->releases.arr[i]);
  }

  if (self->info != NULL) gtt_box_info_delete(self->info);
  gtt_ptr_arr_delete(self->releases);

  free(self);
}

GttRelease *gtt_box_get_release(GttBox *self, const char *version,
                                const char *platform, const char *arch) {
  char __platform[GTT_BUFLEN], __arch[GTT_BUFLEN];
  GttRelease *res;
  GttPtrArr arr;
  int i, j;

  res = NULL;
  arr = gtt_ptr_arr_new(0);

  snprintf(__platform, GTT_BUFLEN, "%s",
           platform ? platform : gtt_get_platform());

  snprintf(__arch, GTT_BUFLEN, "%s", arch ? arch : gtt_get_arch());

  __platform[GTT_BUFLEN - 1] = 0;
  __arch[GTT_BUFLEN - 1] = 0;

  if (strncmp(__platform, "", GTT_BUFLEN) == 0 ||
      strncmp(__arch, "", GTT_BUFLEN) == 0) {
    gtt_error(GTT_UNSUPPORTED_HOST,
              "Platform/arch not given; host's platform/arch not supported");
    return NULL;
  }

  j = 0;

  for (i = 0; i < self->releases.nmemb; i++) {
    if (strncmp(((GttRelease *)self->releases.arr[i])->platform, __platform,
                GTT_BUFLEN) == 0 &&
        strncmp(((GttRelease *)self->releases.arr[i])->arch, __arch,
                GTT_BUFLEN) == 0) {
      gtt_ptr_arr_resize(&arr, -1);
      arr.arr[j++] = self->releases.arr[i];
    }
  }

  if (version == NULL) {
    res = gtt_get_latest_release_version(arr);
  } else {
    for (i = 0; i < arr.nmemb; i++) {
      if (strncmp(((GttRelease *)arr.arr[i])->version, version, GTT_BUFLEN) ==
          0) {
        res = arr.arr[i];
        break;
      }
    }
  }

  gtt_ptr_arr_delete(arr);
  gtt_ok();
  return res;
}

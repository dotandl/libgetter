/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#define CVECTOR_LOGARITHMIC_GROWTH

#include <cvector.h>
#include <getter/box/box.h>
#include <getter/release/version.h>
#include <getter/tools/error.h>
#include <getter/tools/platform.h>
#include <string.h>

GttBox *gtt_box_new(GttBoxInfo *info,
                    cvector_vector_type(GttRelease *) releases) {
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

  for (i = 0; i < cvector_size(self->releases); i++) {
    if (self->releases[i] != NULL) gtt_release_delete(self->releases[i]);
  }

  if (self->info != NULL) gtt_box_info_delete(self->info);
  if (self->releases != NULL) cvector_free(self->releases);

  free(self);
}

GttRelease *gtt_box_get_release(GttBox *self, const char *version,
                                const char *platform, const char *arch) {
  char __platform[GTT_BUFLEN], __arch[GTT_BUFLEN];
  GttRelease *res;
  cvector_vector_type(GttRelease *) vec;
  int i;

  res = NULL;
  vec = NULL;

  strncpy(__platform, platform ? platform : gtt_get_platform(), GTT_BUFLEN - 1);
  strncpy(__arch, arch ? arch : gtt_get_arch(), GTT_BUFLEN - 1);

  __platform[GTT_BUFLEN - 1] = 0;
  __arch[GTT_BUFLEN - 1] = 0;

  if (strncmp(__platform, "", GTT_BUFLEN) == 0 ||
      strncmp(__arch, "", GTT_BUFLEN) == 0) {
    gtt_error(GTT_UNSUPPORTED_HOST,
              "Platform/arch not given; host's platform/arch not supported");
    return NULL;
  }

  for (i = 0; i < cvector_size(self->releases); i++) {
    if (strncmp(self->releases[i]->platform, __platform, GTT_BUFLEN) == 0 &&
        strncmp(self->releases[i]->arch, __arch, GTT_BUFLEN) == 0) {
      cvector_push_back(vec, self->releases[i]);
    }
  }

  if (version == NULL) {
    res = gtt_get_latest_release_version(vec);
  } else {
    for (i = 0; i < cvector_size(vec); i++) {
      if (strncmp(vec[i]->version, version, GTT_BUFLEN) == 0) {
        res = vec[i];
        break;
      }
    }
  }

  cvector_free(vec);
  gtt_ok();
  return res;
}

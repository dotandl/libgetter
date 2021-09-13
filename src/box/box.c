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

GttBox *gtt_box_new(GttBoxInfo *info, GttVector_release *releases) {
  GttBox *self;

  self = malloc(sizeof(GttBox));
  memset(self, 0, sizeof(GttBox));

  self->info = info;
  self->releases = releases;

  return self;
}

void gtt_box_delete(GttBox *self) {
  GttVectorNode_release *node;

  if (self == NULL) return;

  gtt_vector_for_each(self->releases, node) {
    if (node->value != NULL) gtt_release_delete(node->value);
  }

  if (self->info != NULL) gtt_box_info_delete(self->info);
  if (self->releases != NULL) gtt_vector_release_delete(self->releases);

  free(self);
}

#define __BUFSIZE 16

GttRelease *gtt_box_get_release(GttBox *self, const char *version,
                                const char *platform, const char *arch) {
  char __platform[__BUFSIZE], __arch[__BUFSIZE];
  GttRelease *res;
  GttVector_release *vec;
  GttVectorNode_release *node;

  res = NULL;
  vec = gtt_vector_release_new();

  strncpy(__platform, platform ? platform : gtt_get_platform(), __BUFSIZE - 1);
  strncpy(__arch, arch ? arch : gtt_get_arch(), __BUFSIZE - 1);

  if (strncmp(__platform, "", __BUFSIZE - 1) == 0 ||
      strncmp(__arch, "", __BUFSIZE - 1) == 0) {
    gtt_error(GTT_UNSUPPORTED_HOST,
              "Platform/arch not given; host's platform/arch not supported");
    return NULL;
  }

  gtt_vector_for_each(self->releases, node) {
    if (strncmp(node->value->platform, __platform, __BUFSIZE - 1) == 0 &&
        strncmp(node->value->arch, __arch, __BUFSIZE - 1) == 0) {
      gtt_vector_release_push(vec, node->value);
    }
  }

  if (version == NULL) {
    res = gtt_get_latest_release_version(vec);
  } else {
    gtt_vector_for_each(vec, node) {
      if (strncmp(node->value->version, version, __BUFSIZE - 1) == 0) {
        res = node->value;
        break;
      }
    }
  }

  gtt_vector_release_delete(vec);
  gtt_ok();
  return res;
}

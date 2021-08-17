/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/box/box.h>

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

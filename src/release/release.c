/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/release/release.h>
#include <re.h>

GttRelease *gtt_release_new(const char *platform, const char *arch,
                            const char *version) {
  GttRelease *self;
  re_t regexp;
  int match_idx, matched_elements;

  regexp = re_compile("[0-9]+\\.[0-9]+\\.[0-9]+");
  match_idx = re_matchp(regexp, version, &matched_elements);

  if (match_idx == -1) return NULL;  // invalid version

  self = malloc(sizeof(GttRelease));
  memset(self, 0, sizeof(GttRelease));

  self->platform = calloc(strlen(platform) + 1, sizeof(char));
  self->arch = calloc(strlen(arch) + 1, sizeof(char));
  self->version = calloc(strlen(version) + 1, sizeof(char));

  strcpy((char *)self->platform, platform);
  strcpy((char *)self->arch, arch);
  strcpy((char *)self->version, version);

  return self;
}

void gtt_release_delete(GttRelease *self) {
  if (self == NULL) return;

  if (self->platform != NULL) free((char *)self->platform);
  if (self->arch != NULL) free((char *)self->arch);
  if (self->version != NULL) free((char *)self->version);

  free(self);
}

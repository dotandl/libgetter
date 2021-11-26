/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#define PCRE2_CODE_UNIT_WIDTH 8

#include <getter/release/release.h>
#include <getter/tools/error.h>
#include <pcre2.h>
#include <stdio.h>
#include <string.h>

GttRelease *gtt_release_new(const char *platform, const char *arch,
                            const char *version) {
  GttRelease *self;
  pcre2_code *regexp;
  pcre2_match_data *match_data;
  PCRE2_SIZE error_offset;
  int error_code, matches;

  // Regexp checking if version field contains MAJOR.MINOR.PATCH substring.
  regexp = pcre2_compile("[0-9]+\\.[0-9]+\\.[0-9]+", PCRE2_ZERO_TERMINATED, 0,
                         &error_code, &error_offset, NULL);

  if (regexp == NULL) {
    gtt_error(GTT_REGEXP_COMPILATION_FAILED, "Could not compile regexp");
    return NULL;
  }

  match_data = pcre2_match_data_create_from_pattern(regexp, NULL);
  matches =
      pcre2_match(regexp, version, strlen(version), 0, 0, match_data, NULL);

  if (matches < 0) {
    pcre2_match_data_free(match_data);
    pcre2_code_free(regexp);

    gtt_error(GTT_INVALID_VERSION,
              "Version not matched MAJOR.MINOR.PATCH pattern");
    return NULL;
  }

  self = malloc(sizeof(GttRelease));
  memset(self, 0, sizeof(GttRelease));

  self->platform = calloc(strlen(platform) + 1, sizeof(char));
  self->arch = calloc(strlen(arch) + 1, sizeof(char));
  self->version = calloc(strlen(version) + 1, sizeof(char));

  snprintf((char *)self->platform, strlen(platform) + 1, "%s", platform);
  snprintf((char *)self->arch, strlen(arch) + 1, "%s", arch);
  snprintf((char *)self->version, strlen(version) + 1, "%s", version);

  pcre2_match_data_free(match_data);
  pcre2_code_free(regexp);

  gtt_ok();
  return self;
}

void gtt_release_delete(GttRelease *self) {
  if (self == NULL) return;

  if (self->platform != NULL) free((char *)self->platform);
  if (self->arch != NULL) free((char *)self->arch);
  if (self->version != NULL) free((char *)self->version);

  free(self);
}

/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/release/extracted_release.h>
#include <getter/types/array.h>
#include <stdio.h>
#include <string.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

static void gtt_merge_cstr_arrs(GttCStrArr arr, GttCStrArr *dest);
static void gtt_cstr_arr_copy(GttCStrArr arr, GttCStrArr *dest);

GttExtractedRelease *gtt_extracted_release_new(GttRelease *r,
                                               GttReleaseInfo *ri,
                                               GttBoxInfo *bi) {
  GttExtractedRelease *self;
  char *ptr;
  unsigned int i;

  self = malloc(sizeof(GttExtractedRelease));
  memset(self, 0, sizeof(GttExtractedRelease));

  /* Copy GttRelease */
  snprintf((char *)self->platform, GTT_BUFLEN, "%s", r->platform);
  snprintf((char *)self->arch, GTT_BUFLEN, "%s", r->arch);
  snprintf((char *)self->version, GTT_BUFLEN, "%s", r->version);

  /* Copy always-present strings */
  snprintf((char *)self->script, GTT_BUFLEN, "%s", ri->script);
  snprintf((char *)self->name, GTT_BUFLEN, "%s", bi->name);
  snprintf((char *)self->full_name, GTT_BUFLEN, "%s", bi->full_name);
  snprintf((char *)self->summary, GTT_BUFLEN, "%s", bi->summary);
  snprintf((char *)self->license_name, GTT_BUFLEN, "%s", bi->license_name);

  /* Copy optional strings */
  if (strcmp(bi->getter, "") != 0)
    snprintf((char *)self->getter, GTT_BUFLEN, "%s", bi->getter);
  if (strcmp(bi->description, "") != 0)
    snprintf((char *)self->description, GTT_BUFLEN, "%s", bi->description);
  if (strcmp(bi->homepage, "") != 0)
    snprintf((char *)self->homepage, GTT_BUFLEN, "%s", bi->homepage);
  if (strcmp(bi->repository, "") != 0)
    snprintf((char *)self->repository, GTT_BUFLEN, "%s", bi->repository);
  if (strcmp(bi->license, "") != 0)
    snprintf((char *)self->license, GTT_BUFLEN, "%s", bi->license);
  if (strcmp(bi->readme, "") != 0)
    snprintf((char *)self->readme, GTT_BUFLEN, "%s", bi->readme);
  if (strcmp(bi->changelog, "") != 0)
    snprintf((char *)self->changelog, GTT_BUFLEN, "%s", bi->changelog);

  /* Copy always-present vectors of strings */
  gtt_cstr_arr_copy(bi->authors, &self->authors);

  /* Copy optional vectors of strings */
  if (bi->categories.nmemb != 0)
    gtt_cstr_arr_copy(bi->categories, &self->categories);
  if (bi->dependencies.nmemb != 0)
    gtt_cstr_arr_copy(bi->dependencies, &self->dependencies);
  if (bi->build_dependencies.nmemb != 0)
    gtt_cstr_arr_copy(bi->build_dependencies, &self->build_dependencies);
  if (bi->optional_dependencies.nmemb != 0)
    gtt_cstr_arr_copy(bi->optional_dependencies, &self->optional_dependencies);
  if (bi->conflicts.nmemb != 0)
    gtt_cstr_arr_copy(bi->conflicts, &self->conflicts);
  if (bi->replaces.nmemb != 0) gtt_cstr_arr_copy(bi->replaces, &self->replaces);

  /* Replace strings */
  if (strcmp(ri->repository, "") != 0)
    snprintf((char *)self->repository, GTT_BUFLEN, "%s", ri->repository);
  if (strcmp(ri->license_name, "") != 0)
    snprintf((char *)self->license_name, GTT_BUFLEN, "%s", ri->license_name);
  if (strcmp(ri->license, "") != 0)
    snprintf((char *)self->license, GTT_BUFLEN, "%s", ri->license);
  if (strcmp(ri->readme, "") != 0)
    snprintf((char *)self->readme, GTT_BUFLEN, "%s", ri->readme);
  if (strcmp(ri->changelog, "") != 0)
    snprintf((char *)self->changelog, GTT_BUFLEN, "%s", ri->changelog);

  /* Append values from vectors to existing vectors */
  if (ri->dependencies.nmemb != 0)
    gtt_merge_cstr_arrs(ri->dependencies, &self->dependencies);
  if (ri->build_dependencies.nmemb != 0)
    gtt_merge_cstr_arrs(ri->build_dependencies, &self->build_dependencies);
  if (ri->optional_dependencies.nmemb != 0)
    gtt_merge_cstr_arrs(ri->optional_dependencies,
                        &self->optional_dependencies);
  if (ri->conflicts.nmemb != 0)
    gtt_merge_cstr_arrs(ri->conflicts, &self->conflicts);
  if (ri->replaces.nmemb != 0)
    gtt_merge_cstr_arrs(ri->replaces, &self->replaces);

  return self;
}

void gtt_extracted_release_delete(GttExtractedRelease *self) {
  if (self == NULL) return;

  gtt_cstr_arr_delete(self->authors);
  gtt_cstr_arr_delete(self->categories);
  gtt_cstr_arr_delete(self->dependencies);
  gtt_cstr_arr_delete(self->build_dependencies);
  gtt_cstr_arr_delete(self->optional_dependencies);
  gtt_cstr_arr_delete(self->conflicts);
  gtt_cstr_arr_delete(self->replaces);

  free(self);
}

void gtt_merge_cstr_arrs(GttCStrArr arr, GttCStrArr *dest) {
  GttCStrArr ret;
  unsigned int i;
  char *ptr;

  const size_t nmemb = dest->nmemb + arr.nmemb;
  const size_t el_size = max(dest->size, arr.size);

  ret = gtt_cstr_arr_new(nmemb, el_size);

  for (i = 0; i < nmemb; i++) {
    snprintf((char *)ret.arr[i], el_size, "%s",
             i < dest->nmemb ? dest->arr[i] : arr.arr[dest->nmemb - nmemb + i]);
  }

  gtt_cstr_arr_delete(*dest);
  *dest = ret;
}

void gtt_cstr_arr_copy(GttCStrArr arr, GttCStrArr *dest) {
  unsigned int i;
  char *ptr;

  *dest = gtt_cstr_arr_new(arr.nmemb, arr.size);

  for (i = 0; i < arr.nmemb; i++) {
    snprintf((char *)dest->arr[i], arr.size, "%s", arr.arr[i]);
  }
}

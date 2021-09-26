/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/release/info.h>
#include <getter/tools/error.h>

#define CVECTOR_LOGARITHMIC_GROWTH

#include <cvector.h>
#include <string.h>

static void pkvf_str_alloc_copy(GttPKVFToken *token, char **dest);
static void pkvf_arr_to_vec(GttPKVFToken *token,
                            cvector_vector_type(char *) * vec);

GttReleaseInfo *gtt_release_info_new_from_pkvf(const char *pkvf) {
  GttReleaseInfo *self;
  GttPKVFToken *token;
  cvector_vector_type(GttPKVFToken) vec;
  int i;

  vec = gtt_parse_pkvf(pkvf);
  if (GTT_FAILED) return NULL;  // forward the error

  self = malloc(sizeof(GttReleaseInfo));
  memset(self, 0, sizeof(GttReleaseInfo));

  for (i = 0; i < cvector_size(vec); i++) {
    token = &vec[i];

    switch (token->type) {
      case GTT_PKVF_STRING_TOKEN:
        if (strcmp(token->key, "repository") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->repository);
        } else if (strcmp(token->key, "license_name") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->license_name);
        } else if (strcmp(token->key, "license") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->license);
        } else if (strcmp(token->key, "readme") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->readme);
        } else if (strcmp(token->key, "changelog") == 0) {
          pkvf_str_alloc_copy(token, (char **)&self->changelog);
        } else {
          gtt_vector_pkvf_token_free(vec);
          gtt_release_info_delete(self);

          gtt_error(GTT_INVALID_DATA, "Unexpected token found");
          return NULL;
        }
        break;

      case GTT_PKVF_STRING_VECTOR_TOKEN:
        if (strcmp(token->key, "dependencies") == 0) {
          pkvf_arr_to_vec(token, &self->dependencies);
        } else if (strcmp(token->key, "build_dependencies") == 0) {
          pkvf_arr_to_vec(token, &self->build_dependencies);
        } else if (strcmp(token->key, "optional_dependencies") == 0) {
          pkvf_arr_to_vec(token, &self->optional_dependencies);
        } else if (strcmp(token->key, "conflicts") == 0) {
          pkvf_arr_to_vec(token, &self->conflicts);
        } else if (strcmp(token->key, "replaces") == 0) {
          pkvf_arr_to_vec(token, &self->replaces);
        } else {
          gtt_vector_pkvf_token_free(vec);
          gtt_release_info_delete(self);

          gtt_error(GTT_INVALID_DATA, "Unexpected token found");
          return NULL;
        }
        break;
    }
  }

  gtt_vector_pkvf_token_free(vec);
  gtt_ok();
  return self;
}

#define free_all_strings(vec)                 \
  do {                                        \
    int i;                                    \
    if ((vec) != NULL)                        \
      for (i = 0; i < cvector_size(vec); i++) \
        if ((vec)[i] != NULL) free((vec)[i]); \
  } while (0)

void gtt_release_info_delete(GttReleaseInfo *self) {
  if (self == NULL) return;

  if (self->repository != NULL) free((char *)self->repository);
  if (self->license_name != NULL) free((char *)self->license_name);
  if (self->license != NULL) free((char *)self->license);
  if (self->readme != NULL) free((char *)self->readme);
  if (self->changelog != NULL) free((char *)self->changelog);

  free_all_strings(self->dependencies);
  free_all_strings(self->build_dependencies);
  free_all_strings(self->optional_dependencies);
  free_all_strings(self->conflicts);
  free_all_strings(self->replaces);

  cvector_free(self->dependencies);
  cvector_free(self->build_dependencies);
  cvector_free(self->optional_dependencies);
  cvector_free(self->conflicts);
  cvector_free(self->replaces);

  free(self);
}

void pkvf_str_alloc_copy(GttPKVFToken *token, char **dest) {
  *dest = calloc(strlen(token->val.str) + 1, sizeof(char));
  strcpy(*dest, token->val.str);
}

void pkvf_arr_to_vec(GttPKVFToken *token, cvector_vector_type(char *) * vec) {
  int i;
  char *str;

  *vec = NULL;

  for (i = 0; i < cvector_size(token->val.vec); i++) {
    str = calloc(strlen(token->val.vec[i]) + 1, sizeof(char));
    strcpy(str, token->val.vec[i]);

    // *vec needs to be surrounded by () because of bug in the c-vector lib
    cvector_push_back((*vec), str);
  }
}

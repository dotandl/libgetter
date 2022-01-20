/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/tools/error.h>
#include <getter/types/array.h>

GttCStrArr gtt_cstr_arr_new(size_t nmemb, size_t size) {
  char **ptr;
  size_t i;

  /* Allocate array of pointers on the heap */
  ptr = (char **)calloc(nmemb, sizeof(char *));

  /* Allocate arrays of chars (strings) and put them in the array of pointers */
  for (i = 0; i < nmemb; i++) {
    ptr[i] = (char *)calloc(size, sizeof(char));
  }

  return (GttCStrArr){(const char **)ptr, nmemb, size};
}

void gtt_cstr_arr_delete(GttCStrArr self) {
  size_t i;

  /* Free arrays of chars (strings) */
  for (i = 0; i < self.nmemb; i++) free((void *)self.arr[i]);

  /* Free array of pointers */
  free(self.arr);
}

GttPtrArr gtt_ptr_arr_new(size_t nmemb) {
  void **ptr;
  ptr = calloc(nmemb, sizeof(void *));
  return (GttPtrArr){ptr, nmemb};
}

void gtt_ptr_arr_resize(GttPtrArr *self, int nmemb) {
  if (nmemb == -1) {
    nmemb = self->nmemb + 1;
  }

  if (nmemb <= self->nmemb) {
    gtt_error(GTT_ARR_RESIZE_FAILED,
              "New number of elements in the array is smaller than or equal to "
              "the current one");
    return;
  }

  self->nmemb = nmemb;
  self->arr = realloc(self->arr, nmemb * sizeof(void *));
  gtt_ok();
}

void gtt_ptr_arr_delete_all(GttPtrArr self) {
  size_t i;

  for (i = 0; i < self.nmemb; i++) {
    free(self.arr[i]);
  }

  free(self.arr);
}

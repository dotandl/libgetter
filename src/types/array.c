/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

#include <getter/types/array.h>
#include <stdlib.h>

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

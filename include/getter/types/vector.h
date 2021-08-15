/*
 * +----------------------------------------------------------+
 * | libgetter - part of Getter Package Manager               |
 * | Licensed under the GNU GPLv3 License. See LICENSE.txt    |
 * |                                                          |
 * | Copyright (C) 2021 dotandl                               |
 * +----------------------------------------------------------+
 */

/**
 * \file vector.h
 * Header-only built-in Vector library.
 *
 * Vector is a dynamically sized linked list.
 * Usage:
 * \code
 * #define GTT_VEC_TYPE int // We'll use Vector of integers
 * #define GTT_VEC_NAME integer // Vector type will be GttVector_integer
 * #include <getter/types/vector.h>
 *
 * // Inside a function
 * GttVector_integer *vec = gtt_vector_integer_new();
 * gtt_vector_integer_push(vec, 1);
 * gtt_vector_integer_push(vec, 12);
 * gtt_vector_integer_push(vec, 123);
 *
 * int element = gtt_vector_integer_get(vec, 1)->value; // Will be 12
 * int index = gtt_vector_integer_index_of(vec, 123); // Will be 2
 *
 * gtt_vector_integer_delete(vec);
 * \endcode
 *
 * Note that if you want to create a string Vector you'll need to define another
 * macro to tell Vector how to compare strings:
 * \code
 * #define GTT_VEC_TYPE char *
 * #define GTT_VEC_NAME string
 *
 * #include <string.h>
 * // Use strcmp() to compare strings instead of == operator
 * #define gtt_vec_compare_elements(el1, el2) strcmp(el1, el2) == 0
 *
 * #include <getter/types/vector.h>
 *
 * // ...
 * \endcode
 *
 * Types:
 * - `GttVector_<GTT_VEC_NAME>`
 * - `GttVectorNode_<GTT_VEC_NAME>`
 *
 * Functions:
 * - `GttVector_<GTT_VEC_NAME> *gtt_vector_<GTT_VEC_NAME>_new(void)`
 * - `void gtt_vector_<GTT_VEC_NAME>_delete(GttVector_<GTT_VEC_NAME> *self)`
 * - `<GTT_VEC_TYPE> gtt_vector_<GTT_VEC_NAME>_get(GttVector_<GTT_VEC_NAME>
 * *self, unsigned int idx)`
 * - `int gtt_vector_<GTT_VEC_NAME>_index_of(GttVector_<GTT_VEC_NAME> *self,
 * <GTT_VEC_TYPE> val)`
 * - `void gtt_vector_<GTT_VEC_NAME>_unshift(GttVector_<GTT_VEC_NAME> *self,
 * <GTT_VEC_TYPE> val)`
 * - `void gtt_vector_<GTT_VEC_NAME>_push(GttVector_<GTT_VEC_NAME> *self,
 * <GTT_VEC_TYPE> val)`
 * - `void gtt_vector_<GTT_VEC_NAME>_insert(GttVector_<GTT_VEC_NAME> *self,
 * <GTT_VEC_TYPE> val, unsigned int idx)`
 * - `void gtt_vector_<GTT_VEC_NAME>_remove_first(GttVector_<GTT_VEC_NAME>
 * *self)`
 * - `void gtt_vector_<GTT_VEC_NAME>_remove_last(GttVector_<GTT_VEC_NAME>
 * *self)`
 * - `void gtt_vector_<GTT_VEC_NAME>_remove(GttVector_<GTT_VEC_NAME> *self,
 * unsigned int idx)`
 *
 * Macros:
 * - `gtt_vector_for_each(vec, node)`
 */

#include <getter/decl.h>
#include <stdlib.h>

HEADER_BEGIN

#ifndef GTT_VEC_TYPE
#error GTT_VEC_TYPE not defined.
#endif

#ifndef GTT_VEC_NAME
#error GTT_VEC_NAME not defined.
#endif

#if !defined(gtt_vec_compare_elements) && !defined(GTT_VEC_DISABLE_INDEX_OF)
#define gtt_vec_compare_elements(el1, el2) (el1) == (el2)
#endif

#define __strcat_(str1, str2) str1##str2
#define __strcat(str1, str2) __strcat_(str1, str2)

#define __GTT_VECTOR __strcat(GttVector_, GTT_VEC_NAME)
#define __GTT_VECTOR_NODE __strcat(GttVectorNode_, GTT_VEC_NAME)
#define __gtt_vector_func(func) \
  __strcat(gtt_vector_, __strcat(GTT_VEC_NAME, __strcat(_, func)))

#define gtt_vector_for_each(vec, node) \
  if ((vec)->length > 0)               \
    for ((node) = (vec)->first; (node) != NULL; (node) = (node)->next)

typedef struct __GTT_VECTOR __GTT_VECTOR;
typedef struct __GTT_VECTOR_NODE __GTT_VECTOR_NODE;

struct __GTT_VECTOR {
  __GTT_VECTOR_NODE *first, *last;
  unsigned int length;
};

struct __GTT_VECTOR_NODE {
  GTT_VEC_TYPE value;
  __GTT_VECTOR_NODE *next;
};

static __GTT_VECTOR *__gtt_vector_func(new)(void) {
  __GTT_VECTOR *self;

  self = (__GTT_VECTOR *)malloc(sizeof(__GTT_VECTOR));
  self->first = NULL;
  self->last = NULL;
  self->length = 0;

  return self;
}

static void __gtt_vector_func(delete)(__GTT_VECTOR *self) {
  __GTT_VECTOR_NODE *node;
  __GTT_VECTOR_NODE *nextNode;

  if (self == NULL) return;

  node = self->first;

  while (node != NULL) {
    nextNode = node->next;
    free(node);
    node = nextNode;
  }

  free(self);
}

static __GTT_VECTOR_NODE *__gtt_vector_func(get)(__GTT_VECTOR *self,
                                                 unsigned int idx) {
  __GTT_VECTOR_NODE *node;
  unsigned int i;

  if (idx > self->length) return NULL;

  node = self->first;

  for (i = 0; i < idx; i++) {
    node = node->next;
  }

  return node;
}

#ifndef GTT_VEC_DISABLE_INDEX_OF
static int __gtt_vector_func(index_of)(__GTT_VECTOR *self, GTT_VEC_TYPE val) {
  __GTT_VECTOR_NODE *node;
  unsigned int i;

  if (self->length == 0) return -1;

  node = self->first;
  i = 0;

  while (!(gtt_vec_compare_elements(node->value, val))) {
    i++;
    node = node->next;

    if (node == NULL) return -1;
  }

  return i;
}
#endif

static void __gtt_vector_func(unshift)(__GTT_VECTOR *self, GTT_VEC_TYPE val) {
  __GTT_VECTOR_NODE *node;

  node = (__GTT_VECTOR_NODE *)malloc(sizeof(__GTT_VECTOR_NODE));
  node->value = val;

  node->next = self->first;
  self->first = node;

  if (self->length == 0) self->last = self->first;
  self->length++;
}

static void __gtt_vector_func(push)(__GTT_VECTOR *self, GTT_VEC_TYPE val) {
  __GTT_VECTOR_NODE *node;

  if (self->length == 0) {
    __gtt_vector_func(unshift)(self, val);
    return;
  }

  node = (__GTT_VECTOR_NODE *)malloc(sizeof(__GTT_VECTOR_NODE));
  node->value = val;
  node->next = NULL;

  self->last->next = node;
  self->last = node;

  self->length++;
}

static void __gtt_vector_func(insert)(__GTT_VECTOR *self, GTT_VEC_TYPE val,
                                      unsigned int idx) {
  __GTT_VECTOR_NODE *prevNode, *nextNode, *node;
  unsigned int i;

  if (idx > self->length) return;

  if (idx == 0) {
    __gtt_vector_func(unshift)(self, val);
    return;
  }

  if (idx == self->length) {
    __gtt_vector_func(push)(self, val);
    return;
  }

  node = (__GTT_VECTOR_NODE *)malloc(sizeof(__GTT_VECTOR_NODE));
  node->value = val;

  prevNode = self->first;
  for (i = 0; i < idx - 1; i++) {
    prevNode = prevNode->next;
  }

  nextNode = prevNode->next;
  node->next = nextNode;
  prevNode->next = node;

  self->length++;
}

static void __gtt_vector_func(remove_first)(__GTT_VECTOR *self) {
  __GTT_VECTOR_NODE *node;

  if (self->length == 0) return;

  node = self->first;
  self->first = self->first->next;

  free(node);
  self->length--;
}

static void __gtt_vector_func(remove_last)(__GTT_VECTOR *self) {
  __GTT_VECTOR_NODE *prevNode, *node;

  if (self->length == 0) return;

  if (self->length == 1) {
    __gtt_vector_func(remove_first)(self);
    return;
  }

  prevNode = self->first;
  node = self->first->next;

  while (node->next != NULL) {
    prevNode = prevNode->next;
    node = node->next;
  }

  prevNode->next = NULL;
  self->last = prevNode;

  free(node);
  self->length--;
}

static void __gtt_vector_func(remove)(__GTT_VECTOR *self, unsigned int idx) {
  __GTT_VECTOR_NODE *prevNode, *nextNode, *node;
  unsigned int i;

  if (self->length == 0) return;
  if (idx > self->length) return;

  if (idx == 0) {
    __gtt_vector_func(remove_first)(self);
    return;
  }

  if (idx == self->length) {
    __gtt_vector_func(remove_last)(self);
    return;
  }

  prevNode = self->first;

  for (i = 0; i < idx - 1; i++) {
    prevNode = prevNode->next;
  }

  node = prevNode->next;
  nextNode = node->next;
  prevNode->next = nextNode;

  free(node);
  self->length--;
}

#undef __strcat
#undef __strcat_

#undef __GTT_VECTOR
#undef __GTT_VECTOR_NODE
#undef __gtt_vector_func

HEADER_END

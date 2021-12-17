#ifndef TREE_SITTER_ALLOC_H_
#define TREE_SITTER_ALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#if defined(TREE_SITTER_ALLOCATION_TRACKING)

void *ts_record_malloc(size_t);
void *ts_record_calloc(size_t, size_t);
void *ts_record_realloc(void *, size_t);
void ts_record_free(void *);
bool ts_toggle_allocation_recording(bool);

#define ts_malloc  ts_record_malloc
#define ts_calloc  ts_record_calloc
#define ts_realloc ts_record_realloc
#define ts_free    ts_record_free

#else

// Allow clients to override allocation functions

#ifndef ts_malloc
#define ts_malloc  ts_malloc_default
#endif
#ifndef ts_calloc
#define ts_calloc  ts_calloc_default
#endif
#ifndef ts_realloc
#define ts_realloc ts_realloc_default
#endif
#ifndef ts_free
#define ts_free    ts_free_default
#endif

void *ts_malloc_default(size_t) __attribute__((weak));
void *ts_calloc_default(size_t, size_t) __attribute__((weak));
void *ts_realloc_default(void *, size_t) __attribute__((weak));
void ts_free_default(void *) __attribute__((weak));
bool ts_toggle_allocation_recording(bool) __attribute__((weak));

#endif

#ifdef __cplusplus
}
#endif

#endif  // TREE_SITTER_ALLOC_H_

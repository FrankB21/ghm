/*
MIT License

Copyright (c) 2021 FrankB21

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef GHM_H
#define GHM_H 1

#include <stdbool.h>
#include <stdlib.h>

#include <stdint.h>

#define GHM_MIN_BUCKETS 10

typedef struct ghm_hashmap ghm_hashmap_t;

typedef uintptr_t ghm_key_t;

typedef void *ghm_generic_t;

enum ghm_keytype {
    GHM_KEY_INTEGRAL,
    GHM_KEY_STRING
};

typedef union ghm_value {
    int32_t       i32;
    uint32_t      u32;
    int64_t       i64;
    uint64_t      u64;
    float         flt;
    double        dbl;
    ghm_generic_t ptr;
} ghm_value_t;

// Creation and destruction functions

ghm_hashmap_t *ghm_create(size_t buckets, enum ghm_keytype keytype);
void           ghm_destroy(ghm_hashmap_t *map);

// Setting functions

bool ghm_set(ghm_hashmap_t *map, ghm_key_t key, ghm_value_t value);

bool ghm_setint32(ghm_hashmap_t *map, ghm_key_t key, int32_t value);
bool ghm_setuint32(ghm_hashmap_t *map, ghm_key_t key, uint32_t value);

bool ghm_setint64(ghm_hashmap_t *map, ghm_key_t key, int64_t value);
bool ghm_setuint64(ghm_hashmap_t *map, ghm_key_t key, uint64_t value);

bool ghm_setfloat(ghm_hashmap_t *map, ghm_key_t key, float value);
bool ghm_setdouble(ghm_hashmap_t *map, ghm_key_t key, double value);

bool ghm_setptr(ghm_hashmap_t *map, ghm_key_t key, ghm_generic_t value);

// Getting functions

bool ghm_get(const ghm_hashmap_t *map, ghm_key_t key, ghm_value_t *value);

bool ghm_getint32(const ghm_hashmap_t *map, ghm_key_t key, int32_t *value);
bool ghm_getuint32(const ghm_hashmap_t *map, ghm_key_t key, uint32_t *value);

bool ghm_getint64(const ghm_hashmap_t *map, ghm_key_t key, int64_t *value);
bool ghm_getuint64(const ghm_hashmap_t *map, ghm_key_t key, uint64_t *value);

bool ghm_getfloat(const ghm_hashmap_t *map, ghm_key_t key, float *value);
bool ghm_getdouble(const ghm_hashmap_t *map, ghm_key_t key, double *value);

bool ghm_getptr(const ghm_hashmap_t *map, ghm_key_t key, ghm_generic_t *value);

// Removal functions

bool ghm_remove(ghm_hashmap_t *map, ghm_key_t key);

#endif// GHM_H

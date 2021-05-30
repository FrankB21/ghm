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

#ifndef HM_INTERNAL_H
#define HM_INTERNAL_H 1

#include "ghm.h"

typedef struct ghm_kvpair
{
    ghm_key_t   key;
    ghm_value_t value;
} ghm_kvpair_t;

typedef struct ghm_node
{
    ghm_kvpair_t kv_pair;

    struct ghm_node *next;
} ghm_node_t;

struct ghm_hashmap
{
    ghm_node_t **lists;
    size_t       buckets;

    enum ghm_keytype keytype;
};

size_t ghm_hash(const ghm_hashmap_t *map, ghm_key_t key);

size_t ghm_hashint(ghm_key_t key);
size_t ghm_hashstring(ghm_key_t key);

#endif// HM_INTERNAL_H

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

#include "ghm.h"
#include "ghm_internal.h"

#include <string.h>

ghm_hashmap_t *ghm_create(size_t buckets, enum ghm_keytype keytype)
{
    ghm_hashmap_t *map;

    if (buckets < GHM_MIN_BUCKETS) buckets = GHM_MIN_BUCKETS;

    map = malloc(sizeof(ghm_hashmap_t));

    if (map == NULL) return NULL;

    map->buckets = buckets;
    map->lists   = calloc(buckets, sizeof(ghm_node_t *));

    if (map->lists == NULL)
    {
        free(map);
        return NULL;
    }

    if (keytype != GHM_KEY_INTEGRAL && keytype != GHM_KEY_STRING)
    {
        ghm_destroy(map);
        return NULL;
    }

    map->keytype = keytype;

    return map;
}

void ghm_destroy(ghm_hashmap_t *map)
{
    if (map == NULL) return;

    for (size_t i = 0; i < map->buckets; ++i)
    {
        //ghm_node_t **probe = &map->lists[i];
        ghm_node_t *curr = map->lists[i], *tmp;

        while (curr != NULL)
        {
            tmp   = curr;
            curr  = curr->next;
            free(tmp);
        }
    }

    free(map->lists);
    free(map);
}

bool ghm_set(ghm_hashmap_t *map, ghm_key_t key, ghm_value_t value)
{
    if (map == NULL) return false;

    ghm_node_t **probe = &map->lists[ghm_hash(map, key)];

    while ((*probe) != NULL)
    {
        bool keys_equal;

        switch (map->keytype)
        {
        case GHM_KEY_INTEGRAL:
            keys_equal = (*probe)->kv_pair.key == key;
            break;
        case GHM_KEY_STRING:
            keys_equal = strcmp((const char *)(*probe)->kv_pair.key, (const char *)key) == 0;
            break;
        }

        if (keys_equal) break;

        probe = &(*probe)->next;
    }

    if ((*probe) == NULL)
    {
        (*probe) = malloc(sizeof(ghm_node_t));

        if (*probe == NULL) return false;

        (*probe)->kv_pair.key = key;
        //(*probe)->kv_pair.value = value;
        (*probe)->next = NULL;
    }

    (*probe)->kv_pair.value = value;

    return true;
}

bool ghm_setint32(ghm_hashmap_t *map, ghm_key_t key, int32_t value)
{
    return ghm_set(map, key, (ghm_value_t){ .i32 = value });
}

bool ghm_setuint32(ghm_hashmap_t *map, ghm_key_t key, uint32_t value)
{
    return ghm_set(map, key, (ghm_value_t){ .u32 = value });
}

bool ghm_setint64(ghm_hashmap_t *map, ghm_key_t key, int64_t value)
{
    return ghm_set(map, key, (ghm_value_t){ .i64 = value });
}

bool ghm_setuint64(ghm_hashmap_t *map, ghm_key_t key, uint64_t value)
{
    return ghm_set(map, key, (ghm_value_t){ .u64 = value });
}

bool ghm_setfloat(ghm_hashmap_t *map, ghm_key_t key, float value)
{
    return ghm_set(map, key, (ghm_value_t){ .flt = value });
}

bool ghm_setdouble(ghm_hashmap_t *map, ghm_key_t key, double value)
{
    return ghm_set(map, key, (ghm_value_t){ .dbl = value });
}

bool ghm_setptr(ghm_hashmap_t *map, ghm_key_t key, ghm_generic_t value)
{
    return ghm_set(map, key, (ghm_value_t){ .ptr = value });
}

bool ghm_get(const ghm_hashmap_t *map, ghm_key_t key, ghm_value_t *value)
{
    if (map == NULL) return false;


    ghm_node_t **probe = &map->lists[ghm_hash(map, key)];

    while ((*probe) != NULL)
    {
        bool keys_equal;

        switch (map->keytype)
        {
        case GHM_KEY_INTEGRAL:
            keys_equal = (*probe)->kv_pair.key == key;
            break;
        case GHM_KEY_STRING:
            keys_equal = strcmp((const char *)(*probe)->kv_pair.key, (const char *)key) == 0;
            break;
        }

        if (keys_equal) break;

        probe = &(*probe)->next;
    }

    if ((*probe) == NULL) return false;

    *value = (*probe)->kv_pair.value;

    return true;
}

bool ghm_getint32(const ghm_hashmap_t *map, ghm_key_t key, int32_t *value)
{
    ghm_value_t union_value;

    bool retval = ghm_get(map, key, &union_value);

    *value = union_value.i32;
    return retval;
}

bool ghm_getuint32(const ghm_hashmap_t *map, ghm_key_t key, uint32_t *value)
{
    ghm_value_t union_value;

    bool retval = ghm_get(map, key, &union_value);

    *value = union_value.u32;
    return retval;
}

bool ghm_getint64(const ghm_hashmap_t *map, ghm_key_t key, int64_t *value)
{
    ghm_value_t union_value;

    bool retval = ghm_get(map, key, &union_value);

    *value = union_value.i64;
    return retval;
}

bool ghm_getuint64(const ghm_hashmap_t *map, ghm_key_t key, uint64_t *value)
{
    ghm_value_t union_value;

    bool retval = ghm_get(map, key, &union_value);

    *value = union_value.u64;
    return retval;
}

bool ghm_getfloat(const ghm_hashmap_t *map, ghm_key_t key, float *value)
{
    ghm_value_t union_value;

    bool retval = ghm_get(map, key, &union_value);

    *value = union_value.flt;
    return retval;
}

bool ghm_getdouble(const ghm_hashmap_t *map, ghm_key_t key, double *value)
{
    ghm_value_t union_value;

    bool retval = ghm_get(map, key, &union_value);

    *value = union_value.dbl;
    return retval;
}

bool ghm_getptr(const ghm_hashmap_t *map, ghm_key_t key, ghm_generic_t *value)
{
    ghm_value_t union_value;

    bool retval = ghm_get(map, key, &union_value);

    *value = union_value.ptr;
    return retval;
}

bool ghm_remove(ghm_hashmap_t *map, ghm_key_t key)
{
    if (map == NULL) return false;


    ghm_node_t **probe = &map->lists[ghm_hash(map, key)];

    while ((*probe) != NULL)
    {
        bool keys_equal;

        switch (map->keytype)
        {
        case GHM_KEY_INTEGRAL:
            keys_equal = (*probe)->kv_pair.key == key;
            break;
        case GHM_KEY_STRING:
            keys_equal = strcmp((const char *)(*probe)->kv_pair.key, (const char *)key) == 0;
            break;
        }

        if (keys_equal) break;

        probe = &(*probe)->next;
    }

    if ((*probe) == NULL) return false;

    ghm_node_t *tmp = *probe;

    *probe = (*probe)->next;
    free(tmp);

    return true;
}

size_t ghm_hash(const ghm_hashmap_t *map, ghm_key_t key)
{
    size_t hash = 0;

    switch (map->keytype)
    {
    case GHM_KEY_INTEGRAL:
        hash = ghm_hashint(key);
        break;
    case GHM_KEY_STRING:
        hash = ghm_hashstring(key);
        break;
    }

    return hash % map->buckets;
}

size_t ghm_hashint(ghm_key_t key)
{
    return key * 2305843009213693951UL;
}

size_t ghm_hashstring(ghm_key_t key)
{
    const char *strkey = (const char *)key;

    size_t keylen = strlen(strkey), result = 0;

    for (size_t i = 0; i < keylen; ++i)
    {
        result = result * 37 + (size_t)strkey[i];
    }
    return result;
}

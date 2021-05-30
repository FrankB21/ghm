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

#include "ghm_test_utils.h"

#include "ghm.h"

#define NUM_INTS 20

int main()
{
    ghm_hashmap_t *map;
    int v;

    map = ghm_create(10, GHM_KEY_INTEGRAL);


    for (int i = 0; i < NUM_INTS; ++i)
    {
        GHM_ASSERT_MSG(ghm_setint32(map, (ghm_key_t)i, i * 2), "Failed to add new key");
    }

    GHM_ASSERT_MSG(ghm_setint32(map, 0, 1), "Failed to set exisiting key");

    for (int i = 1; i < NUM_INTS; ++i)
    {
        GHM_ASSERT_MSG(ghm_getint32(map, (ghm_key_t)i, &v), "Failed to retrieve existing key");
        GHM_ASSERT_MSG(v == i * 2, "Retrieved incorrect key");
    }

    GHM_ASSERT_MSG(ghm_getint32(map, NUM_INTS, &v) == false, "Retrieved nonexistent key");

    GHM_ASSERT_MSG(ghm_remove(map, 0), "Failed to remove existing key");
    GHM_ASSERT_MSG(ghm_getint32(map, 0, &v) == false, "Retrieved deleted key");

    for (int i = 1; i < NUM_INTS; ++i)
    {
        GHM_ASSERT_MSG(ghm_getint32(map, (ghm_key_t)i, &v), "Failed to find non-removed key");
        GHM_ASSERT_MSG(v == i * 2, "Retrieved incorrect key");
    }
    
    GHM_ASSERT_MSG(ghm_remove(map, NUM_INTS) == false, "Succeeded to remove nonexistent key");

    ghm_destroy(map);

    GHM_TESTS_PASSED();
}
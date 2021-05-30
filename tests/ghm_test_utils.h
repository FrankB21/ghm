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

#ifndef GHM_TEST_UTILS_H
#define GHM_TEST_UTILS_H 1

#include "ghm.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define GHM_ASSERT_MSG(expr, message) { if(!(expr)) { fprintf(stderr, "TEST FAILED: " __FILE__ ":%u\t " #expr "\t%s\n", __LINE__, message); exit(EXIT_FAILURE);}}
#define GHM_ASSERT(expr) GHM_ASSERT_MSG(expr, "");

#define GHM_TESTS_PASSED() fprintf(stderr, "TESTS PASSED: " __FILE__ "\n")

#endif// HM_TEST_UTILS_H

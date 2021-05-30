# MIT License
# 
# Copyright (c) 2021 FrankB21
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


CC=gcc
CWARNS=-Wall -Wextra -Wshadow -Wcast-align \
-Wpedantic -Wunused -Wconversion -Wsign-conversion \
-Wmisleading-indentation -Wnull-dereference \
-Wdouble-promotion -Wformat=2

INCDIR=include

CFLAGS=$(CWARNS) -std=gnu17 -I$(INCDIR)

SRCDIR=src
OBJDIR=obj

SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

TESTDIR=tests
TESTSRCS=$(wildcard $(TESTDIR)/*.c)
TESTBINS=$(patsubst $(TESTDIR)/%.c, $(TESTDIR)/bin/%, $(TESTSRCS))

LIBDIR=lib
LIB=$(LIBDIR)/libghm.a

all: CFLAGS+=-g
all: $(LIB)

release: CFLAGS+=-O3 -DNDEBUG
release: clean
release: $(LIB)

test: CFLAGS+=-g
test: $(LIB) $(TESTDIR)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

$(LIB): $(LIBDIR) $(OBJDIR) $(OBJS)
	$(RM) $(LIB)
	ar -cvrs $(LIB) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTDIR)/bin/%: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $< $(OBJS) -o $@

$(TESTDIR)/bin:
	mkdir $@

$(OBJDIR):
	mkdir $@

$(LIBDIR):
	mkdir $@

.PHONY: clean
clean:
	$(RM) -r $(LIBDIR) $(OBJDIR) $(TESTDIR)/bin

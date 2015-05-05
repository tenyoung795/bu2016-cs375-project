# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
GTEST_DIR := gtest-1.7.0

# Where to find user code.
USER_DIR := .

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS := -isystem $(GTEST_DIR)/include -I$(GTEST_DIR)

# Flags passed to the C++ compiler.
CXXFLAGS ?= -std=c++11 -Wall -Wextra -Wmissing-field-initializers -O3 -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS ?= $(shell xargs echo < unittests)

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS := $(GTEST_DIR)/include/gtest/*.h \
                 $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.
all : LDLIBS = -lpthread
all : $(TESTS)

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o

# Builds gtest.a and gtest_main.a.

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

gtest_main.o : $(GTEST_DIR)/src/gtest_main.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $^

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.
sparse-array_unittest : sparse-array_unittest.cc sparse-array.h gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ sparse-array_unittest.cc gtest_main.a
resize_unittest : resize_unittest.cc resize.h gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ resize_unittest.cc gtest_main.a
linearProbeTest : linearProbeTest.cc linearProbe.h gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ linearProbeTest.cc gtest_main.a
robinHoodTest : robinHoodTest.cc robinHoodHash.h gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ robinHoodTest.cc gtest_main.a

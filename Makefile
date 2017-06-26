all: t-address
.PHONY: all

check: t-address; ./t-address
.PHONY: check

clean:; rm -f ./t-address
.PHONY: clean

ARFLAGS = rcs
CPPFLAGS += -I.
CXXFLAGS += -std=c++14 -Wall -Wextra -Weffc++ -fprofile-arcs -ftest-coverage
GOOGLETEST_ROOT ?= /usr/src/gtest

t-address: t-address.cpp address.o | libgtest.a libgtest_main.a
	$(CXX) $(CXXFLAGS) -L. $^ -lgtest_main -lgtest -lpthread -o $@

address.o: address.cpp address.hpp detail/address/alignment.hpp detail/address/basic_parser.hpp \
           detail/address/dispatcher.hpp detail/address/dumper.hpp detail/address/limits.hpp \
		   detail/address/parser.hpp

detail/address/basic_parser.hpp: detail/address/basic_parser.hpp.re2c

libgtest.a: gtest.o
gtest.o: $(GOOGLETEST_ROOT)/src/gtest-all.cc
	$(CXX) -I$(GOOGLETEST_ROOT) -c -o $@ $<

libgtest_main.a: gtest_main.o
gtest_main.o: $(GOOGLETEST_ROOT)/src/gtest_main.cc
	$(CXX) -c -o $@ $<

%.a:
	$(AR) $(ARFLAGS) $@ $^

%.hpp: %.hpp.re2c
	re2c -s -o $@ $<

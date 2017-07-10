all: t-address
.PHONY: all

check: t-address t-command
	./t-address
	./t-command
.PHONY: check

clean:; rm -f ./t-address
.PHONY: clean

ARFLAGS = rcs
CPPFLAGS += -I.
CXXFLAGS += -std=gnu++1z -Wall -Wextra -Weffc++ -fprofile-arcs -ftest-coverage
GOOGLETEST_ROOT ?= /usr/src/gtest

t-address: t-address.cpp address.o | libgtest.a libgtest_main.a
	$(CXX) $(CXXFLAGS) -L. $^ -lgtest_main -lgtest -lpthread -o $@

t-command: t-command.cpp command.o address.o | libgtest.a libgtest_main.a
	$(CXX) $(CXXFLAGS) -L. $^ -lgtest_main -lgtest -lpthread -o $@

address.o: address.cpp address.hpp detail/address/alignment.hpp detail/address/basic_parser.hpp \
           detail/address/dispatcher.hpp detail/address/dumper.hpp detail/address/limits.hpp \
		   detail/address/parser.hpp detail/address/lexer.inl

command.o: command.cpp command.hpp detail/command/dump.inl \
           detail/command/frame.hpp detail/command/checksum.hpp

detail/address/lexer.inl: detail/address/lexer.inl.re2c
	re2c -g -o $@ $<

libgtest.a: gtest.o
gtest.o: $(GOOGLETEST_ROOT)/src/gtest-all.cc
	$(CXX) -I$(GOOGLETEST_ROOT) -c -o $@ $<

libgtest_main.a: gtest_main.o
gtest_main.o: $(GOOGLETEST_ROOT)/src/gtest_main.cc
	$(CXX) -c -o $@ $<

%.a:
	$(AR) $(ARFLAGS) $@ $^

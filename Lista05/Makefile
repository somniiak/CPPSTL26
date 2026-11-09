CXX = clang++
CXXFLAGS = -std=c++23 -stdlib=libc++ -Wall -Wextra -pedantic -O2

TARGETS = zadanie1 zadanie2

all: $(TARGETS)

%: %.cpp lexer.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean

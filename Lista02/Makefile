CXX      = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -O2

TARGETS = zadanie1 zadanie2 zadanie3

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean

CXX = clang++
CXXFLAGS = -std=c++23 -stdlib=libc++ -Wall -Wextra -pedantic -O2

TARGETS = zadanie1 zadanie2 zadanie3 zadanie4 zadanie5 zadanie6

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean

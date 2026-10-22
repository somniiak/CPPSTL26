CXX      = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -O2

TARGETS = zadanie1 zadanie2 zadanie3 zadanie4 \
          zadanie5 zadanie6 zadanie7 zadanie8

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
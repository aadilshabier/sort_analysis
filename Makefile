CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -O2 -ggdb

all: /tmp/sort_analysis

utils.o: utils.hpp utils.cpp

sorters.o: sorters.hpp sorters.cpp

datagenerators.o: datagenerators.hpp datagenerators.cpp

benchmarker.o: benchmarker.hpp sorters.hpp datagenerators.hpp utils.hpp benchmarker.cpp

main.o: benchmarker.hpp sorters.hpp datagenerators.hpp utils.hpp main.cpp

/tmp/sort_analysis: utils.o sorters.o main.o benchmarker.o datagenerators.o
	$(CXX) $(CXXFLAGS) -o /tmp/sort_analysis utils.o sorters.o main.o benchmarker.o datagenerators.o

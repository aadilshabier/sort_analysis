#include <iostream>
#include <random>
#include <vector>

#include "sorters.hpp"
#include "datagenerators.hpp"
#include "benchmarker.hpp"

constexpr int RANDOM_SEED = 420;

int main() {
	std::mt19937 gen(RANDOM_SEED); // used as RNG for the random number engine

    SorterList sorters = {
		{"quicksort1", new QuickSorter1()},
		{"quicksort2", new QuickSorter2(gen)},
		{"quicksort3", new QuickSorter3()},
		{"radixsort", new RadixSorter()},
		{"insertionsort", new InsertionSorter()},
		{"mergesort", new MergeSorter()},
		{"heapsort", new HeapSorter()},
	};

	DataGenerators datagens = {
		{"rand", new RandomGen(gen)},
		{"inc", new IncGen(gen)},
		{"dec", new DecGen(gen)},
	};

	std::vector<size_t> sizes = {1000, 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
	size_t n = 10; // number of runs for a particular size, average is taken

	Benchmarker b;
	b.run(sorters, datagens, sizes, n);
	b.save();
}

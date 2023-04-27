#pragma once

#include <utility>
#include <random>
#include <string>
#include <vector>

class Sorter {
public:
	virtual void sort(std::vector<int>& a) = 0;
};

using SorterList = std::vector<std::pair<std::string, Sorter*>>;

// last element is pivot
class QuickSorter1 : public Sorter {
	void sort_rec(std::vector<int>& a, int l, int h);
public:
	void sort(std::vector<int>& a) override;
};

// random element is pivot
class QuickSorter2 : public Sorter {
	std::mt19937& gen;

	void sort_rec(std::vector<int>& a, int l, int h);
public:
	QuickSorter2(std::mt19937& gen)
		: gen(gen)
	{}
	void sort(std::vector<int>& a) override;
};

// pivot is median of first, middle, last elements
class QuickSorter3 : public Sorter {
	void sort_rec(std::vector<int>& a, int l, int h);
public:
	void sort(std::vector<int>& a) override;
};

class RadixSorter : public Sorter {
	void countingsort(std::vector<int>& a, int exp, std::vector<int>& output);
public:
	void sort(std::vector<int>& a) override;
};

class InsertionSorter : public Sorter {
	size_t bsearch(const std::vector<int>&a, int elem, size_t l, size_t h);
public:
	void sort(std::vector<int>& a) override;
};

class MergeSorter : public Sorter {
	void merge(std::vector<int>& a, size_t l, size_t mid, size_t h, std::vector<int>& buf);
	void sort_rec(std::vector<int>& a, size_t l, size_t h, std::vector<int>& buf);
public:
	void sort(std::vector<int>& a) override;
};

class HeapSorter : public Sorter {
	void heapify(std::vector<int>& a, size_t n, size_t i);
public:
	void sort(std::vector<int>& a) override;
};

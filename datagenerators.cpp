#include "datagenerators.hpp"

#include <algorithm>
#include <random>

void RandomGen::generate(std::vector<int>& a, size_t n)
{
	a.resize(n);
	std::uniform_int_distribution<> distrib(0, 100000000);
	for (size_t i=0; i<n; i++)
		a[i] = distrib(gen);
}

void IncGen::generate(std::vector<int>& a, size_t n)
{
	RandomGen rgen(gen);
	rgen.generate(a, n);
	std::sort(a.begin(), a.end());
}

void DecGen::generate(std::vector<int>& a, size_t n)
{
	RandomGen rgen(gen);
	rgen.generate(a, n);
	std::sort(a.rbegin(), a.rend());
}

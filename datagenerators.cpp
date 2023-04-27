#include "datagenerators.hpp"

#include <random>

void RandomGen::generate(std::vector<int>& a, size_t n)
{
	a.resize(n);
	std::uniform_int_distribution<> distrib(0, 100);
	for (size_t i=0; i<n; i++)
		a[i] = distrib(gen);
}

void IncGen::generate(std::vector<int>& a, size_t n)
{
	a.resize(n);
	for (size_t i=0; i<n; i++) {
		a[i] = i;
	}
}

void DecGen::generate(std::vector<int>& a, size_t n)
{
	a.resize(n);
	for (size_t i=0; i<n; i++) {
		a[i] = n-i;
	}
}

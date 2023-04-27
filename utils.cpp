#include "utils.hpp"

#include <iostream>

using std::cout;
using std::vector;

void print_vector(const vector<int>& a)
{
	for (const auto& x : a)
		cout << x << ' ';
	cout << '\n';
}

bool is_sorted(const vector<int>& a)
{
	for (size_t i=0; i<a.size()-1; i++) {
		if (a[i] > a[i+1])
			return false;
	}
	return true;
}

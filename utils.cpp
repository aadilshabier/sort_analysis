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

static double sum_rec(const vector<double>& a, size_t l, size_t h)
{
	auto m = (l + h) / 2;
	double sum = 0.0;
	if (m - l > 1)
		sum += sum_rec(a, l, m);
	else
		sum += a[l];
	if (h - m > 1)
		sum += sum_rec(a, m, h);
	else
		sum += a[m];
	return sum;
}

double average(const vector<double>& a)
{
	return sum_rec(a, 0, a.size()) / double{a.size()};
}

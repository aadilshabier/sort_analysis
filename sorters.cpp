#include "sorters.hpp"

#include <algorithm>

// Take a[h] as pivot and return its final position
static size_t partition(std::vector<int>& a, size_t l, size_t h)
{
	auto p = h; 	// select last element as pivot
	auto firsthigh = l; // index of first element higher than pivot
	for (size_t i=l; i<h; i++) {
		if (a[i] < a[p]) {
			std::swap(a[firsthigh], a[i]);
			firsthigh++;
		}
	}
	std::swap(a[firsthigh], a[p]);
	return firsthigh;
}

void QuickSorter1::sort_rec(std::vector<int>& a, int l, int h)
{
	if (l < h) {
		auto p = partition(a, l, h);
		sort_rec(a, l, p-1);
		sort_rec(a, p+1, h);
	}
}

void QuickSorter1::sort(std::vector<int>& a)
{
	sort_rec(a, 0, a.size()-1);
}

void QuickSorter2::sort_rec(std::vector<int>& a, int l, int h)
{
	if (l < h) {
		std::uniform_int_distribution<> distrib(l, h);
		auto i = distrib(gen);
		std::swap(a[i], a[h]);
		size_t p = partition(a, l, h);
		sort_rec(a, l, p-1);
		sort_rec(a, p+1, h);
	}
}

void QuickSorter2::sort(std::vector<int>& a)
{
	sort_rec(a, 0, a.size()-1);
}

static int median_index(std::vector<int>& a, int i, int j, int k)
{
	int r;
	int s[] = {a[i], a[j], a[k]};
	std::sort(s, s+3);
	int m = s[1];
	if (m == a[i])
		r = i;
	else if (m == a[j])
		r = j;
	else
		r = k;
	return r;
}

void QuickSorter3::sort_rec(std::vector<int>& a, int l, int h)
{
	if (l < h) {
		auto m = (l+h)/2;
		auto i = median_index(a, l, m, h);
		std::swap(a[i], a[h]);
		size_t p = partition(a, l, h);
		sort_rec(a, l, p-1);
		sort_rec(a, p+1, h);
	}
}

void QuickSorter3::sort(std::vector<int>& a)
{
	sort_rec(a, 0, a.size()-1);
}

void RadixSorter::countingsort(std::vector<int>& a, int exp, std::vector<int>& output)
{
	auto n = a.size();
    size_t count[10] = {0};
 
    // Store count of occurrences in count[]
    for (size_t i = 0; i < n; i++)
        count[(a[i] / exp) % 10]++;
 
    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (size_t i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
 
    // Swap the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
	a.swap(output);
}

void RadixSorter::sort(std::vector<int>& a)
{
	const auto m = *std::max_element<>(a.begin(), a.end());

	std::vector<int> output(a.size());
	for (int exp = 1; m / exp > 0; exp *= 10)
		countingsort(a, exp, output);
}

void InsertionSorter::sort(std::vector<int>& a)
{
	for (size_t i=1; i<a.size(); i++) {
		auto j = i;
		while (j > 0 && a[j] < a[j-1]) {
			std::swap(a[j], a[j-1]);
			j--;
		}
	}
}

void MergeSorter::sort(std::vector<int>& a)
{
	std::vector<int> buf(a.size());
	sort_rec(a, 0, a.size()-1, buf);
}

void MergeSorter::sort_rec(std::vector<int>& a, size_t l, size_t h, std::vector<int>& buf)
{
	size_t m = (l + h)/2;

	if (m - l > 0)
		sort_rec(a, l, m, buf);
	if (h - m > 0)
		sort_rec(a, m+1, h, buf);

	merge(a, l, m, h, buf);
}

void MergeSorter::merge(std::vector<int>& a, size_t l, size_t mid, size_t h, std::vector<int>& buf)
{
    size_t i = l, j= mid+1, k = l;
    while(i <= mid && j <= h) {
        if(a[i] < a[j])
			buf[k++]=a[i++];
        else
			buf[k++]=a[j++];
    }

    for(; i<=mid; i++)
		buf[k++]=a[i];

    for(; j<=h; j++)
		buf[k++]=a[j];

    for(i=l; i<=h; i++)
		a[i]=buf[i];
}

// void mergesort(int *a,int n)
// {
//     int i,p,l,h,mid;
//     for(p=2;p<=n;p=p*2)
//     {
//         for(i=0;i+p-1<n;i=i+p)
//         {
//             l=i;
//             h=i+p-1;
//             mid=(h+l)/2;
//             merge(a,l,mid,h);
//         }
//     }
//     if(p/2<n)
//     {
//         merge(a,0,p/2-1,n-1);
// 	}
// }

void HeapSorter::heapify(std::vector<int>& a, size_t n, size_t i) {
    auto largest = i;
    auto left = 2 * i + 1;
    auto right = 2 * i + 2;

    if (left < n && a[left] > a[largest])
		largest = left;

    if (right < n && a[right] > a[largest])
		largest = right;


    if (largest != i) {
		std::swap(a[i], a[largest]);
		heapify(a, n, largest);
    }
}

void HeapSorter::sort(std::vector<int>& a)
{
	auto n = a.size();
    for (long long int i = n/2-1; i >= 0; i--)
		heapify(a, n, i);

    for (long long int i=n-1; i >= 0; i--) {
		std::swap(a[0], a[i]);
		heapify(a, i, 0);
    }
}

#pragma once

#include <map>

#include "sorters.hpp"
#include "datagenerators.hpp"

/* {
   'random': {'quicksort': [..vals..], 'mergesort': [..vals..], ..},
   'inc': {'quicksort': [..vals..], 'mergesort': [..vals..], ..},
   'dec': {'quicksort': [..vals..], 'mergesort': [..vals..], ..},
   }
*/

const std::string DATA_DIR {"data/"};

using ResultsMap = std::map<std::string, std::map<std::string, std::vector<double>>>;

class Benchmarker
{
	ResultsMap results;
    std::vector<size_t> array_sizes;
	void setup(const SorterList& sorters, const DataGenerators& datagens, const std::vector<size_t>& sizes);
public:
	void run(const SorterList& sorters, const DataGenerators& datagens, const std::vector<size_t>& sizes, size_t n);
	void save();
};

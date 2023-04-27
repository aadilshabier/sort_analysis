#include "benchmarker.hpp"

#include <iostream>
#include <fstream>

#include "utils.hpp"

void Benchmarker::setup(const SorterList& sorters, const DataGenerators& datagens, const std::vector<size_t>& sizes)
{
	auto n_vals = sizes.size();
	array_sizes = sizes;
	results.clear();
	for (const auto& [datagen_name, _] : datagens) {
		for (const auto& [sorter_name, _] : sorters) {
			results[datagen_name][sorter_name].reserve(n_vals);; // initialize empty vectors
		}
	}
}


void Benchmarker::run(const SorterList& sorters, const DataGenerators& datagens, const std::vector<size_t>& sizes, size_t n)
{
	setup(sorters, datagens, sizes);
	StopWatch sw;
	std::vector<int> data;
	for (const auto& [datagen_name, datagen] : datagens) {
		for (const auto& size : sizes) {
			datagen->generate(data, size);
			for (const auto& [sorter_name, sorter] : sorters) {
				// sort n times and take average to get better results
				double t_total = 0.0;
				for (size_t i=0; i<n; i++) {
					// std::cout << "Starting " << sorter_name << ", " << datagen_name << " with size: " << size << ", iteration: " << i <<  '\n';
					auto data_copy{data}; // create a copy of the data and sort it
					sw.reset();
					sorter->sort(data_copy);
					t_total += sw.elapsed_ms();
					if (!is_sorted(data_copy)) {
						print_vector(data_copy);
						std::cerr << "ERROR: " << sorter_name << " could not sort " << datagen_name << " data!" << std::endl;
						return;
					}
				}
				auto t = t_total / double{n};
				std::cout << sorter_name << " sorted " << datagen_name << '(' << size << ") in " << t << "ms." << std::endl;
				results[datagen_name][sorter_name].push_back(t);
			}
		}
	}
}

// save into DATA_DIR
void Benchmarker::save()
{
	// save array sizes used
	auto array_sizes_filename{ DATA_DIR + "array_sizes.txt" };
	std::ofstream array_sizes_file(array_sizes_filename);
	array_sizes_file << array_sizes.size() << '\n';
	for (const auto& x : array_sizes)
		array_sizes_file << x << '\n';
	array_sizes_file.close();
	// std::cout << "Array sizes list written to " << array_sizes_filename << '\n';

	for (const auto& [datagen_name, datagen_data] : results) {
		for (const auto& [sorter_name, data] : datagen_data) {
			auto filename{ DATA_DIR + datagen_name + '_' + sorter_name + ".txt" };
			std::ofstream file(filename);
		    file << data.size() << '\n';
			for (const auto& x : data)
				file << x << '\n';
		}
	}

}

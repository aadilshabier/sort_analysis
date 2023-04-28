#pragma once

#include <chrono>
#include <random>

using std::vector;

class StopWatch {
	std::chrono::time_point<std::chrono::system_clock> t1;
public:
	void reset() {
		t1 = std::chrono::high_resolution_clock::now();
	}

	double elapsed_ms() {
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> ms_double = t2 - t1;
		return ms_double.count();
	}

	double elapsed_s() {
		return elapsed_ms() / 1000.f;
	}
};

void print_vector(const vector<int>& a);

double average(const vector<double>& a);

#pragma once

#include <random>
#include <string>
#include <utility>
#include <vector>

class DataGen {
public:
	virtual void generate(std::vector<int>& a, size_t n) = 0;
};

using DataGenerators = std::vector<std::pair<std::string, DataGen*>>;

class RandomGen : public DataGen {
	std::mt19937& gen;
public:
	RandomGen(std::mt19937& gen)
		: gen(gen)
	{}
	void generate(std::vector<int>& a, size_t n) override;
};

class IncGen : public DataGen {
	std::mt19937& gen;
public:
	IncGen(std::mt19937& gen)
		: gen(gen)
	{}
	void generate(std::vector<int>& a, size_t n) override;
};

class DecGen : public DataGen {
	std::mt19937& gen;
public:
	DecGen(std::mt19937& gen)
		: gen(gen)
	{}
	void generate(std::vector<int>& a, size_t n) override;
};

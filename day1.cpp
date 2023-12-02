#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <format>
#include <numeric>

TEST(Day1, Part1) {
	std::ifstream inputFile("../../inputs/day1.txt");

	ASSERT_TRUE(inputFile.is_open());

	std::vector<int> results;
	std::string line;
	while(std::getline(inputFile, line)) {
		char first = 0;
		char last = 0;
		for (const auto& letter : line) {
			if (std::isdigit(letter)) {
				if (first == 0) {
					first = letter;
				}
				last = letter;
			}
		}
		std::stringstream resStream;
		resStream << first << last;
		auto resS = resStream.str();
		int resNum = std::stoi(resStream.str());

		results.push_back(resNum);
	}

	auto result = std::accumulate(results.begin(), results.end(), 0);
	std::cout << result << std::endl;
}

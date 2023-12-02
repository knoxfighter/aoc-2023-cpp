#include <format>
#include <fstream>
#include <gtest/gtest.h>
#include <numeric>
#include <string>
#include <ranges>

TEST(Day1, Part1) {
	std::ifstream inputFile("../../inputs/day1.txt");

	ASSERT_TRUE(inputFile.is_open());

	std::vector<int> results;
	std::vector<uint64_t> times;
	std::string line;
	while (std::getline(inputFile, line)) {
		const auto& start = std::chrono::steady_clock::now();

		// second variant, seems to be slightly faster
		auto first = *std::ranges::find_if(line, [](const char val) {
			return val >= '0' && val <= '9';
		});
		auto last = *std::ranges::find_if(line | std::views::reverse, [](const char val) {
			return val >= '0' && val <= '9';
		});

//		char first = 0;
//		char last = 0;
//		for (const auto& letter : line) {
//			if (std::isdigit(letter)) {
//				if (first == 0) {
//					first = letter;
//				}
//				last = letter;
//			}
//		}
		std::stringstream resStream;
		resStream << first << last;
		auto resS = resStream.str();
		int resNum = std::stoi(resStream.str());

		const auto& end = std::chrono::steady_clock::now();
		times.push_back((end - start).count());

		results.push_back(resNum);
	}

	auto result = std::accumulate(results.begin(), results.end(), 0);
	std::cout << result << std::endl;

	std::cout << std::format("Took {}ns", std::accumulate(times.begin(), times.end(), 0)) << std::endl;
}

TEST(Day1, Part2) {
	std::ifstream inputFile("../../inputs/day1.txt");

	ASSERT_TRUE(inputFile.is_open());

	std::vector<int> results;
	std::string line;
	while (std::getline(inputFile, line)) {
		char first = 0;
		char last = 0;

		auto setFirstLast = [&](char val) {
			if (first == 0) {
				first = val;
			}
			last = val;
		};

		for (int i = 0; i < line.size(); ++i) {
			auto val = line[i];

			// if current letter is a number
			if (val >= '0' && val <= '9') {
				setFirstLast(val);
			} else {
				const char* cur = line.data() + i;
				if (std::strncmp(cur, "one", 3) == 0) {
					setFirstLast('1');
				} else if (std::strncmp(cur, "two", 3) == 0) {
					setFirstLast('2');
				} else if (std::strncmp(cur, "three", 5) == 0) {
					setFirstLast('3');
				} else if (std::strncmp(cur, "four", 4) == 0) {
					setFirstLast('4');
				} else if (std::strncmp(cur, "five", 4) == 0) {
					setFirstLast('5');
				} else if (std::strncmp(cur, "six", 3) == 0) {
					setFirstLast('6');
				} else if (std::strncmp(cur, "seven", 5) == 0) {
					setFirstLast('7');
				} else if (std::strncmp(cur, "eight", 5) == 0) {
					setFirstLast('8');
				} else if (std::strncmp(cur, "nine", 4) == 0) {
					setFirstLast('9');
				}
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

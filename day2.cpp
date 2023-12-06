#include <fstream>
#include <gtest/gtest.h>
#include <numeric>
#include <ranges>
#include <Windows.h>

TEST(Day2, Part1Splits) {
	std::ifstream inputFile("../../inputs/day2.txt");

	ASSERT_TRUE(inputFile.is_open());

	std::unordered_map<std::string, int> maxCubes = {
			{"red", 12},
			{"green", 13},
			{"blue", 14},
	};

	int result = 0;
	std::vector<uint64_t> times;
	std::string line;
	while (std::getline(inputFile, line)) {
		const auto& start = std::chrono::steady_clock::now();
		bool failed = false;
		int i = 0;
		int lineNum = 0;
		for (const auto& lineSplit : std::views::split(line, ':')) {
			switch (i) {
				case 0: {
					// this is the first part of the input (Game X)
					int j = 0;
					for (const auto& gameSplit : std::views::split(lineSplit, ' ')) {
//						std::cout << std::string_view(gameSplit) << std::endl;
						switch (j) {
							case 1:
								std::from_chars(gameSplit.data(), gameSplit.data() + gameSplit.size(), lineNum);
								break;
						}
						++j;
					}
					break;
				}
				case 1:
					// the second part, where everything happens
					for (const auto& roundSplit : std::views::split(lineSplit, ';')) {
						for (const auto& cubeSplit : std::views::split(roundSplit, ',')) {
							int j = 0;
							std::string colour;
							int amount;
							for (const auto& dataSplit : std::views::split(cubeSplit, ' ') | std::views::drop(1)) {
//								std::cout << std::string_view(dataSplit) << std::endl;
								switch (j) {
									case 0:
										// this is the number of the input
										std::from_chars(dataSplit.data(), dataSplit.data() + dataSplit.size(), amount);
										// missing error handling
										break;
									case 1:
										// this is the colour of the input
										colour = std::string_view(dataSplit);
										break;
								}
								++j;
							}
							if (amount > maxCubes[colour]) {
//								std::cout << std::format("line {} failed with colour {}", lineNum, colour) << std::endl;
								failed = true;
								break;
							}
//							std::cout << colour << ' ' << amount << std::endl;
						}
						if (failed) break;
					}
					break;
			}
			++i;
		}
		if (!failed) {
//			std::cout << std::format("success of line {}", lineNum) << std::endl;
//			std::cout << "sucess: " << line << std::endl;
			result += lineNum;
		}

		const auto& end = std::chrono::steady_clock::now();
		times.push_back((end - start).count());
	}

	std::cout << result << std::endl;

	std::cout << std::format("Took {}ns", std::accumulate(times.begin(), times.end(), 0ull)) << std::endl;
}

TEST(Day2, Part1Manual) {
	std::ifstream inputFile("../../inputs/day2.txt");

	ASSERT_TRUE(inputFile.is_open());

	std::unordered_map<std::string, int> maxCubes = {
			{"red", 12},
			{"green", 13},
			{"blue", 14},
	};

	int result = 0;
	std::vector<uint64_t> times;
	std::string line;
	while (std::getline(inputFile, line)) {
		const auto& start = std::chrono::steady_clock::now();

		int lineNum = 0;
		int amount = 0;
		bool failed = false;

		std::string::iterator partStart = line.begin();
		int part = 0;
		for (auto it = line.begin(); it != line.end(); ++it) {
			switch (part) {
				case 0:
					// wait for first space
					if (*it == ' ') {
						++part;
						partStart = it+1;
					}
					break;
				case 1:
					// wait until `:` and parse int
					if (*it == ':') {
						std::string_view str(partStart, it);
						std::from_chars(str.data(), str.data() + str.size(), lineNum);
						++it;
						++part;
						partStart = it+1;
					}
					break;
				case 2:
					// get until next space
					if (*it == ' ') {
						std::string_view str(partStart, it);
						std::from_chars(str.data(), str.data()+str.size(), amount);
						++part;
						partStart = it + 1;
					}
					break;
				case 3:
					// get until ',' or ';' to find the colour
					if (*it == ',' || *it == ';') {
						// get colour
						std::string colour(partStart, it);
						if (amount > maxCubes[colour]) {
//							std::cout << std::format("failed colour {} - {}", colour, amount) << std::endl;
							failed = true;
						}
						++it;
						--part;
						partStart = it + 1;
					}
					break;
			}

			if (failed) {
				break;
			}
		}

		// get colour
		std::string colour(partStart, line.end());
		if (amount > maxCubes[colour]) {
			failed = true;
		}

		if (!failed) {
//			std::cout << "sucess: " << line << std::endl;
			result += lineNum;
		}

		const auto& end = std::chrono::steady_clock::now();
		times.push_back((end - start).count());
	}

	std::cout << result << std::endl;

	std::cout << std::format("Took {}ns", std::accumulate(times.begin(), times.end(), 0ull)) << std::endl;
}

TEST(Day2, Part2Splits) {
	std::ifstream inputFile("../../inputs/day2.txt");

	ASSERT_TRUE(inputFile.is_open());

	int result = 0;
	std::vector<uint64_t> times;
	std::string line;
	while (std::getline(inputFile, line)) {
		const auto& start = std::chrono::steady_clock::now();
		std::unordered_map<std::string, int> maxCubes;
		int i = 0;
		int lineNum = 0;
		for (const auto& lineSplit : std::views::split(line, ':')) {
			switch (i) {
				case 0: {
					// this is the first part of the input (Game X)
					int j = 0;
					for (const auto& gameSplit : std::views::split(lineSplit, ' ')) {
						//						std::cout << std::string_view(gameSplit) << std::endl;
						switch (j) {
							case 1:
								std::from_chars(gameSplit.data(), gameSplit.data() + gameSplit.size(), lineNum);
								break;
						}
						++j;
					}
					break;
				}
				case 1:
					// the second part, where everything happens
					for (const auto& roundSplit : std::views::split(lineSplit, ';')) {
						for (const auto& cubeSplit : std::views::split(roundSplit, ',')) {
							int j = 0;
							std::string colour;
							int amount;
							for (const auto& dataSplit : std::views::split(cubeSplit, ' ') | std::views::drop(1)) {
								switch (j) {
									case 0:
										// this is the number of the input
										std::from_chars(dataSplit.data(), dataSplit.data() + dataSplit.size(), amount);
										// missing error handling
										break;
									case 1:
										// this is the colour of the input
										colour = std::string_view(dataSplit);
										break;
								}
								++j;
							}
							if (amount > maxCubes[colour]) {
								maxCubes[colour] = amount;
							}
						}
					}
					break;
			}
			++i;
		}

		result += maxCubes["red"] * maxCubes["green"] * maxCubes["blue"];

		const auto& end = std::chrono::steady_clock::now();
		times.push_back((end - start).count());
	}

	std::cout << result << std::endl;

	std::cout << std::format("Took {}ns", std::accumulate(times.begin(), times.end(), 0ull)) << std::endl;
}

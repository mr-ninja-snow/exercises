#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

char charToDigit(char digitChar) { return digitChar - '0'; }

// this enum is used to indicate the number of neighbors (pairs) a pair has
enum neighborTypes
{
	NO_NEIGHBORS = 0,
	NEIGHBOR_TO_THE_RIGHT = 1,
	NEIGHBOR_TO_THE_LEFT = 2,
	TWO_NEIGHBORS = 3,
};

unsigned int factorial(unsigned int n)
{
	if (n == 0)
	{
		return 1;
	}
	return n * factorial(n - 1);
}

int goRight(std::vector<char>& pairs, int index)
{
	bool use = false;

	int count = 0;
	while(index < pairs.size()) {
		if(use) {
			count++;
		}
		use = !use;
		index++;
	}

	return count;
}

int goLeft(std::vector<char>& pairs, int index)
{
	bool use = false;

	int count = 0;
	while(index >= 0) {
		if(use) {
			count++;
		}
		use = !use;
		index--;
	}

	return count;
}

int getCombo(std::vector<char>& pairs, int index)
{
	int total = 0;
	total += goLeft(pairs, index - 1);
	total += goRight(pairs, index + 1);

	int nFac = factorial(total);
	int kFac = factorial(2);
	int nkFac = factorial(total - 2);

	int numberOfCombos = nFac/(kFac * nkFac);

	return numberOfCombos;
}

int main(int argc, char const *argv[]) {
	// std::fstream file_out( "out.txt" , std::fstream::out);
	// std::fstream file( "in.txt" , std::fstream::in);

	std::string inputStr("1111\n0");
	std::istringstream iss(inputStr);

	//std::istream& input = std::cin;
	std::istream& input = iss;
	// std::istream& input = file;

	std::ostream& output = std::cout;
	// std::ostream& output = file_out;

	std::string inputNumStr;
	while (input >> inputNumStr)
	{
		if (inputNumStr.size() == 1 || stoi(inputNumStr) == 0) {
			break;
		}

		char currentNum = charToDigit(inputNumStr[0]);
		char nextNum = 0;
		char currentPairNum = 0;

		bool neighboringPair = false;
		std::vector<char> pairs;

		for (unsigned i = 1; i < inputNumStr.size(); ++i) {
			nextNum = charToDigit(inputNumStr[i]);
			currentPairNum = currentNum * 10 + nextNum;
			if (currentPairNum <= 26) {
				if (neighboringPair) {
					pairs.back() |= NEIGHBOR_TO_THE_RIGHT;
					pairs.push_back(NEIGHBOR_TO_THE_LEFT);
				}
				else {
					pairs.push_back(NO_NEIGHBORS);
					neighboringPair = true;
				}
			}
			else {
				neighboringPair = false;
			}
		}

		int comboCount = 0;
		for (auto&& i : pairs) {
			std::cout << int(i) << ' ';
			int res = getCombo(pairs, i);
			std::cout << int(res) << '\n';
			comboCount += res;
		}


	}

	return 0;
}
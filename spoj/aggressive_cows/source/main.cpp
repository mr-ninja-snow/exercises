#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <functional>


template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> vec)
{
	for (auto&& i : vec) {
		out << i << " ";
	}
	out << "\n";

	return out;
}

int main(int argc, char const *argv[]) {

	// std::fstream file_out( "out.txt" , std::fstream::out);
	// std::fstream file( "in.txt" , std::fstream::in);

	//std::string inputStr( "1 5 3 1 2 8 4 9" );
	//std::string inputStr("1 5 5 1 2 8 4 9");
	//std::string inputStr("1 5 4 1 2 8 4 9");
	//std::string inputStr("1 5 2 1 2 8 4 9");
	//std::string inputStr("1 5 4 1 2 8 4 9");
	//std::string inputStr("1 2 2 1 3");
	//std::string inputStr("1 2 2 1 3");
	//std::string inputStr("1 7 4 2 13 15 16 55 66 99");
	//std::string inputStr("1 7 2 2 13 15 16 55 66 99");
	//std::string inputStr("1 7 2 2 13 15 16 55 66 99");
	std::string inputStr("1 7 3 2 13 15 16 27 75 99");
	std::istringstream iss(inputStr);

	//std::istream& input = std::cin;
	std::istream& input = iss;
	// std::istream& input = file;

	std::ostream& output = std::cout;
	// std::ostream& output = file_out;

	unsigned t;
	input >> t;

	for (unsigned i = 0; i < t; ++i) {
		unsigned numberOfStals;
		unsigned numberOfCows;

		input >> numberOfStals;
		input >> numberOfCows;

		std::vector<int> stalPos;
		stalPos.reserve(numberOfStals);

		for (unsigned j = 0; j < numberOfStals; ++j) {
			int posTmp;
			input >> posTmp;

			stalPos.push_back(posTmp);
		}

		/*if (numberOfCows == 2) {
			output << stalPos.back() - stalPos.front() << "\n";
			continue;
		}*/

		std::sort(stalPos.begin(), stalPos.end());

		int lo = 1;
		int hi = stalPos.back() - stalPos.front();

		output << stalPos << "\n\n";
		while (lo < hi) {
			int x = lo + (hi - lo) / 2;
			output << lo << " - " << x << " - " << hi << "\n\n";

			int currentCows = 1;
			int currentDistance = 0;
			int currentPos = stalPos.front();
			for (int i = 1; i < stalPos.size(); ++i)
			{
				int distance = stalPos[i] - currentPos;

				output << "currentDistance : " << currentDistance << "\ncurrentCows - " << currentCows << "\n";
				output << "stalPos[i] -  currentPos =  " << stalPos[i] << "-" << currentPos << " = " << distance << "\n";
				if (currentDistance + distance <= x)
				{
					currentDistance += distance;
				}
				else
				{
					currentCows++;
					currentDistance = distance;
				}
				currentPos = stalPos[i];

				output << "\n\n";
			}

			output << "currentCows - " << currentCows << "\n\n\n";
			//if (currentCows <= (numberOfCows - 1))
			if (currentCows <= numberOfCows)
			{
				hi = x;
			}
			else
			{
				lo = x + 1;
			}
		}
		output << lo << "\n";
	}

	// file.close();
	// file_out.close();

	return 0;
}
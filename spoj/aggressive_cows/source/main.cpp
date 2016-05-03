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

	//std::string inputStr( "1 5 3 1 2 8 4 9" );  // 3
	//std::string inputStr("1 5 5 1 2 8 4 9");  // 1
	//std::string inputStr("1 5 4 1 2 8 4 9");
	//std::string inputStr("1 5 2 1 2 8 4 9");
	//std::string inputStr("1 5 4 1 2 8 4 9");
	//std::string inputStr("1 2 2 1 3");
	//std::string inputStr("1 2 2 5 4");
	//std::string inputStr("1 2 2 1 3");
	//std::string inputStr("1 7 4 2 13 15 16 55 66 99");  // 14  (2 - 16)
	//std::string inputStr("1 7 2 2 13 15 16 55 66 99");
	//std::string inputStr("1 7 2 2 13 15 16 55 66 99");
	//std::string inputStr("1 7 3 2 13 15 16 27 75 99"); // 24
	std::string inputStr("1 3 3 0 1000000000 500000000");
	/*std::string inputStr("6 \
	10 3 \
	1 2 9 8 4 4 8 9 2 1 \
	5 3 \
	1 2 8 4 9 \
	20 3 \
	9 8 7 10 6 5 4 3 2 1 19 18 17 16 15 14 13 12 11 20 \
	3 3 \
	0 1000000000 500000000 \
	20 4 \
	9 8 7 10 6 5 4 3 2 1 19 18 17 16 15 14 13 12 11 20 \
	20 5 \
	9 8 7 10 6 5 4 3 2 1 19 18 17 16 15 14 13 12 11 20");*/
	std::istringstream iss(inputStr);

	//std::istream& input = std::cin;
	std::istream& input = iss;
	// std::istream& input = file;

	std::ostream& output = std::cout;
	// std::ostream& output = file_out;

	unsigned t;
	input >> t;

	bool moded = false;
	for (unsigned i = 0; i < t; ++i) {
		unsigned numberOfStals;
		unsigned numberOfCows;

		input >> numberOfStals;
		input >> numberOfCows;

		std::vector<long int> stalPos;
		stalPos.reserve(numberOfStals);

		for (unsigned j = 0; j < numberOfStals; ++j) {
			long int posTmp;
			input >> posTmp;

			stalPos.push_back(posTmp);
		}

		if (numberOfCows == 2) {
			output << std::abs(stalPos.back() - stalPos.front()) << "\n";
			continue;
		}

		std::sort(stalPos.begin(), stalPos.end());

		long int lo = 1;
		long int hi = stalPos.back() - stalPos.front();

		while (lo < hi) {
			moded = false;
			int x = lo + (hi - lo) / 2;
			output << lo << " - " << x << " - " << hi << "\n\n";

			long int currentCows = 1;
			long int currentDistance = 0;
			long int currentPos = stalPos.front();
			for (int i = 1; i < stalPos.size(); ++i)
			{
				long int distance = stalPos[i] - currentPos;

				output << stalPos << "\n";
				output << "currentDistance : " << currentDistance << "/" << x << "\ncurrentCows - " << currentCows << "\n";
				output << "prev stall : stalPos[" << i - 1 << "/" << stalPos.size() << "] = " << stalPos[i - 1] << "\n";
				output << "current stall : stalPos[" << i << "/" << stalPos.size() << "] = " << stalPos[i] << "\n";
				output << "current stall -  prev stall =  " << stalPos[i] << "-" << currentPos << " = " << distance << "\n";

				if (currentDistance + distance <= x)
				{
					currentDistance += distance;
					output << "continue sreaching...\n\n";
				}
				else
				{
					output << "putting a cow at stalPos[" << i << "/" << stalPos.size() << "] = " << stalPos[i] << "\n\n";
					currentCows++;
					currentDistance = 0;
				}
				currentPos = stalPos[i];

				output << "\n\n";
			}

			output << "currentCows - " << currentCows << "\n\n\n";
			//if (currentCows <= (numberOfCows - 1))
			//if (currentCows <= numberOfCows)
			if (currentCows < numberOfCows)
			{
				hi = x;
			}
			else
			{
				moded = true;
				lo = x + 1;
			}
		}

		if (moded)
			output << lo - 1 << "\n";
		else
			output << lo << "\n";
	}

	// file.close();
	// file_out.close();
	return 0;
}

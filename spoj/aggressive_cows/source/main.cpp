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
	std::istream& input = std::cin;

	std::ostream& output = std::cout;

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

		std::sort(stalPos.begin(), stalPos.end());

		if (numberOfCows == 2) {
			output << std::abs(stalPos.back() - stalPos.front()) << "\n";
			continue;
		}

		long int lo = 1;
		long int hi = stalPos.back() - stalPos.front();

		while (lo < hi) {
			moded = false;
			int x = lo + (hi - lo) / 2;

			long int currentCows = 1;
			long int currentDistance = 0;
			long int currentPos = stalPos.front();
			for (int i = 1; i < stalPos.size(); ++i)
			{
				long int distance = stalPos[i] - currentPos;

				if (currentDistance + distance <= x)
				{
					currentDistance += distance;
				}
				else
				{
					currentCows++;
					currentDistance = 0;
				}
				currentPos = stalPos[i];

			}

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

		output << lo << "\n";
	}

	return 0;
}
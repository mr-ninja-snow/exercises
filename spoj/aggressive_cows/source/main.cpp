#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> vec)
{
	for(auto&& i : vec) {
		out << i << " ";
	}
	out << "\n";

	return out;
}

int main(int argc, char const *argv[]) {

	// std::fstream file_out( "out.txt" , std::fstream::out);
	// std::fstream file( "in.txt" , std::fstream::in);

	// std::string inputStr( "1 5 4 1 2 8 4 9" );
	std::string inputStr( "1 7 4 2 13 15 16 55 66 99" );
	std::istringstream iss(inputStr);

	//std::istream& input = std::cin;
	std::istream& input = iss;
	// std::istream& input = file;

	std::ostream& output = std::cout;
	// std::ostream& output = file_out;

	unsigned t;
	input >> t;

	for ( unsigned i = 0; i < t; ++i ) {
		unsigned numberOfStals;
		unsigned numberOfCows;

		input >> numberOfStals;
		input >> numberOfCows;

		std::vector<int> stalPos;
		stalPos.reserve(numberOfStals);

		for(unsigned j = 0; j < numberOfStals; ++j) {
			int posTmp;
			input >> posTmp;

			stalPos.push_back(posTmp);
		}

		std::sort(stalPos.begin(), stalPos.end());

		std::priority_queue <int, std::vector<int >, std::greater< int>> stallPositionsDiffs;
		int currentStallPos = stalPos.front();
		for(unsigned i = 1; i < stalPos.size() - 1; ++i) {
			int ans = stalPos[i] - currentStallPos;

			stallPositionsDiffs.push(ans);

			currentStallPos = stalPos[i];
		}

		int lo = stallPositionsDiffs.top();
		int hi = stalPos.back() - stalPos.front();

		output << stalPos << "\n\n";
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			output << lo << " - " << mid << " - " << hi << "\n\n";

			int currentCows = 0;
			int currentDistance = 0;
			int currentPos = stalPos.front();
			for (int i = 1; i < stalPos.size(); ++i)
			{
				int distance = stalPos[i] - currentPos;

				output << "currentDistance : " << currentDistance << "\ncurrentCows - " << currentCows << "\n";
				output << "stalPos[i] -  currentPos =  " << stalPos[i] <<  "-" << currentPos << " = " << distance << "\n";
				if (currentDistance + distance >= mid)
				{
					//int numCows = distance / mid + 1;
					int numCows = distance / mid;
					output << "number of cows in dist - " << numCows << "\n";
					currentCows += numCows ? numCows : 1;
					
					// mns: check mod 
					//currentCows += numCows;

					//currentDistance = distance - numCows * mid;
					currentDistance = distance - numCows * mid - (mid - currentDistance);
				}
				else
				{
					currentDistance += distance;
				}
				currentPos = stalPos[i];

				output << "\n\n";
			}

			if (currentCows <= (numberOfCows - 1))
			{
				hi = mid;
			}
			else
			{
				lo = mid + 1;
			}
		}
		output << lo - 1 << "\n";
	}

	// file.close();
	// file_out.close();

	return 0;
}

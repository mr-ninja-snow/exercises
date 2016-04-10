#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <queue>
#include <functional>

int decisionHelper(int a, int b, int pointOfIntrest)
{
	int res1 = pointOfIntrest - a;
	int res2 = b - pointOfIntrest;
	if(res1 == res2) {
		return b; // vstepano: this is incorrect
	} else {
		if(res1 > res2) {
			return b;
		} else {
			return a;
		}
	}
}

int binarySerchForPointsOfInterst(std::vector<int>::iterator lo, std::vector<int>::iterator mid, std::vector<int>::iterator hi, int pointOfIntrest)
{
	if(*lo == pointOfIntrest || *mid == pointOfIntrest || *hi == pointOfIntrest) {
		return pointOfIntrest;
	}

	if(pointOfIntrest > *mid) {
		// vstepano check for bug
		if(std::distance(mid, hi) == 1) {
			return decisionHelper(*mid, *hi, pointOfIntrest);
		} else {
			std::vector<int>::iterator newMid = mid + std::distance(mid, hi) / 2;
			return binarySerchForPointsOfInterst(mid, newMid, hi, pointOfIntrest);
		}
	} else {
		if(std::distance(lo, mid) == 1) {
			return decisionHelper(*lo, *mid, pointOfIntrest);
		} else {
			std::vector<int>::iterator newMid = mid - std::distance(lo, mid) / 2;
			return binarySerchForPointsOfInterst(lo, newMid, mid, pointOfIntrest);
		}
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> vec)
{
	for(auto&& i : vec) {
		out << i << " ";
	}
	out << "\n";

	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, std::pair<T, T> p)
{
	out << p.first << " <-> " << p.second << " ";
	return out;
}

int main(int argc, char const *argv[]) {

	// std::fstream file_out( "out.txt" , std::fstream::out);
	// std::fstream file( "in.txt" , std::fstream::in);

	// std::string inputStr( "1 5 4 1 2 8 4 9" );
	std::string inputStr( "1 7 4 2	13	15	16	55	66	99" );
	//std::string inputStr( "1 2 2 1 2" );
	// std::string inputStr( "1 5 3 1 2 8 4 9" );
	//std::string inputStr("1 10 5 1 2 8 4 9 12 13 15 18 19");
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
					//currentCows += numCows;

					currentDistance = distance - numCows * mid;
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

		// int cowsToSort = numberOfCows - 2; // a cow in pos 1 and in last pos
		// int minDistance = stalPos.back() - stalPos.front();
		// int numberOfAreasOfIntrest = cowsToSort + 1;//int(minDistance / cowsToSort);
		// int spacingBetweenPointsOfIntrest = int(minDistance / numberOfAreasOfIntrest);

		// std::vector<int>::iterator lo = stalPos.begin();
		// std::vector<int>::iterator hi= stalPos.end() - 1;
		// std::vector<int>::iterator mid = stalPos.begin() + std::distance(lo, hi) / 2;

		// // output << *lo << "\n";
		// // output << *mid << "\n";
		// // output << *hi << "\n";

		// int currentPosCandidate = stalPos.front() + spacingBetweenPointsOfIntrest;



		// std::vector<int> stalCandidates;
		// stalCandidates.push_back(stalPos.front());

		// while(cowsToSort != 0) {
		// 	output << "currentPosCandidate - " << currentPosCandidate << "\n";
		// 	int stalCandidate = binarySerchForPointsOfInterst(lo, mid, hi, currentPosCandidate);
		// 	stalCandidates.push_back(stalCandidate);
		// 	cowsToSort--;
		// 	currentPosCandidate += spacingBetweenPointsOfIntrest;
		// }
		// stalCandidates.push_back(stalPos.back());

		// int currentStallPos = stalCandidates[0];
		// std::priority_queue <int, std::vector<int >, std::greater< int>> stallPositionsDiffs;

		// for(unsigned i = 1; i < stalCandidates.size() - 1; ++i) {
		// 	int ans = stalCandidates[i] - currentStallPos;

		// 	stallPositionsDiffs.push(ans);

		// 	currentStallPos = stalCandidates[i];
		// }

		// output << stalPos << "\n\n";
		// output << stalCandidates << "\n";
		//  output << stallPositionsDiffs.size() << "\n";

		// int a = stallPositionsDiffs.top();
		// output << a << "\n";
	}

	// file.close();
	// file_out.close();

	return 0;
}

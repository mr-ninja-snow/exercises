#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>

std::pair<int, int> binarySerchForPointsOfInterst(std::vector<int>::iterator lo, std::vector<int>::iterator mid, std::vector<int>::iterator hi, int pointOfIntrest)
{
	if(*lo == pointOfIntrest || *mid == pointOfIntrest || *hi == pointOfIntrest) {
		return std::pair<int, int>(pointOfIntrest, -1);
	}

	if(pointOfIntrest > *mid) {
		// vstepano check for bug
		if(std::distance(mid, hi) == 1) {
			return std::pair<int, int>(*mid, *hi);
		} else {
			std::vector<int>::iterator newMid = mid + std::distance(mid, hi) / 2;
			return binarySerchForPointsOfInterst(mid, newMid, hi, pointOfIntrest);
		}
	} else {
		if(std::distance(lo, mid) == 1) {
			return std::pair<int, int>(*lo, *mid);
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

	std::fstream file_out( "out.txt" , std::fstream::out);
	std::fstream file( "in.txt" , std::fstream::in);

	//std::string inputStr( "1 5 3 1 2 8 4 9" );
	std::string inputStr("1 10 5 1 2 8 4 9 12 13 15 18 19");
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

		int cowsToSort = numberOfCows - 2; // a cow in pos 1 and in last pos
		int minDistance = stalPos.back() - stalPos.front();
		int numberOfAreasOfIntrest = cowsToSort + 1;//int(minDistance / cowsToSort);
		int spacingBetweenPointsOfIntrest = int(minDistance / numberOfAreasOfIntrest);

		std::vector<int>::iterator lo = stalPos.begin();
		std::vector<int>::iterator hi= stalPos.end() - 1;
		std::vector<int>::iterator mid = stalPos.begin() + std::distance(lo, hi) / 2;

		output << *lo << "\n";
		output << *mid << "\n";
		output << *hi << "\n";

		int currentPosCandidate = stalPos.front() + spacingBetweenPointsOfIntrest;

		output << currentPosCandidate << "\n";

		std::vector<std::pair<int, int>> stalCandidates;
		while(cowsToSort != 0) {
			std::pair<int, int> stalCandidate = binarySerchForPointsOfInterst(lo, mid, hi, currentPosCandidate);
			stalCandidates.push_back(stalCandidate);
			cowsToSort--;
			currentPosCandidate += spacingBetweenPointsOfIntrest;
		}

		output << stalPos << "\n\n";
		output << stalCandidates << "\n";
	}

	file.close();
	file_out.close();

	return 0;
}

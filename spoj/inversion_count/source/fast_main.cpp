#include <algorithm>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>


void updateBIT(std::vector<unsigned long long int>& BIT, unsigned long long int index)
{
	// std::cout << "updateBIT begin\n";
	if( index != 0) {
		
		while(index <= BIT.size()) {
			// std::cout << "index: " << index << "\n";
			BIT[index] -= 1;
			index += index & (-index);
		}
	}
	// std::cout << "updateBIT end\n";

}

void initBIT(std::vector<unsigned long long int>& BIT)
{
	unsigned long long int currentNumber = 1;
	unsigned long long int currentNumberStep = 2;

	while(currentNumber < BIT.size()){ 
		for(unsigned i = currentNumber; i < BIT.size(); ) {
			BIT[i] = currentNumber;
			i += currentNumberStep;
		}
		currentNumber *= 2;
		currentNumberStep *= 2;
	}

	std::cout << "BIT content\n";
	for(auto& i : BIT) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

unsigned long long countNumberOfGreaterElements(std::vector<unsigned long long int>& BIT, unsigned long long int pos)
{
	// std::cout << "\n\n\ncountNumberOfGreaterElements begin\n";

	unsigned long long currentPos = pos;
	unsigned long long numberOfGreaterElements = 0;

	while(currentPos) {
		std::cout << "currentPos: " << currentPos << "\n";
		// std::cout << "new currentPos: " << currentPos << "\n\n";

		numberOfGreaterElements += BIT[currentPos];
		currentPos -= currentPos & (-currentPos);
		// currentPos = currentPos & (~(currentPos & (-currentPos)));
	}

	// std::cout << "countNumberOfGreaterElements end\n";


	return numberOfGreaterElements;
}

int main(int argc, char const *argv[]) {
	// std::fstream file_out( "out.txt" , std::fstream::out);
	std::fstream infile( "in.txt" , std::fstream::in);

	std::vector<unsigned long long int> v;
	std::vector<unsigned long long int> vSorted;
	int a;
	while (infile >> a)
	{
		v.push_back(a);
		vSorted.push_back(a);
	}

	std::sort(vSorted.begin(), vSorted.end(), std::greater<long long int>());

	std::vector<unsigned long long int> BIT(vSorted.size() + 1);
	initBIT(BIT);

	unsigned long long int numberOfInvertions = 0;
	for(auto rit = v.rbegin(); rit != v.rend(); rit++) {
		auto elIt = std::find(vSorted.begin(), vSorted.end(), *rit);

		std::cout << "*rit: " << *rit << "\n";

		unsigned long long int pos = std::distance(vSorted.begin(), elIt);
		std::cout << "pos: " << pos << "\n";
		unsigned long long int numberOfGreaterElements = countNumberOfGreaterElements(BIT, pos);
		numberOfInvertions += numberOfGreaterElements;
		std::cout << "numberOfGreaterElements: " << numberOfGreaterElements << "\n";

		updateBIT(BIT, pos + 1);
	}

	std::cout << "numberOfInvertions: " << numberOfInvertions << "\n";



	// for(auto&& i : BIT) {
	// 	std::cout << " " << (int)i;
	// }

	// std::cout << "\n";

	// unsigned long long numberOfInvertions = 0;
	// for(auto rit = v.rbegin(); rit != v.rend(); rit++) {
	// 	auto elIt = std::find(vSorted.begin(), vSorted.end(), *rit);
	// 	std::cout << "\n\n*rit: " << *rit << "\n";

	// 	unsigned long long pos = std::distance(vSorted.begin(), elIt);
	// 	unsigned long long countNumberOfGreaterElements = countNumberOfGreaterElements(BIT, pos);

	// 	std::cout << "numberOfGreaterElements: " << numberOfGreaterElements << "\n";
	// 	numberOfInvertions += numberOfGreaterElements;
	// }

	// std::cout << "numberOfInvertions: " << numberOfInvertions << "\n";
}
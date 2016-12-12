#include <algorithm>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>


void updateBIT(std::vector<unsigned long long int>& BIT)
{

}

void initBIT(std::vector<unsigned long long int>& BIT)
{
	unsigned long long int currentNumber = 1;
	unsigned long long int currentNumberStep = 2;

	while(currentNumber < BIT.size()){ 
		for(unsigned i = currentNumber - 1; i < BIT.size(); ) {
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
	std::cout << "\n\n\n";

	unsigned long long currentPos = pos;
	unsigned long long numberOfGreaterElements = 0;

	while(currentPos) {
		std::cout << "currentPos: " << currentPos << "\n";
		currentPos = currentPos & (~(currentPos & (-currentPos)));
		std::cout << "new currentPos: " << currentPos << "\n\n";

		numberOfGreaterElements += BIT[currentPos];
	}

	return 0;
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

	std::vector<unsigned long long int> BIT(vSorted.size());
	initBIT(BIT);


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
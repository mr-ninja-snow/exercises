#include <algorithm>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>


void updateBIT(std::vector<char>& BIT)
{

}

void initBIT(std::vector<char>& BIT)
{
	unsigned long long int currentNumber = 1;

	for(auto& i : BIT) {
		if(currentNumber & 1) {
			i = 1;
		} else {
			if(((currentNumber & (currentNumber-1)) == 0)) { // checking if number is a power of two
				/* code */
			}
		}

		currentNumber++;
	}
}

unsigned long long countNumberOfGreaterElements(std::vector<char>& BIT, unsigned long long int pos)
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
}

int main(int argc, char const *argv[]) {
	// std::fstream file_out( "out.txt" , std::fstream::out);
	std::fstream infile( "in.txt" , std::fstream::in);

	std::vector<long long int> v;
	std::vector<long long int> vSorted;
	int a;
	while (infile >> a)
	{
		v.push_back(a);
		vSorted.push_back(a);
	}

	std::sort(vSorted.begin(), vSorted.end(), std::greater<long long int>());


	std::vector<char> BIT(vSorted.size(), 1);

	for(auto&& i : BIT) {
		std::cout << " " << (int)i;
	}

	std::cout << "\n";

	unsigned long long numberOfInvertions = 0;
	for(auto rit = v.rbegin(); rit != v.rend(); rit++) {
		auto elIt = std::find(vSorted.begin(), vSorted.end(), *rit);
		std::cout << "\n\n*rit: " << *rit << "\n";

		unsigned long long pos = std::distance(vSorted.begin(), elIt);
		unsigned long long countNumberOfGreaterElements = countNumberOfGreaterElements(BIT, pos);

		std::cout << "numberOfGreaterElements: " << numberOfGreaterElements << "\n";
		numberOfInvertions += numberOfGreaterElements;
	}

	std::cout << "numberOfInvertions: " << numberOfInvertions << "\n";
}
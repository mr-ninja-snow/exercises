#include <algorithm>
#include <fstream>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


enum InputState
{
	GET_ARRAY_SIZE,
	GET_ARRAY_ELEMENT,
	FIND_ANS
};

void brute_force(std::vector<long long int>& v, long long int& curAns)
{
	int currentArrayIndex = 0;
	for(auto& el : v) {
		//std::cout << tc.first << " in pos " << tc.second << "\n";
		for(unsigned i = currentArrayIndex; i < v.size(); ++i) {
			if(el > v[i]) {
				curAns++;
			}
		}
		currentArrayIndex++;
	}
}

class MergeSort {
private:
	std::vector<long long int> v1;
	std::vector<long long int> v2;
	std::vector<long long int>& vRes;

	int m_debugMergeCount;

	long long int m_inversionCount;

	enum AuxArray
	{
		USE_V1_TO_MERGE,
		USE_V2_TO_MERGE
	};

	AuxArray m_currentAuxArray;
public:
	MergeSort(std::vector<long long int>&& v) : v1{v}, vRes{v1}, m_debugMergeCount{0}, m_inversionCount{0}, m_currentAuxArray{USE_V2_TO_MERGE} { v2.resize(v1.size()); }

	void debugVectorPrint(std::vector<long long int>& v, std::string msg) const 
	{
		std::cout << "debug:" << msg << "\nindex|";
		for(unsigned i = 0; i < v.size(); ++i) {
			std::cout << std::setw(2) << i << " ";
		}
		std::cout <<"\n     |";
		for(auto&& i : v) {
			std::cout << std::setw(2) << i << " ";
		}
		std::cout << "\n";

	}

	long long int getInversionCount() const { return m_inversionCount; }

	void sort()
	{
		// debugVectorPrint(v1, "before sort");
		AuxArray resltingArray = divide_and_conquer(0, v1.size() - 1, USE_V2_TO_MERGE);
		// divide_and_conquer(0, v1.size(),USE_V2_TO_MERGE );
		// debugVectorPrint(getMainArray(resltingArray), "after sort");
		vRes = getMainArray(resltingArray);
		// std::cout << "debug:" << "m_inversionCount: " << m_inversionCount << "\n\n";
	}



	const std::vector<long long int>& getSortedArray()
	{
		return vRes;
	}

private:
	AuxArray divide_and_conquer(int lo, int hi, AuxArray toUse)
	// void divide_and_conquer(int lo, int hi, AuxArray toUse)
	{
		int mid = lo + (hi - lo)/2;

		// std::cout << "debug:" << "divide_and_conquer\n";
		// std::cout << "debug:" << "\tlo: " << lo << "\n";
		// std::cout << "debug:" << "\tmid: " << mid << "\n";
		// std::cout << "debug:" << "\thi: " << hi << "\n";
		
		if(hi - lo < 1) {
			// m_currentAuxArray = toggelAuxArray(m_currentAuxArray);
			// std::cout << "debug:" << "return!\n";
			std::vector<long long int>& mainArray = getMainArray(toUse);
			std::vector<long long int>& auxArray = getAuxArray(toUse);
			auxArray[hi] = mainArray[hi];
			return toUse;
		}



		// std::cout << "debug:" << "leftHalf \n";
		auto resltingAuxLeft = divide_and_conquer(lo, mid, toUse);
		// divide_and_conquer(lo, mid, toggelAuxArray(toUse));
		
		// std::cout << "debug:" << "rightHalf \n";
		// divide_and_conquer(mid, hi, toggelAuxArray(toUse));
		auto resltingAuxRight = divide_and_conquer(mid + 1, hi, toUse);

		if(resltingAuxLeft != resltingAuxRight) {
			std::vector<long long int>& mainRArrayy = getMainArray(resltingAuxRight);
			std::vector<long long int>& mainLArrayy = getMainArray(resltingAuxLeft);
			for(unsigned i = mid + 1; i <= hi; ++i) {
				mainLArrayy[i] = mainRArrayy[i];
			}
		}

		merge(lo, mid + 1, hi, resltingAuxLeft);
		return toggelAuxArray(resltingAuxLeft);
		// m_currentAuxArray = toggelAuxArray(m_currentAuxArray);


	}

	AuxArray toggelAuxArray(AuxArray toUse)
	{
		if(toUse == USE_V2_TO_MERGE) {
			return USE_V1_TO_MERGE;
		} else {
			return USE_V2_TO_MERGE;
		}
	}

	// std::vector<long long int>& getAuxArray()
	std::vector<long long int>& getAuxArray(AuxArray toUse)
	{
		if(toUse == USE_V2_TO_MERGE) {
		// if(m_currentAuxArray == USE_V2_TO_MERGE) {
			return v2;
		} else {
			return v1;
		}
	}

	// std::vector<long long int>& getMainArray()
	std::vector<long long int>& getMainArray(AuxArray toUse)
	{
		if(toUse == USE_V2_TO_MERGE) {
		// if(m_currentAuxArray == USE_V2_TO_MERGE) {
			// std::cout << "debug:" << "main array is v1\n";
			return v1;
		} else {
			// std::cout << "debug:" << "main array is v2\n";

			return v2;
		}
	}

	// void merge(int lo, int mid, int hi)
	void merge(int lo, int mid, int hi, AuxArray toUse)
	{
		// std::cout << "debug:" << m_debugMergeCount++ << "# merging " << lo << ".."<< mid - 1 << " and " << mid << ".." << hi << "\n";
		std::vector<long long int>& mainArrayy = getMainArray(toUse);
		std::vector<long long int>& auxArray = getAuxArray(toUse);
		// debugVectorPrint(mainArrayy, "\n\nmain array before merge\n");

		unsigned int leftHalfIndex = lo;
		unsigned int rightHalfIndex = mid;
		unsigned int auxIndex = lo;
		for(; auxIndex <= hi; ++auxIndex) {

			if(leftHalfIndex >= mid) {
				// std::cout << "debug:" << "\t\tcpRight\n";
				while(rightHalfIndex <= hi) {
					// auxIndex++;
					auxArray[auxIndex] = mainArrayy[rightHalfIndex];
					// std::cout << "debug:" << "\t\tmainArrayy[rightHalfIndex:" << rightHalfIndex << "]: " << mainArrayy[rightHalfIndex] << "<= is used\n";
					rightHalfIndex++;
					auxIndex++;
				}
				break;
			}
			if(rightHalfIndex > hi) {
				// std::cout << "debug:" << "\t\tcp Left\n";

				while(leftHalfIndex < mid) {
					// auxIndex++;
					auxArray[auxIndex] = mainArrayy[leftHalfIndex];
					// std::cout << "debug:" << "\t\tmainArrayy[leftHalfIndex:" << leftHalfIndex << "]: " << mainArrayy[leftHalfIndex] << "<= is used\n";
					leftHalfIndex++;
					auxIndex++;
				}
				break;
			}

			// std::cout << "debug:" << "\t\tauxIndex: " << auxIndex << "\n";
			if(mainArrayy[leftHalfIndex] > mainArrayy[rightHalfIndex]) {
				// std::cout << "debug:" << "\t\trightHalf item smaller\n";
				// std::cout << "debug:" << "\t\tmainArrayy[rightHalfIndex:" << rightHalfIndex << "]: " << mainArrayy[rightHalfIndex] << "<= is used\n";
				// std::cout << "debug:" << "\t\tmainArrayy[leftHalfIndex:" << leftHalfIndex << "]: " << mainArrayy[leftHalfIndex] << "\n";
				auxArray[auxIndex] = mainArrayy[rightHalfIndex];
				rightHalfIndex++;
				
				int invertions = mid - leftHalfIndex;
				// std::cout << "debug:" << "invertions: " << invertions << "\n";
				m_inversionCount += invertions;
			} else{
				// std::cout << "debug:" << "\t\tleftHalf item smaller\n";
				// std::cout << "debug:" << "\t\tmainArrayy[rightHalfIndex:" << rightHalfIndex << "]: " << mainArrayy[rightHalfIndex] << "\n";
				// std::cout << "debug:" << "\t\tmainArrayy[leftHalfIndex:" << leftHalfIndex << "]: " << mainArrayy[leftHalfIndex] << "<= is used\n";

				auxArray[auxIndex] = mainArrayy[leftHalfIndex];
				leftHalfIndex++;
			}

		}

		// debugVectorPrint(auxArray, "auxArray after merge\n");

	}
};

/*int main(int argc, char const *argv[]) {
	// std::fstream file_out( "out.txt" , std::fstream::out);
	std::fstream infile( "in.txt" , std::fstream::in);

	std::vector<long long int> v;
	int a;
	while (infile >> a)
	{
		v.push_back(a);
	}

	std::vector<long long int> v2(v);
	std::vector<long long int> v3(v);

	MergeSort ms(std::move(v));
	{
		auto start = std::chrono::high_resolution_clock::now();
		ms.sort();
		auto finish = std::chrono::high_resolution_clock::now();
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(finish-start);
		// std::cout << "debug: using My Merge sort - the array was sorted in " << seconds.count() << "s\n";
	}

	const std::vector<long long int>& vMS = ms.getSortedArray();

	{
		auto start = std::chrono::high_resolution_clock::now();
		std::sort(v2.begin(), v2.end());
		auto finish = std::chrono::high_resolution_clock::now();
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(finish-start);
		// std::cout << "debug: using the std::sort - the array was sorted in " << seconds.count() << "s\n";
	}

	bool correctSort = true;
	for(unsigned i = 0; i < v2.size(); ++i) {
		if(v2[i] != vMS[i]) {
			correctSort = false;
			std::cout << "Failed on elem " << i <<"#\n";
			break;
		}
	}

	if(correctSort) {
		std::cout << "\n\nThe array was sorted correctly\n\n";
	} else {
		std::cout << "\n\nThe array wasn't sored correctly!\n\n";
	}


	long long int curAns = 0;

	auto start = std::chrono::high_resolution_clock::now();
	brute_force(v3, curAns);
	auto finish = std::chrono::high_resolution_clock::now();

	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(finish-start);
	std::cout << "It took the brute_force implementation " << seconds.count() << "s to find the number of invertions\n";

	std::cout << "number of invertions - " << curAns << "\n";

	if(ms.getInversionCount() == curAns) {
		std::cout << "\n\nThe number of invertions match!\n";
	} else {
		std::cout << "\n\nERROR!!!\n\nThe number of invertions DO NOT match!\n";
	}

	return 0;
}*/


int main(int argc, char const *argv[]) {
	// std::fstream file_out( "out.txt" , std::fstream::out);
	// std::fstream file( "in.txt" , std::fstream::in);

	// std::string inputStr("2\n\n3\n3\n1\n2\n\n5\n2\n3\n8\n6\n1\n");
	// std::string inputStr("2\n\n3\n3\n1\n2\n\n5\n2\n3\n8\n6\n1\n");
	// std::istringstream iss(inputStr);

	std::istream& input = std::cin;
	// std::istream& input = iss;
	// std::istream& input = file;

	std::ostream& output = std::cout;
	// std::ostream& output = file_out;

	int inputIndex = 0;
	std::string inputNumStr;

	// std::vector<int> ans;

	std::vector<long long int> TC;
	// std::map<int, int> arrayPosMap;
	// std::vector<std::vector<int>> testcases;
	// int testcasesIndex = 0;
	InputState is = GET_ARRAY_SIZE;
	int currentArraySize = 0;
	int currentArrayIndex = 0;

	int curNum = 0;
	// int curAns = 0;

	int numberOfTestCases = 0;
	while (input >> inputNumStr)
	{
		// std::cout << "input: '" << inputNumStr<< "'\n";
		if(inputIndex == 0) {
			numberOfTestCases = std::stoi(inputNumStr);
			inputIndex++;
			continue;
		}

		switch(is)
		{
		case GET_ARRAY_SIZE:
			currentArraySize = std::stoi(inputNumStr);
			//testcases.emplace_back(currentArraySize);
			TC.clear();
			currentArrayIndex = 0;
			is = GET_ARRAY_ELEMENT;
			// std::cout << "\nsize of tc array  " << testcases.size() << "\n";
			// arrayPosMap.clear();
			break;
		case GET_ARRAY_ELEMENT:
			// testcases[testcasesIndex][currentArrayIndex] = std::stoi(inputNumStr);
			curNum = std::stoi(inputNumStr);
			TC.push_back(curNum);
			// arrayPosMap.insert(std::pair<int, int>(curNum, currentArrayIndex));
			// std::cout << "\nsize of tc  " << testcases[testcasesIndex].size() << "\n";
			currentArrayIndex++;
			if(currentArrayIndex == currentArraySize) {
				// testcasesIndex++;
				is = FIND_ANS;
			}
			else
			{
			break;
			}
		case FIND_ANS:
		{
			// std::cout << "\n\nhere is the map::\n";
			// std::sort(TC.begin(), TC.end(), std::greater<int>());
			MergeSort ms(std::move(TC));
			auto start = std::chrono::high_resolution_clock::now();
			ms.sort();
			// currentArrayIndex = 0;
			// curAns = 0;
			// for(auto& el : TC) {
			// 	//std::cout << tc.first << " in pos " << tc.second << "\n";
			// 	for(unsigned i = currentArrayIndex; i < TC.size(); ++i) {
			// 		if(el > TC[i]) {
			// 			curAns++;
			// 		}
			// 	}

			// 	currentArrayIndex++;

			// }

			// std::cout << "current ans  " << curAns << "\n";
			is = GET_ARRAY_SIZE;
			std::cout << ms.getInversionCount() << "\n";

			numberOfTestCases--;
			if(numberOfTestCases == 0) {
				return 0;
			}

			break;
		}
		}
	}

	return 0;
}

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

void brute_force(std::vector<unsigned long long int>& v, unsigned long long int& curAns)
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
	std::vector<unsigned long long int> v1;
	std::vector<unsigned long long int> v2;
	std::vector<unsigned long long int>& vRes;

	int m_debugMergeCount;

	unsigned long long int m_inversionCount;

	enum AuxArray
	{
		USE_V1_TO_MERGE,
		USE_V2_TO_MERGE
	};

	AuxArray m_currentAuxArray;
public:
	MergeSort(std::vector<unsigned long long int>&& v) : v1{v}, vRes{v1}, m_debugMergeCount{0}, m_inversionCount{0}, m_currentAuxArray{USE_V2_TO_MERGE} { v2.resize(v1.size()); }

	void debugVectorPrint(std::vector<unsigned long long int>& v, std::string msg) const 
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

	unsigned long long int getInversionCount() const { return m_inversionCount; }

	void sort()
	{
		// debugVectorPrint(v1, "before sort");
		AuxArray resltingArray = divide_and_conquer(0, v1.size() - 1, USE_V2_TO_MERGE);
		// divide_and_conquer(0, v1.size(),USE_V2_TO_MERGE );
		// debugVectorPrint(getMainArray(resltingArray), "after sort");
		vRes = getMainArray(resltingArray);
		// std::cout << "debug:" << "m_inversionCount: " << m_inversionCount << "\n\n";
	}



	const std::vector<unsigned long long int>& getSortedArray()
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
			std::vector<unsigned long long int>& mainArray = getMainArray(toUse);
			std::vector<unsigned long long int>& auxArray = getAuxArray(toUse);
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
			std::vector<unsigned long long int>& mainRArrayy = getMainArray(resltingAuxRight);
			std::vector<unsigned long long int>& mainLArrayy = getMainArray(resltingAuxLeft);
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

	// std::vector<unsigned long long int>& getAuxArray()
	std::vector<unsigned long long int>& getAuxArray(AuxArray toUse)
	{
		if(toUse == USE_V2_TO_MERGE) {
		// if(m_currentAuxArray == USE_V2_TO_MERGE) {
			return v2;
		} else {
			return v1;
		}
	}

	// std::vector<unsigned long long int>& getMainArray()
	std::vector<unsigned long long int>& getMainArray(AuxArray toUse)
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
		std::vector<unsigned long long int>& mainArrayy = getMainArray(toUse);
		std::vector<unsigned long long int>& auxArray = getAuxArray(toUse);
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

void updateBIT(std::vector<unsigned long long int>& BIT, unsigned long long int index)
{
	// std::cout << "updateBIT begin\n";
	if( index != 0) {
		
		while(index <= BIT.size()) {
			// std::cout << "index: " << index << "\n";
			BIT[index] += 1;
			index += index & (-index);
		}
	}
	// std::cout << "updateBIT end\n";

}

unsigned long long countNumberOfGreaterElements(std::vector<unsigned long long int>& BIT, unsigned long long int pos)
{
	// std::cout << "\n\n\ncountNumberOfGreaterElements begin\n";

	unsigned long long currentPos = pos;
	unsigned long long numberOfGreaterElements = 0;

	while(currentPos) {
		// std::cout << "currentPos: " << currentPos << "\n";
		// std::cout << "new currentPos: " << currentPos << "\n\n";

		numberOfGreaterElements += BIT[currentPos];
		currentPos -= currentPos & (-currentPos);
		// currentPos = currentPos & (~(currentPos & (-currentPos)));
	}

	// std::cout << "countNumberOfGreaterElements end\n";


	return numberOfGreaterElements;
}

template<typename T>
unsigned long long int binary_search(const std::vector<T>& vec, unsigned long long int start, unsigned long long int end, const T& key)
{
    // Termination condition-: start index greater than end index

    // std::cout << "start: " << start << "\n";
    // std::cout << "end: " << end << "\n";
    if(start > end)
    {
    	// std::cout << "error if(start > end)\n";
        return -1;
    }

    // Find the middle element of the vector and use that for splitting
    // the array unsigned long long into two pieces.
    const unsigned long long int middle = start + ((end - start) / 2);

    // std::cout << "vec[middle]: " << vec[middle] << "\n";
    if(vec[middle] == key)
    {
        return middle;
    }
    else if(vec[middle] < key)
    {
        return binary_search(vec, start, middle - 1, key);
    }

    return binary_search(vec, middle + 1, end, key);
}
/*
int main(int argc, char const *argv[]) {
	// std::fstream file_out( "out.txt" , std::fstream::out);
	std::fstream infile( "in.txt" , std::fstream::in);

	std::vector<unsigned long long int> v;
	int a;
	while (infile >> a)
	{
		v.push_back(a);
	}

	std::vector<unsigned long long int> v2(v);
	std::vector<unsigned long long int> v3(v);

	std::vector<unsigned long long int> vBITSort(v);
	std::vector<unsigned long long int> vBITUse(v);

	MergeSort ms(std::move(v));
	{
		auto start = std::chrono::high_resolution_clock::now();
		ms.sort();
		auto finish = std::chrono::high_resolution_clock::now();
		auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(finish-start);
		std::cout << "debug: using My Merge sort - the array was sorted in " << seconds.count() << "milliseconds\n";
	}

	const std::vector<unsigned long long int>& vMS = ms.getSortedArray();

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


	// unsigned long long int curAns = 0;

	// auto start = std::chrono::high_resolution_clock::now();
	// brute_force(v3, curAns);
	// auto finish = std::chrono::high_resolution_clock::now();

	// auto seconds = std::chrono::duration_cast<std::chrono::seconds>(finish-start);
	// std::cout << "It took the brute_force implementation " << seconds.count() << "s to find the number of invertions\n";
	// // std::cout << "It took the brute_force implementation " << seconds.count() << "s to find the number of invertions\n";

	// std::cout << "number of invertions - " << curAns << "\n";

	unsigned long long int curAnsBIT = 0;
	{
		// auto& vSorted = vBITSort;
		// std::sort(vSorted.begin(), vSorted.end(), std::greater<long long int>());
		auto start = std::chrono::high_resolution_clock::now();
		auto& vSorted = vBITSort;
		std::sort(vSorted.begin(), vSorted.end(), std::greater<long long int>());
		std::vector<unsigned long long int> BIT(vSorted.size() + 1);

		for(auto rit = v.rbegin(); rit != v.rend(); rit++) {
			auto elmPos = binary_search<unsigned long long int>(vSorted, 0, vSorted.size(), *rit);

			unsigned long long int numberOfGreaterElementsPassed = countNumberOfGreaterElements(BIT, elmPos);
			unsigned long long int numberOfGreaterElements = elmPos - numberOfGreaterElementsPassed;
			curAnsBIT += numberOfGreaterElements;

			updateBIT(BIT, elmPos + 1);
		}
		// std::vector<unsigned long long int> BIT(vSorted.size() + 1);
		// // initBIT(BIT);


		// unsigned long long int index = 0;
		// for(auto rit = v.rbegin(); rit != v.rend(); rit++) {
		// 	// std::cout << index++ << "\n";

		// 	// std::cout << "*rit: " << *rit << "\n";
		// 	auto startFind = std::chrono::high_resolution_clock::now();
		// 	// auto elIt = std::find(vSorted.begin(), vSorted.end(), *rit);
		// 	auto elmPos = binary_search<unsigned long long int>(vSorted, 0, vSorted.size(), *rit);
		// 	auto finishFind = std::chrono::high_resolution_clock::now();
		// 	// std::cout << "elmPos: " << elmPos << "\n";

		// 	auto secondsFind = std::chrono::duration_cast<std::chrono::nanoseconds>(finishFind-startFind);
		// 	// std::cout << secondsFind.count() << "s to find the number\n";

		// 	// std::cout << "*rit: " << *rit << "\n";

		// 	auto startAdd = std::chrono::high_resolution_clock::now();
		// 	// unsigned long long int pos = std::distance(vSorted.begin(), elIt);
		// 	unsigned long long int numberOfGreaterElementsPassed = countNumberOfGreaterElements(BIT, elmPos);
		// 	// std::cout << "numberOfGreaterElementsPassed: " << numberOfGreaterElementsPassed << "\n";
		// 	unsigned long long int numberOfGreaterElements = elmPos - numberOfGreaterElementsPassed;
		// 	curAnsBIT += numberOfGreaterElements;
		// 	// std::cout << "numberOfGreaterElements: " << numberOfGreaterElements << "\n";

		// 	auto finishAdd = std::chrono::high_resolution_clock::now();

		// 	auto secondsAdd = std::chrono::duration_cast<std::chrono::nanoseconds>(finishAdd-startAdd);
		// 	// std::cout << secondsAdd.count() << "s to add the number\n";



		// 	auto startUpdate = std::chrono::high_resolution_clock::now();

		// 	updateBIT(BIT, elmPos + 1);
		// 	auto finishUpdate = std::chrono::high_resolution_clock::now();

		// 	auto secondsUpdate = std::chrono::duration_cast<std::chrono::nanoseconds>(finishUpdate-startUpdate);
		// 	// std::cout << secondsUpdate.count() << "s to update the array\n\n\n";

		// }
		auto finish = std::chrono::high_resolution_clock::now();

		auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(finish-start);
		std::cout << "It took the BIT implementation " << seconds.count() << "milliseconds to find the number of invertions\n";
	}


	if(ms.getInversionCount() == curAnsBIT) {
		std::cout << "\n\nThe number of invertions match!\n";
	} else {
		std::cout << "curAnsBIT: " << curAnsBIT << "\n";
		std::cout << "ms.getInversionCount(): " << ms.getInversionCount() << "\n";
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

	enum AlgoToUse
	{
		MergeSortAlgo,
		BITAlgo
	};

	AlgoToUse algo = BITAlgo;

	int inputIndex = 0;
	std::string inputNumStr;

	std::vector<unsigned long long int> TC;
	InputState is = GET_ARRAY_SIZE;
	int currentArraySize = 0;
	int currentArrayIndex = 0;

	int curNum = 0;

	int numberOfTestCases = 0;
	while (input >> inputNumStr)
	{
		if(inputIndex == 0) {
			numberOfTestCases = std::stoi(inputNumStr);
			inputIndex++;
			continue;
		}

		switch(is)
		{
		case GET_ARRAY_SIZE:
			currentArraySize = std::stoi(inputNumStr);

			TC.clear();
			currentArrayIndex = 0;
			is = GET_ARRAY_ELEMENT;

			break;
		case GET_ARRAY_ELEMENT:
			curNum = std::stoi(inputNumStr);
			TC.push_back(curNum);

			currentArrayIndex++;
			if(currentArrayIndex == currentArraySize) {
				is = FIND_ANS;
			}
			else
			{
			break;
			}
		case FIND_ANS:
		{
			switch(algo)
			{
			case BITAlgo:
				{
					unsigned long long int curAnsBIT = 0;
					std::vector<unsigned long long int> v(TC);
					auto& vSorted = TC;
					std::sort(vSorted.begin(), vSorted.end(), std::greater<unsigned long long int>());
					std::vector<unsigned long long int> BIT(vSorted.size() + 1);

					for(auto rit = v.rbegin(); rit != v.rend(); rit++) {
						auto elmPos = binary_search<unsigned long long int>(vSorted, 0, vSorted.size(), *rit);

						unsigned long long int numberOfGreaterElementsPassed = countNumberOfGreaterElements(BIT, elmPos);
						unsigned long long int numberOfGreaterElements = elmPos - numberOfGreaterElementsPassed;
						curAnsBIT += numberOfGreaterElements;

						updateBIT(BIT, elmPos + 1);
					}
					std::cout << curAnsBIT << "\n";
					break;
				}
			case MergeSortAlgo:
				{
					MergeSort ms(std::move(TC));
					auto start = std::chrono::high_resolution_clock::now();
					ms.sort();
					std::cout << ms.getInversionCount() << "\n";
					break;
				}
			}

			is = GET_ARRAY_SIZE;

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
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <map>

#include "bprinter\table_printer.h"

using namespace std;

typedef std::chrono::high_resolution_clock high_resolution_clock;
typedef std::chrono::milliseconds milliseconds;

//move
class Timer
{
public:
	explicit Timer(bool run = false)
	{
		if (run)
			Reset();
	}

	void Reset()
	{
		_start = high_resolution_clock::now();
	}

	milliseconds Elapsed() const
	{
		return std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - _start);
	}

	template <typename T, typename Traits>
	friend std::basic_ostream<T, Traits>& operator<<(std::basic_ostream<T, Traits>& out, const Timer& timer)
	{
		return out << timer.Elapsed().count();
	}
private:
	high_resolution_clock::time_point _start;
};


// RVO
std::vector<int> getInputVector(std::istream& input)
{
	int num = 0;
	std::vector<int> v;

	while(input >> num) {
		v.push_back(num);
	}

	return v;
}

enum Algos
{
	BRUTEFORCE_BITONIC_ARRAY_SEARCH,
	BINARY_BITONIC_ARRAY_SEARCH,
	NUMBER_OF_ALGORITHMS
};

bool bruteForceBitonicArraySearch(std::vector<int>& v, int x)
{
	bool res = false;
	for(unsigned i = 0; i < v.size(); ++i) {
		if(v[i] == x) {
			res = true;
			break;
		}
	}

	std::cout << "[Brute-force] Bitonic Array Search found " << x << " - " << res << ")\n";

	return 0;
}

class BitonicArraySide {
public:
	// BitonicArraySide(int minIndex, int maxIndex) :
	BitonicArraySide(int minIndex) :
		m_minIndex(minIndex),
		// m_maxIndex(maxIndex),
		m_needToCheck(true)
	{}

	~BitonicArraySide() = default;
	int getMinIndex() const { return m_minIndex; }
	void setMinIndex(int newMinValue) { m_minIndex = newMinValue; }
	// int getMaxIndex() const { return m_maxIndex; }

	bool stillNeedToCheck() const { return m_needToCheck; }
	void checked() { m_needToCheck = false; }
private:
	int m_minIndex;
	// int m_maxIndex;
	bool m_needToCheck;
};

class BitonicArray
{
public:
	BitonicArray(const std::vector<int>& v) :
		m_aSide(0),
		m_bSide(v.size() - 1),
		m_array(v),
		m_level(0)
	{}

	~BitonicArray() = default;

	bool searchFor(int x)
	{
		m_searchingFor = x;
		return devideAndConquer();
	}
private:
	bool devideAndConquer()
	{
		m_level++;
		int rangeBeginingIndex = m_aSide.getMinIndex();
		int rangeEndingIndex = m_bSide.getMinIndex();

		// std::cout << "\n--------------------------------------------------\n";
		// std::cout << "devideAndConquer level - " << m_level << "\n";
		// std::cout << "rangeBeginingIndex - " << rangeBeginingIndex << "\n";
		// std::cout << "rangeEndingIndex - " << rangeEndingIndex << "\n";

		int rangeMiddelIndex = rangeBeginingIndex + (rangeEndingIndex - rangeBeginingIndex) / 2;
		int rangeQuarter1Index = rangeBeginingIndex + (rangeMiddelIndex - rangeBeginingIndex) / 2;
		int rangeQuarter2Index = rangeMiddelIndex + (rangeEndingIndex - rangeMiddelIndex) / 2;

		int rangeMiddelValue = m_array[rangeMiddelIndex];
		int rangeQuarter1Value = m_array[rangeQuarter1Index];
		int rangeQuarter2Value = m_array[rangeQuarter2Index];

		// std::cout << "\n";
		// std::cout << "rangeMiddelIndex - " << rangeMiddelIndex << "\n";
		// std::cout << "rangeQuarter1Index - " << rangeQuarter1Index << "\n";
		// std::cout << "rangeQuarter2Index - " << rangeQuarter2Index << "\n";

		SideType quarter1SideType = determineSide(rangeQuarter1Index);
		SideType quarter2SideType = determineSide(rangeQuarter2Index);
		SideType middelSideType = determineSide(rangeMiddelIndex);

		// std::cout << "\n";
		// std::cout << "quarter1SideType - " << sideTypeToString(quarter1SideType) << "\n";
		// std::cout << "quarter2SideType - " << sideTypeToString(quarter2SideType) << "\n";
		// std::cout << "middelSideType - " << sideTypeToString(middelSideType) << "\n";

		bool found = false;
		if(quarter1SideType == SideType::CENTER || quarter2SideType == SideType::CENTER || middelSideType == SideType::CENTER) {
			// std::cout << "found the center\n TODO: implement the bin search";
			// return false;
			int centerIndex = rangeQuarter1Index;
			if(quarter2SideType == SideType::CENTER) {
				centerIndex = rangeQuarter2Index;
			}

			if(middelSideType == SideType::CENTER) {
				centerIndex = rangeMiddelIndex;
			}

			found = binsearch(m_aSide.getMinIndex(), centerIndex);
			if(found) {
				return true;
			}
			found = binsearch(m_aSide.getMinIndex(), centerIndex);
			return found;
		}

		if(quarter1SideType == quarter2SideType) {
			if(quarter1SideType == SideType::SIDE_A) {
				if(rangeQuarter2Value > m_searchingFor) {
					if(rangeMiddelValue > m_searchingFor) {
						if(rangeQuarter1Value > m_searchingFor) {
							// launch bin search from  quarter1Index to m_ASide min index
							found = binsearch(m_aSide.getMinIndex(), rangeQuarter1Index);
						} else {
							// launch bin search from  quarter1Index to middelSide index
							found = binsearch(rangeQuarter1Index, rangeMiddelIndex);
						}
					} else {
						// launch bin search from  middelSide to quarter2Index index
						found = binsearch(rangeMiddelIndex, rangeQuarter2Index);
					}
				} else {
					// make quarter2Index the m_ASide min index
					m_aSide.setMinIndex(rangeQuarter2Index);
					return devideAndConquer();
				}
			} else { // quarter1SideType == SideType::SIDE_B
				if(rangeQuarter1Value > m_searchingFor) {
					if(rangeMiddelValue > m_searchingFor) {
						if(rangeQuarter2Value > m_searchingFor) {
							// launch bin search from  quarter1Index to m_ASide min index
							found = reverseOrderBinsearch(rangeQuarter2Index, m_bSide.getMinIndex());
						} else {
							// launch bin search from  quarter1Index to middelSide index
							found = reverseOrderBinsearch(rangeMiddelIndex, rangeQuarter2Index);
						}
					} else {
						// launch bin search from  middelSide to quarter2Index index
						found = reverseOrderBinsearch(rangeQuarter1Index, rangeMiddelIndex);
					}
				} else {
					// make quarter2Index the m_ASide min index
					m_bSide.setMinIndex(rangeQuarter1Index);
					return devideAndConquer();
				}
			}
		} else {
			// todo: when the quarters are on diffrent sides of the bitonic array

			if(rangeQuarter1Value > m_searchingFor) {
				found = binsearch(m_aSide.getMinIndex(), rangeQuarter1Index);
				m_aSide.setMinIndex(rangeQuarter1Index);
			}
			if(!found) {
				if(rangeQuarter2Value > m_searchingFor) {
					found = reverseOrderBinsearch(rangeQuarter1Index, m_bSide.getMinIndex());
					m_bSide.setMinIndex(rangeQuarter2Index);
				}
			}

			if(!found) {
				if(middelSideType == SideType::SIDE_A) {
					found = binsearch(m_aSide.getMinIndex(), rangeMiddelIndex);
					m_aSide.setMinIndex(rangeMiddelIndex);
				} else {
					found = binsearch(rangeMiddelIndex, m_bSide.getMinIndex());
					m_bSide.setMinIndex(rangeMiddelIndex);
				}
			}

			if(!found) {
				return devideAndConquer();
			}
		}

		return found;
	}

	bool reverseOrderBinsearch(int lo, int hi)
	{
		return binsearch(lo, hi, true);
	}

	bool binsearch(int lo, int hi, bool reverseOrder = false)
	{
		int mid = lo + (hi - lo) / 2;
		while(lo < hi) {
			if(m_array[mid] == m_searchingFor) {
				return true;
			}

			if(reverseOrder) {
				if(m_array[mid] > m_searchingFor) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			} else {
				if(m_array[mid] > m_searchingFor) {
					hi = mid - 1;
				} else {
					lo = mid + 1;
				}
			}

			mid = lo + (hi - lo) / 2;
		}

		if (m_array[mid] == m_searchingFor) {
			return true;
		}
		return false;
	}

	enum SideType
	{
		SIDE_A,
		SIDE_B,
		CENTER,
		UNKNOWN
	};

	std::string sideTypeToString(SideType st)
	{
		switch(st)
		{
		case SIDE_A:
			return "SIDE_A";
			break;
		case SIDE_B:
			return "SIDE_B";
			break;
		case CENTER:
			return "CENTER";
			break;
		default:
			return "UNKNOWN";
			break;
		};
	}

	SideType determineSide(int index)
	{
		int curNum = m_array[index];
		int prevNum = 0;
		int nextNum = 0;

		bool greaterThanPrev = false;
		if(index != 0 ) {
			prevNum = m_array[index - 1];
			greaterThanPrev = prevNum < curNum;
		}

		bool greaterThanNext = false;
		if(index < m_array.size() - 1) {
			nextNum = m_array[index + 1];
			greaterThanNext = nextNum < curNum;
		}

		if(greaterThanNext && !greaterThanPrev) {
			return SideType::SIDE_B;
		}

		if(!greaterThanNext && greaterThanPrev) {
			return SideType::SIDE_A;
		}

		if(greaterThanNext && greaterThanPrev) {
			return SideType::CENTER;
		}

		return SideType::UNKNOWN;
	}

	BitonicArraySide m_aSide;
	BitonicArraySide m_bSide;

	std::vector<int> m_array;

	int m_searchingFor;
	int m_level;
};

bool binaryBitonicArraySearch(std::vector<int>& v, int x)
{
	BitonicArray ba(v);

	bool res = ba.searchFor(x);

	std::cout << "[Logarithmic] Bitonic Array Search found " << x << " - " << res << ")\n";

	return 0;
}

int testAlgo(bool (*algoFunc)(std::vector<int>&, int), std::vector<double>& prevTimes, int algoIndex, const std::vector<int>& v, int x)
{
	Timer t;

	std::vector<int> vTmp(v);
	t.Reset();
	bool res = algoFunc(vTmp, x);

	int time = t.Elapsed().count();
	// if(prevTimes[algoIndex] == 0) {
	// 	prevTimes[algoIndex] = time;
	// }

	return time;
}

int main(int argc, char const *argv[]) {

	std::vector<std::string> vInputFiles;
	//vInputFiles = { "bitonicCenter1KInts.txt"};
	vInputFiles = { "bitonicCenter1KInts.txt", "bitonicCenter2KInts.txt", "bitonicCenter4KInts.txt", "bitonicCenter8KInts.txt", "bitonicCenter16KInts.txt", "bitonicCenter32KInts.txt"};
	std::string pathToInputDir("../testing/");

	std::map<std::string, int> notPresentIntMap;
	notPresentIntMap.insert(std::pair<std::string, int>("bitonicCenter1KInts.txt", 927));
	notPresentIntMap.insert(std::pair<std::string, int>("bitonicCenter2KInts.txt", 927));
	notPresentIntMap.insert(std::pair<std::string, int>("bitonicCenter4KInts.txt", 927));
	notPresentIntMap.insert(std::pair<std::string, int>("bitonicCenter8KInts.txt", 927));
	notPresentIntMap.insert(std::pair<std::string, int>("bitonicCenter16KInts.txt", 927));
	notPresentIntMap.insert(std::pair<std::string, int>("bitonicCenter32KInts.txt", 927));


	std::fstream file_out( "algo_out.txt" , std::fstream::out);
	//std::ostream& output = std::cout;
	std::ostream& output = file_out;

	output << std::setprecision(5);

	bprinter::TablePrinter tp(&output);
	tp.AddColumn("Input", 30);
	tp.AddColumn("Comment", 40);
	tp.AddColumn("Brute-force bitonic array search Time (ms)", 30);
	tp.AddColumn("BF BAS Doubling Ratio", 30);
	tp.AddColumn("BF BAS Average time (ms)", 30);

	tp.AddColumn("Binary Search bitonic array search Time (ms)", 30);
	tp.AddColumn("BF BAS Doubling Ratio", 30);
	tp.AddColumn("BF BAS Average time (ms)", 30);

	tp.PrintHeader();

	std::vector<double> prevTimes(int(NUMBER_OF_ALGORITHMS), 0.0);
	std::vector<double> averageTime(int(NUMBER_OF_ALGORITHMS), 0.0);
	int res = 0;
	int time = 0;
	double avtime = 0;
	for(auto&& fileName : vInputFiles) {

		std::string inputFile = fileName;
		std::string pathToInputFile = pathToInputDir + inputFile;
		std::fstream file( pathToInputFile , std::fstream::in);
		std::istream& input = file;

		std::vector<int> v = getInputVector(input);
		file.close();

		averageTime[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] = 0.0;
		averageTime[Algos::BINARY_BITONIC_ARRAY_SEARCH] = 0.0;
		int searchFor = 0;
		// search for preset int left side
		searchFor = v[0];
		time = testAlgo(bruteForceBitonicArraySearch, prevTimes, Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH, v, searchFor);
		tp << fileName << "search for preset int left side" << time << time / prevTimes[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] << "";
		averageTime[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] += time;

		time = testAlgo(binaryBitonicArraySearch, prevTimes, Algos::BINARY_BITONIC_ARRAY_SEARCH, v, searchFor);
		tp << time << time / prevTimes[Algos::BINARY_BITONIC_ARRAY_SEARCH] << "";
		averageTime[Algos::BINARY_BITONIC_ARRAY_SEARCH] += time;

		// search for preset int center
		searchFor = v[int(v.size()/2)];
		time = testAlgo(bruteForceBitonicArraySearch, prevTimes, Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH, v, searchFor);
		tp << fileName << "search for preset int center" << time << time / prevTimes[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] << "";
		averageTime[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] += time;

		time = testAlgo(binaryBitonicArraySearch, prevTimes, Algos::BINARY_BITONIC_ARRAY_SEARCH, v, searchFor);
		tp << time << time / prevTimes[Algos::BINARY_BITONIC_ARRAY_SEARCH] << "";
		averageTime[Algos::BINARY_BITONIC_ARRAY_SEARCH] += time;


		// search for preset int right side
		searchFor = v[v.size() - 1];
		time = testAlgo(bruteForceBitonicArraySearch, prevTimes, Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH, v, searchFor);
		tp << fileName << "search for preset int right side" << time << time / prevTimes[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] << "";
		averageTime[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] += time;

		time = testAlgo(binaryBitonicArraySearch, prevTimes, Algos::BINARY_BITONIC_ARRAY_SEARCH, v, searchFor);
		tp << time << time / prevTimes[Algos::BINARY_BITONIC_ARRAY_SEARCH] << "";
		averageTime[Algos::BINARY_BITONIC_ARRAY_SEARCH] += time;

		// search for none preset int
		searchFor = notPresentIntMap[inputFile];
		time = testAlgo(bruteForceBitonicArraySearch, prevTimes, Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH, v, searchFor);
		tp << fileName << "search for none preset int" << time << time / prevTimes[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] << "";
		averageTime[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] += time;

		time = testAlgo(binaryBitonicArraySearch, prevTimes, Algos::BINARY_BITONIC_ARRAY_SEARCH, v, searchFor);
		tp << time << time / prevTimes[Algos::BINARY_BITONIC_ARRAY_SEARCH] << "";
		averageTime[Algos::BINARY_BITONIC_ARRAY_SEARCH] += time;

		averageTime[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH] = averageTime[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH]/4;
		tp << fileName << "the average time in ms" << "" << "" << averageTime[Algos::BRUTEFORCE_BITONIC_ARRAY_SEARCH];

		averageTime[Algos::BINARY_BITONIC_ARRAY_SEARCH] = averageTime[Algos::BINARY_BITONIC_ARRAY_SEARCH]/4;
		tp << "" << "" << averageTime[Algos::BINARY_BITONIC_ARRAY_SEARCH];
	}

	tp.PrintFooter();

	file_out.close();

	return 0;
}
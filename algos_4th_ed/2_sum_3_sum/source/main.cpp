#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

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
	TWO_SUM_BRUTEFORCE,
	TWO_SUM_BINSEARCH,
	THREE_SUM_BRUTEFORCE,
	THREE_SUM_BINSEARCH,
	NUMBER_OF_ALGORITHMS
};

int threeSumBruteforce(/*const*/ std::vector<int>& vecInts)
{
	int count = 0;
	std::sort(vecInts.begin(), vecInts.end());

	for(unsigned i = 0; i < vecInts.size(); ++i) {
		for(unsigned j = i + 1; j < vecInts.size(); ++j) {
			for(unsigned k = j + 1; k < vecInts.size(); ++k) {
				if(vecInts[j] + vecInts[i] + vecInts[k] == 0) {
					std::cout << vecInts[i] << " + " << vecInts[j] << " + " << vecInts[k] << "; index " << i << " + " << j << " + " << k << "\n";
					count++;
				}
			}
		}
	}

	std::cout << "threeSumBruteforce found " << count << " threes;\n";

	return count;
}

int threeSumBinSearch(std::vector<int>& vecInts)
{
	int count = 0;

	std::cout << "\n\n\n\nthreeSumBinSearch\n";

	std::sort(vecInts.begin(), vecInts.end());
	int lo = 0;
	int hi = 0;
	for(unsigned i = 0; i < vecInts.size(); ++i) {
		for(unsigned j = i + 1; j < vecInts.size(); ++j) {

			/*if(vecInts[i] > 0) {  vstepano to be optimized
				break;
			}*/
			//lo = j + 1;
			lo = j;
			hi = vecInts.size() - 1;

			int searchFor = (vecInts[i] + vecInts[j]) * (-1);
			// if(searchFor < 0) {
			// 	/* code */
			// }
			//std::cout << "searching for " << searchFor << "\n";
			while(lo < hi) {

				int mid = lo + (hi - lo)/2;

				//std::cout << "lo " << lo << " : " << vecInts[lo] << "\n";
				//std::cout << "mid " << mid << " : " << vecInts[mid] << "\n";
				//std::cout << "hi " << hi << " : " << vecInts[hi] << "\n";

				if(vecInts[mid] == searchFor) {
					std::cout << vecInts[i] << " + " << vecInts[j] << " + " << vecInts[mid] << "; index " << i << " + " << j << " + " << mid << "\n";
					count++;
					break;
				}

				if(vecInts[mid] > searchFor) {
					hi = mid;
				} else {
					lo = mid + 1;
				}
			}
		}
	}

	std::cout << "threeSumBinSearch found " << count << " threes;\n";

	return count;
}

int twoSumBruteforce(/*const*/ std::vector<int>& vecInts)
{
	int count = 0;

	for(unsigned i = 0; i < vecInts.size(); ++i) {
		for(unsigned j = i; j < vecInts.size(); ++j) {
			if(vecInts[j] + vecInts[i] == 0) {
				count++;
			}
		}
	}

	std::cout << "twoSumBruteforce found " << count << " pairs;\n";

	return count;
}

int twoSumBinSearch(std::vector<int>& vecInts)
{
	int count = 0;

	std::sort(vecInts.begin(), vecInts.end());
	int lo = 0;
	int hi = 0;
	for(unsigned i = 0; i < vecInts.size(); ++i) {
		if(vecInts[i] > 0) {
			break;
		}
		lo = i + 1;
		hi = vecInts.size() - 1;

		int searchFor = vecInts[i] * (-1);
		//std::cout << "searching for " << searchFor << "\n";
		while(lo < hi) {

			int mid = lo + (hi - lo)/2;

			//std::cout << "lo " << lo << " : " << vecInts[lo] << "\n";
			//std::cout << "mid " << mid << " : " << vecInts[mid] << "\n";
			//std::cout << "hi " << hi << " : " << vecInts[hi] << "\n";

			if(vecInts[mid] == searchFor) {
				count++;
				break;
			}

			if(vecInts[mid] > searchFor) {
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
	}

	std::cout << "twoSumBinSearch found " << count << " pairs;\n";

	return count;
}

double testAlgo(int (*algoFunc)(std::vector<int>&), std::vector<double>& prevTimes, int algoIndex, const std::vector<int>& v)
{
	Timer t;

	std::vector<int> vTmp(v);
	t.Reset();
	int res = algoFunc(vTmp);

	double time = t.Elapsed().count();
	if(prevTimes[algoIndex] == 0) {
		prevTimes[algoIndex] = time;
	}

	return time;
}

int main(int argc, char const *argv[]) {

	std::vector<std::string> vInputFiles;
	// vInputFiles = { "1Kints.txt", "2Kints.txt", "4Kints.txt", "8Kints.txt", "16Kints.txt", "32Kints.txt" };
	vInputFiles = { "1Kints.txt", "2Kints.txt"};
	std::string pathToInputDir("../testing/");

	std::fstream file_out( "algo_out.txt" , std::fstream::out);
	//std::ostream& output = std::cout;
	std::ostream& output = file_out;

	output << std::setprecision(5);

	bprinter::TablePrinter tp(&output);
	tp.AddColumn("Input", 15);
	//tp.AddColumn("Two Sum Brute-force Time (ms)", 30);
	//tp.AddColumn("TS BF Doubling Ratio", 30);
	//tp.AddColumn("Two Sum Bin Search Time (ms)", 30);
	//tp.AddColumn("TS BS Doubling Ratio", 30);
	tp.AddColumn("Three Sum Brute-force Time (ms)", 30);
	tp.AddColumn("3S BF Doubling Ratio", 30);
	tp.AddColumn("Three Sum Bin Search Time (ms)", 30);
	tp.AddColumn("3S BS Doubling Ratio", 30);

	tp.PrintHeader();

	std::vector<double> prevTimes(int(NUMBER_OF_ALGORITHMS), 0.0);
	int res = 0;
	double time = 0;
	for(auto&& fileName : vInputFiles) {

		std::string inputFile = fileName;
		std::string pathToInputFile = pathToInputDir + inputFile;
		std::fstream file( pathToInputFile , std::fstream::in);
		std::istream& input = file;

		std::vector<int> v = getInputVector(input);
		file.close();

		tp << fileName;

		// double time = testAlgo(twoSumBruteforce, prevTimes, Algos::TWO_SUM_BRUTEFORCE, v);
		// tp << time << time / prevTimes[Algos::TWO_SUM_BRUTEFORCE] ;
		// prevTimes[Algos::TWO_SUM_BRUTEFORCE] = time;

		// time = testAlgo(twoSumBinSearch, prevTimes, Algos::TWO_SUM_BINSEARCH, v);
		// tp << time << time / prevTimes[Algos::TWO_SUM_BINSEARCH] ;
		// prevTimes[Algos::TWO_SUM_BINSEARCH] = time;

		time = testAlgo(threeSumBruteforce, prevTimes, Algos::THREE_SUM_BRUTEFORCE, v);
		tp << time << time / prevTimes[Algos::THREE_SUM_BRUTEFORCE] ;
		prevTimes[Algos::THREE_SUM_BRUTEFORCE] = time;

		time = testAlgo(threeSumBinSearch, prevTimes, Algos::THREE_SUM_BINSEARCH, v);
		tp << time << time / prevTimes[Algos::THREE_SUM_BINSEARCH] ;
		prevTimes[Algos::THREE_SUM_BINSEARCH] = time;
	}

	tp.PrintFooter();

	file_out.close();

	return 0;
}
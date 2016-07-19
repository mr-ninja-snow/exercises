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
typedef std::chrono::nanoseconds nanoseconds;

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

	nanoseconds Elapsed() const
	{
		return std::chrono::duration_cast<nanoseconds>(high_resolution_clock::now() - _start);
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
	FIBONACCI_SEARCH,
	BINARY_SEARCH,
	NUMBER_OF_ALGORITHMS
};

bool binarySearch(const std::vector<int>& v, int x)
{
	std::cout << "binarySearch    - ";
	int lo = 0;
	int hi = v.size() - 1;
	int mid = 0;
	while(lo < hi) {
		mid = lo + (hi - lo) / 2;

		if(v[mid] > x) {
			hi = mid - 1;
		} else {
			if(v[mid] < x) {
				lo = mid + 1;
			} else {
				return true;
			}
		}
	}

	if (v[lo] == x) {
		return true;
	}
	return false;
}

bool fibonacciSearchImp(const std::vector<int>& v, int x, int lo, int hi)
{
	int tmp = 0;
	int previousFibonacci = 1;
	int currentFibonacci = 1;

	while(currentFibonacci - lo < hi) {
		tmp = currentFibonacci;
		currentFibonacci += previousFibonacci;
		previousFibonacci = tmp;
	}

	while(hi - lo > 1) {
		int mid = lo + currentFibonacci - previousFibonacci;

		// std::cout << "lo - " << lo << "\n";
		// std::cout << "mid - " << mid << "\n";
		// std::cout << "hi - " << hi << "\n";

		if(v[mid] < x) {
			lo = mid + 1;
			//fibonacciSearchImp(v, x, lo, hi);
			while (hi - lo < currentFibonacci) {
				// std::cout << "\nhi - lo = " << hi - lo << "\n";
				// std::cout << "currentFibonacci = " << currentFibonacci << "\n";
				// std::cout << "previousFibonacci = " << previousFibonacci << "\n";

				tmp = previousFibonacci;
				previousFibonacci = currentFibonacci - previousFibonacci;
				currentFibonacci = tmp;
			}
		} else {
			if(v[mid] > x) {
				//currentFibonacci = previousFibonacci;
				//previousFibonacci = mid;
				hi = mid - 1;
				while (hi - lo < currentFibonacci) {
					// std::cout << "\nhi - lo = " << hi - lo << "\n";
					// std::cout << "currentFibonacci = " << currentFibonacci << "\n";
					// std::cout << "previousFibonacci = " << previousFibonacci << "\n";

					tmp = previousFibonacci;
					previousFibonacci = currentFibonacci - previousFibonacci;
					currentFibonacci = tmp;
				}
				// lo++;
				// return fibonacciSearchImp(v, x, lo, hi);
			} else {
				return true;
			}
		}

	}

	if (v[hi] == x) {
		return true;
	}

	/*while(true) {
		tmp = currentFibonacci;
		currentFibonacci += previousFibonacci;
		previousFibonacci = tmp;

		if(lo + currentFibonacci < v.size() - 1) {

			if(v[lo + currentFibonacci] > x) {
				lo = lo + currentFibonacci;
			} else {
				if(v[lo + currentFibonacci] < x) {
					hi = lo + currentFibonacci;
					lo++;
					return fibonacciSearchImp(v, x, lo, hi);
				} else {
					return true;
				}
			}
		} else {
			if(hi - lo > 1) {
				hi = v.size() - 1;
				return fibonacciSearchImp(v, x, lo, hi);
			} else {
				break;
			}
		}
	}*/

	// if (v[mid] == x) {
	// 	return true;
	// }
	return false;
}

bool fibonacciSearch(const std::vector<int>& v, int x)
{
	std::cout << "fibonacciSearch - ";
	if(x > v[0] && x < v[v.size() - 1]) {
		return fibonacciSearchImp(v, x, 0, v.size() - 1);
	} else {
		if(x == v[0] || x == v[v.size() - 1]) {
			return true;
		}
	}
	return false;
}

long long testAlgo(bool (*algoFunc)(const std::vector<int>&, int), std::vector<double>& prevTimes, int algoIndex, const std::vector<int>& v, int x)
{
	Timer t;

	std::vector<int> vTmp(v);
	t.Reset();
	bool res = algoFunc(vTmp, x);

	if(res) {
		std::cout << "found " << x;
	} else {
		std::cout << "didn't find " << x;
	}

	long long time = t.Elapsed().count();
	// if(prevTimes[algoIndex] == 0) {
	// 	prevTimes[algoIndex] = time;
	// }

	return time;
}

int main(int argc, char const *argv[]) {

	std::vector<std::string> vInputFiles;
	//vInputFiles = { "1KInts.txt"};
	vInputFiles = { "1KInts.txt", "2KInts.txt", "4KInts.txt", "8KInts.txt", "16KInts.txt", "32KInts.txt"};
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
	tp.AddColumn("Binary Search Time (ns)", 30);
	tp.AddColumn("BS Average time (ns)", 30);

	tp.AddColumn("Fibonacci Search Time (ns)", 30);
	tp.AddColumn("BF BAS Average time (ns)", 30);

	tp.PrintHeader();
	std::vector<double> prevTimes(int(NUMBER_OF_ALGORITHMS), 0.0);
	std::vector<double> averageTime(int(NUMBER_OF_ALGORITHMS), 0.0);

	for(auto&& fileName : vInputFiles) {
		std::cout << fileName << "\n";
		std::string inputFile = fileName;
		std::string pathToInputFile = pathToInputDir + inputFile;
		std::fstream file( pathToInputFile , std::fstream::in);
		std::istream& input = file;

		std::vector<int> v = getInputVector(input);
		file.close();

		std::sort(v.begin(), v.end());
		averageTime[Algos::BINARY_SEARCH] = 0.0;
		averageTime[Algos::FIBONACCI_SEARCH] = 0.0;

		// search for preset int left side
		std::cout << "\nleft side ";
		int searchFor = v[1];
		long long time = testAlgo(binarySearch, prevTimes, Algos::BINARY_SEARCH, v, searchFor);
		tp << fileName << "search for preset int left side" << time << 0;// << time / prevTimes[Algos::BINARY_SEARCH] << "";
		averageTime[Algos::BINARY_SEARCH] += time;

		std::cout << "\nleft side ";
		time = testAlgo(fibonacciSearch, prevTimes, Algos::FIBONACCI_SEARCH, v, searchFor);
		tp << time << 0; // << time / prevTimes[Algos::FIBONACCI_SEARCH] << "";
		averageTime[Algos::FIBONACCI_SEARCH] += time;

		std::cout << "\ncenter ";
		// search for preset int center
		searchFor = v[int(v.size()/2)];
		time = testAlgo(binarySearch, prevTimes, Algos::BINARY_SEARCH, v, searchFor);
		tp << fileName << "search for preset int center" << time << 0; // << time / prevTimes[Algos::BINARY_SEARCH] << "";
		averageTime[Algos::BINARY_SEARCH] += time;

		std::cout << "\ncenter ";
		time = testAlgo(fibonacciSearch, prevTimes, Algos::FIBONACCI_SEARCH, v, searchFor);
		tp << time << 0; // << time / prevTimes[Algos::FIBONACCI_SEARCH] << "";
		averageTime[Algos::FIBONACCI_SEARCH] += time;

		std::cout << "\nright side ";
		// search for preset int right side
		searchFor = v[v.size() - 2];
		time = testAlgo(binarySearch, prevTimes, Algos::BINARY_SEARCH, v, searchFor);
		tp << fileName << "search for preset int right side" << time << 0; // << time / prevTimes[Algos::BINARY_SEARCH] << "";
		averageTime[Algos::BINARY_SEARCH] += time;

		std::cout << "\nright side ";
		time = testAlgo(fibonacciSearch, prevTimes, Algos::FIBONACCI_SEARCH, v, searchFor);
		tp << time << 0; // << time / prevTimes[Algos::FIBONACCI_SEARCH] << "";
		averageTime[Algos::FIBONACCI_SEARCH] += time;

		std::cout << "\nnone preset ";
		// search for none preset int
		searchFor = notPresentIntMap[inputFile];
		time = testAlgo(binarySearch, prevTimes, Algos::BINARY_SEARCH, v, searchFor);
		tp << fileName << "search for none preset int" << time << 0; // << time / prevTimes[Algos::BINARY_SEARCH] << "";
		averageTime[Algos::BINARY_SEARCH] += time;

		std::cout << "\nnone preset ";
		time = testAlgo(fibonacciSearch, prevTimes, Algos::FIBONACCI_SEARCH, v, searchFor);
		tp << time << 0;
		averageTime[Algos::FIBONACCI_SEARCH] += time;

		averageTime[Algos::BINARY_SEARCH] = averageTime[Algos::BINARY_SEARCH]/4;
		tp << fileName << "the average time in ns" << "" << averageTime[Algos::BINARY_SEARCH];

		averageTime[Algos::FIBONACCI_SEARCH] = averageTime[Algos::FIBONACCI_SEARCH]/4;
		tp << "" << averageTime[Algos::FIBONACCI_SEARCH];

		// for (size_t i = 0; i < v.size(); i++)
		// {
		// 	int searchFor = v[i];
		// 	if (fibonacciSearch(v, searchFor)) {
		// 		std::cout << "Found ";
		// 	}
		// 	else {
		// 		std::cout << "Didn't find ";
		// 	}
		// 	std::cout << searchFor << "\n";
		// }

		// int searchFor = 453302;
		// if (fibonacciSearch(v, searchFor)) {
		// 	std::cout << "Found ";
		// }
		// else {
		// 	std::cout << "Didn't find ";
		// }
		// std::cout << searchFor << "\n";
	}

	tp.PrintFooter();

	file_out.close();

	return 0;
}
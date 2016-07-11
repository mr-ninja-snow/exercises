#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <set>

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
std::vector<double> getInputVector(std::istream& input)
{
	double num = 0;
	std::vector<double> v;

	while(input >> num) {
		v.push_back(num);
	}

	return v;
}

enum Algos
{
	BRUTEFORCE_COLSEST_PAIR,
	LINEAR_LOGARITHMIC_COLSEST_PAIR,
	NUMBER_OF_ALGORITHMS
};

int bruteForceColsestPair(std::vector<double>& v)
{
	double minDiff = std::numeric_limits<double>::max();
	int indexA = -1;
	int indexB = -1;
	for(unsigned i = 0; i < v.size(); ++i) {
		for(unsigned j = i + 1; j < v.size(); ++j) {
			double diff = std::abs(v[i]-v[j]);
			if(diff < minDiff) {
				minDiff = diff;
				indexA = i;
				indexB = j;
			}
		}
	}

	std::cout << "[Brute-force] The cousest pair is " << v[indexB] << " - " << v[indexA] << " (diff = " << std::abs(v[indexB]  - v[indexA]) << ")\n";

	return 0;
}

int linLogColsestPair(std::vector<double>& v)
{
	double minDiff = std::numeric_limits<double>::max();
	int indexA = -1;
	int indexB = -1;
	std::sort(v.begin(), v.end());

	for (unsigned i = 0; i < v.size() - 1; ++i) {
			double diff = std::abs(v[i] - v[i+1]);
			if (diff < minDiff) {
				minDiff = diff;
				indexA = i;
				indexB = i + 1;
			}
	}

	std::cout << "[Linear Logarithmic] The cousest pair is " << v[indexB] << " - " << v[indexA] << " (diff = " << std::abs(v[indexB] - v[indexA]) << ")\n";

	return 0;
}

double testAlgo(int (*algoFunc)(std::vector<double>&), std::vector<double>& prevTimes, int algoIndex, const std::vector<double>& v)
{
	Timer t;

	std::vector<double> vTmp(v);
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
	vInputFiles = { "1Kdoubles.txt", "2Kdoubles.txt", "4Kdoubles.txt", "8Kdoubles.txt", "16Kdoubles.txt", "32Kdoubles.txt" };
	std::string pathToInputDir("../testing/");

	std::fstream file_out( "algo_out.txt" , std::fstream::out);
	//std::ostream& output = std::cout;
	std::ostream& output = file_out;

	output << std::setprecision(5);

	bprinter::TablePrinter tp(&output);
	tp.AddColumn("Input", 15);
	tp.AddColumn("Brute-force Colsest pair Time (ms)", 30);
	tp.AddColumn("BF CP Doubling Ratio", 30);
	tp.AddColumn("Linear Logarithmic Colsest pair Time (ms)", 30);
	tp.AddColumn("LL CP Doubling Ratio", 30);
	//tp.AddColumn("Four Sum Brute-force Time (ms)", 30);

	tp.PrintHeader();

	std::vector<double> prevTimes(int(NUMBER_OF_ALGORITHMS), 0.0);
	int res = 0;
	double time = 0;
	for(auto&& fileName : vInputFiles) {

		std::string inputFile = fileName;
		std::string pathToInputFile = pathToInputDir + inputFile;
		std::fstream file( pathToInputFile , std::fstream::in);
		std::istream& input = file;

		std::vector<double> v = getInputVector(input);
		file.close();

		tp << fileName;

		time = testAlgo(bruteForceColsestPair, prevTimes, Algos::BRUTEFORCE_COLSEST_PAIR, v);
		tp << time << time / prevTimes[Algos::BRUTEFORCE_COLSEST_PAIR] ;
		prevTimes[Algos::BRUTEFORCE_COLSEST_PAIR] = time;

		time = testAlgo(linLogColsestPair, prevTimes, Algos::LINEAR_LOGARITHMIC_COLSEST_PAIR, v);
		tp << time << time / prevTimes[Algos::LINEAR_LOGARITHMIC_COLSEST_PAIR];
		prevTimes[Algos::LINEAR_LOGARITHMIC_COLSEST_PAIR] = time;

		// time = testAlgo(threeSumBinSearch, prevTimes, Algos::THREE_SUM_BINSEARCH, v);
		// tp << time << time / prevTimes[Algos::THREE_SUM_BINSEARCH] ;
		// prevTimes[Algos::THREE_SUM_BINSEARCH] = time;

		// time = testAlgo(threeSumLinear, prevTimes, Algos::THREE_SUM_LINEAR, v);
		// tp << time << time / prevTimes[Algos::THREE_SUM_LINEAR] ;
		// prevTimes[Algos::THREE_SUM_LINEAR] = time;

		//time = testAlgo(fourSumBruteforce, prevTimes, Algos::FOUR_SUM_BRUTEFORCE, v);
		//tp << time << time / prevTimes[Algos::FOUR_SUM_BRUTEFORCE] ;
		//prevTimes[Algos::FOUR_SUM_BRUTEFORCE] = time;
	}

	tp.PrintFooter();

	file_out.close();

	return 0;
}
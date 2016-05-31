#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

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

int twoSumBruteforce(const std::vector<int>& vecInts)
{
	int count = 0;

	for(unsigned i = 0; i < vecInts.size(); ++i) {
		for(unsigned j = i; j < vecInts.size(); ++j) {
			if(vecInts[j] + vecInts[i] == 0) {
				count++;
			}
		}
	}

	return count;
}

int main(int argc, char const *argv[]) {

	std::vector<std::string> vInputFiles;
	vInputFiles = { "1Kints.txt", "2Kints.txt", "4Kints.txt", "8Kints.txt", "16Kints.txt", "32Kints.txt" };
	std::string pathToInputDir("../testing/");

	std::ostream& output = std::cout;
	// std::ostream& output = file_out;

	output << std::setprecision(5);

	bprinter::TablePrinter tp(&output);
	tp.AddColumn("Input", 15);
	tp.AddColumn("Two Sum Brute-force Time (ms)", 30);
	tp.AddColumn("TS BF Doubling Ratio", 30);

	tp.PrintHeader();

	milliseconds prevTime(1);
	double pt = 0;

	Timer t;
	for(auto&& fileName : vInputFiles) {

		std::string inputFile = fileName;
		std::string pathToInputFile = pathToInputDir + inputFile;
		std::fstream file( pathToInputFile , std::fstream::in);
		std::istream& input = file;

		std::vector<int> v = getInputVector(input);

		//Timer t;
		t.Reset();
		int res =  twoSumBruteforce(v);
		// milliseconds time = t.Elapsed();
		double time = t.Elapsed().count();

		if(pt == 0) {
			pt = time;
		}

		tp << fileName << time << time / pt ;

		//output << time << "\n";

		pt = time;

		file.close();
	}

	tp.PrintFooter();

	return 0;
}
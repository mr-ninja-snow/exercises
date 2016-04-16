#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>

bool almost_equal(double x, double y, int ulp)
{
	return std::abs(x-y) <=   std::numeric_limits<double>::epsilon()
							* std::max(std::abs(x), std::abs(y))
							* ulp;
}

class SortEstimate
{
public:
	SortEstimate() = default;
	~SortEstimate() = default;

	double howMany(int c, int time, std::ostream& output)
	{
		double hi = std::numeric_limits<double>::max();
		double lo = 0;

		while (lo < hi) {
			double x = lo + (hi - lo) / 2;

			output << lo << " - " << x << " - " << hi << "\n";

			// c*n*lg(n) = c*n*(ln(n)/ln(2))
			double currentTime = c * x * (std::log(x) / std::log(2));

			output << "currentTime - " << currentTime << "; time - " << time << "\n";

			if (currentTime < time)
			{
				//lo = x + 1;
				double toAdd = std::abs(currentTime - time) / 100000;
				//int n = std::log(time) + 0.5;
				//toAdd = toAdd / (10 * n);
				toAdd = toAdd > 1 ? 1 : toAdd;
				lo = x + toAdd;
				output << "toAdd - " << toAdd <<  "\n";
			}
			else
			{
				hi = x;
			}

			if (almost_equal(lo, hi, 1000000))
			{
			 	break;
			}

			output << "\n\n";
		}

		return lo;
	}
};

int main(int argc, char const *argv[]) {
	std::fstream file_out( "out.txt" , std::fstream::out);
	// std::fstream file( "in.txt" , std::fstream::in);

	//std::string inputStr("1 8");  // found 4
	//std::string inputStr("2 16");  // found 4
	//std::string inputStr("37 12392342");  // found 23104.9993088173
	std::string inputStr("1 2000000000");  // found 76374950.8918325007
	std::istringstream iss(inputStr);

	//std::istream& input = std::cin;
	std::istream& input = iss;
	// std::istream& input = file;

	std::cout.precision(10);
	std::cout << std::fixed;
	std::ostream& output = std::cout;
	// std::ostream& output = file_out;

	double c;
	input >> c;

	double time;
	input >> time;

	SortEstimate se;

	double numberOfInts = se.howMany(c, time, output);
	output << "\n\nnumberOfInts = " << numberOfInts << "\n";

	file_out.close();
	return 0;
}

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>

// bool almost_equal(double x, double y, int ulp)
// {
// 	return std::abs(x-y) <=   std::numeric_limits<double>::epsilon()
// 							* std::max(std::abs(x), std::abs(y))
// 							* ulp;
// }

class Mortgage
{
public:
	Mortgage() = default;
	~Mortgage() = default;

	int simulatePayments(int monthlyPayment, int loan, int interest, int term, std::ostream& output)
	{
		int termInMonths = term * 12;

		for(unsigned i = 0; i < termInMonths; ++i) {
			loan -= monthlyPayment;
			loan = ceil(loan * (1 + interest / 12 / 100));
			output << " lest to pay - " << loan << "\n";
			if(loan < 0) {
				break;
			}
		}

		return loan;
	}

	int monthlyPayment(int loan, int interest, int term, std::ostream& output)
	{
		int hi = std::numeric_limits<int>::max();
		int lo = 0;

		while(lo < hi) {
			int x = lo + (hi - lo)/2;
			output << "\n\n";
			output << "lo - " << lo << "\n";
			output << "hi - " << hi << "\n";
			output << "current monthly Payment - " << x << "\n";

			int resultingLoan = simulatePayments(x, loan, interest, term, output);
			output << "resulting loan balance - " << resultingLoan << "\n";

			if(resultingLoan > 0) {
				lo = x + 1;
			} else {
				hi = x;
			}
		}

		return lo;
	}
};

int main(int argc, char const *argv[]) {
	std::fstream file_out( "out.txt" , std::fstream::out);
	// std::fstream file( "in.txt" , std::fstream::in);

	std::string inputStr("1000 50 1");  // found
	std::istringstream iss(inputStr);

	//std::istream& input = std::cin;
	std::istream& input = iss;
	// std::istream& input = file;

	std::cout.precision(10);
	std::cout << std::fixed;
	std::ostream& output = std::cout;
	// std::ostream& output = file_out;

	int laon;
	input >> laon;

	int interest;
	input >> interest;

	int term;
	input >> term;

	Mortgage m;

	int numberOfInts = m.monthlyPayment(laon, interest, term, output);
	output << "\n\nnumberOfInts = " << numberOfInts << "\n";

	file_out.close();
	return 0;
}

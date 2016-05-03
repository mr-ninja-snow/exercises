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

	unsigned int simulatePayments(unsigned int monthlyPayment, unsigned int loan, int interest, int term, std::ostream& output)
	{
		int termInMonths = term * 12;

		for(unsigned i = 0; i < termInMonths; ++i) {
			output << "subtract monthy payment - " << monthlyPayment << " from current dept " << loan << "\n";
			loan -= monthlyPayment;
			output << " = " << loan << "\n";
			unsigned int loanNew = ceil((double)loan * (1.0 + (double)interest / 12.0 / 100.0));
			output << " left to pay = " << loan << " * (1 + " << interest << " / 12 / 100) = " << loanNew << "\n";

			if(loanNew > loan + monthlyPayment + monthlyPayment) {
				loan = 0;
				break;
			}
			loan = loanNew;
		}

		return loan;
	}

	int monthlyPayment(int loan, int interest, int term, std::ostream& output)
	{
		unsigned int hi = 2000000000; //std::numeric_limits<unsigned int>::max();
		unsigned int lo = 0;

		while(lo < hi) {
			unsigned int x = lo + (hi - lo)/2;
			output << "\n\n";
			output << "lo - " << lo << "\n";
			output << "hi - " << hi << "\n";
			output << "current monthly Payment - " << x << "\n";
			//output << "                          " << 671844808 << "\n";

			unsigned int resultingLoan;

			if (x <= loan)
			{
				resultingLoan = simulatePayments(x, loan, interest, term, output);
				output << "resulting loan balance - " << resultingLoan << "\n";
			} else
			{
				resultingLoan = 0;
			}

			if(resultingLoan > 0) {
				lo = x + 1;
			} else {
				hi = x;
			}
		}

		return lo;
	}
};

// vstepano [comment]: the inputs for this problem are aimed at overflow control and detection and not about binary search
int main(int argc, char const *argv[]) {
	std::fstream file_out( "out.txt" , std::fstream::out);
	// std::fstream file( "in.txt" , std::fstream::in);

	//std::string inputStr("1000 50 1");  // found 86
	std::string inputStr("2000000000 6000 1");  // found 671844808
	//std::string inputStr("1000000 1000000 1000");  // found
	//std::string inputStr("1000000 129 30");  // found 10185
	//std::string inputStr("1999999999 1000000 1");  // found
	std::istringstream iss(inputStr);

	//std::istream& input = std::cin;
	std::istream& input = iss;
	// std::istream& input = file;

	std::cout.precision(10);
	std::cout << std::fixed;
	std::ostream& output = std::cout;
	// std::ostream& output = file_out;

	unsigned int loan;
	input >> loan;

	unsigned int interest;
	input >> interest;  // given the annual interest rate in tenths of a percent (WTF?)

	unsigned int term;
	input >> term;

	Mortgage m;

	interest /= 10;
	unsigned int paymentPerMonth = m.monthlyPayment(loan, interest, term, output);
	output << "\n\npayment Per Month = " << paymentPerMonth << "\n";

	file_out.close();
	return 0;
}

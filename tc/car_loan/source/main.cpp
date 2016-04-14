#include <iostream>
#include <fstream>
#include <sstream>

class AutoLoan
{
public:
	AutoLoan(double price, double payment, unsigned loanTerm) :
		m_price{ price },
		m_payment{ payment },
		m_loanTerm{ loanTerm }
	{}

	~AutoLoan() = default;

	double getAnnualInterst(std::ostream& output)
	{
		double hi = 101;
		double lo = 0;

		while (lo < hi) {
			double x = lo + (hi - lo) / 2;

			output << lo << " - " << x << " - " << hi << "\n";

			double monthlyIntrest = x / 12;

			double balance = m_price;
			for (unsigned i = 0; i < m_loanTerm; ++i) {
				output << balance << "\n";
				double currentIntrest = (balance * monthlyIntrest) / 100;

				balance += currentIntrest;
				balance -= m_payment;
			}

			output << balance << "\n";
			if (balance < 0) {
				lo = x + 1;
			}
			else {
				hi = x;
			}

			if (hi - lo < 1e-20) {
				break;
			}

			output << "\n\n";
		}

		return lo;
	}

private:
	double m_price;
	double m_payment;
	unsigned m_loanTerm;
};

using namespace std;

int main(int argc, char const *argv[]) {
	std::fstream file_out( "out.txt" , std::fstream::out);
	// std::fstream file( "in.txt" , std::fstream::in);

	//std::string inputStr("6800 100 68");  // our 9.64063; thier 9.56205462458368
	std::string inputStr("2000 510 4");
	std::istringstream iss(inputStr);

	//std::istream& input = std::cin;
	std::istream& input = iss;
	// std::istream& input = file;

	//std::ostream& output = std::cout;
	std::ostream& output = file_out;

	double price;
	input >> price;

	double payment;
	input >> payment;

	unsigned loanTerm;
	input >> loanTerm;

	AutoLoan al(price, payment, loanTerm);

	double anualIntrest = al.getAnnualInterst(output);
	output << "\n\nanual intrest = " << anualIntrest << "\n";

	file_out.close();
	return 0;
}
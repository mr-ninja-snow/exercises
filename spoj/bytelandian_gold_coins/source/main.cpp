#include <cmath>
#include <iostream>
#include <sstream>
#include <map>

class BytelandianMoneyConsultant
{
public:
	BytelandianMoneyConsultant(long int coinDenomination) :
		m_coinDenomination{ coinDenomination }
	{}

	~BytelandianMoneyConsultant() = default;

	long int coinToUSD(long int coinDenomination)
	{
		auto it = m_bytelandianCoinToUSD.find(coinDenomination);

		if (it != m_bytelandianCoinToUSD.end()) {
			return it->second;
		}
		else {
			long int divBy2Res = (long int)std::trunc(coinDenomination / 2);
			long int divBy3Res = (long int)std::trunc(coinDenomination / 3);
			long int divBy4Res = (long int)std::trunc(coinDenomination / 4);

			long int money = 0;
			if (coinDenomination != 0) {
				long int divBy2ResMoney = coinToUSD(divBy2Res);
				long int divBy3ResMoney = coinToUSD(divBy3Res);
				long int divBy4ResMoney = coinToUSD(divBy4Res);

				money = divBy2ResMoney + divBy3ResMoney + divBy4ResMoney;
				money = money > coinDenomination ? money : coinDenomination;
			}
			m_bytelandianCoinToUSD.insert(std::pair<long int, long int>(coinDenomination, money));

			return money;
		}
	}

	long int calculateUSD()
	{
		return coinToUSD(m_coinDenomination);
	}

private:
	long int                     m_coinDenomination;
	std::map<long int, long int> m_bytelandianCoinToUSD;
};

int main(int argc, char const *argv[]) {
	//std::string str("14 0 1 2 3 4 5 6 7 8 9 10 11 12 1000000000");

	std::string str("1 1000000000");
	std::istringstream iss(str);
	std::istream& input = iss;
	//std::istream& input = std::cin;
	std::ostream& output = std::cout;

	unsigned t;
	input >> t;

	for (unsigned i = 0; i < t; ++i) {
		unsigned coinDenomination;

		input >> coinDenomination;
		BytelandianMoneyConsultant consultant(coinDenomination);

		output << consultant.calculateUSD() << "\n";
	}
	return 0;
}
#include <cmath>
#include <iostream>
#include <sstream>
#include <map>

class BytelandianMoneyConsultant
{
public:
	BytelandianMoneyConsultant(unsigned int coinDenomination, std::ostream& output) :
		m_output{ output },
		m_coinDenomination{ coinDenomination }
	{}

	~BytelandianMoneyConsultant() = default;

	unsigned int coinToUSD(unsigned int coinDenomination)
	{
		auto it = m_bytelandianCoinToUSD.find(coinDenomination);

		if (it != m_bytelandianCoinToUSD.end()) {
			return it->second;
		}
		else {
			unsigned int divBy2Res = (unsigned int)std::trunc(coinDenomination / 2);
			unsigned int divBy3Res = (unsigned int)std::trunc(coinDenomination / 3);
			unsigned int divBy4Res = (unsigned int)std::trunc(coinDenomination / 4);

			unsigned int money = 0;
			if (coinDenomination != 0) {
				unsigned int divBy2ResMoney = coinToUSD(divBy2Res);
				unsigned int divBy3ResMoney = coinToUSD(divBy3Res);
				unsigned int divBy4ResMoney = coinToUSD(divBy4Res);

				money = divBy2ResMoney + divBy3ResMoney + divBy4ResMoney;
				money = money > coinDenomination ? money : coinDenomination;
			}
			m_bytelandianCoinToUSD.insert(std::pair<unsigned int, unsigned int>(coinDenomination, money));

			return money;
		}
	}

	unsigned int calculateUSD()
	{
		return coinToUSD(m_coinDenomination);
	}

private:
	std::ostream&                    m_output;
	unsigned int                     m_coinDenomination;
	std::map<unsigned int, unsigned int> m_bytelandianCoinToUSD;
};

int main(int argc, char const *argv[]) {

	std::istream& input = std::cin;
	std::ostream& output = std::cout;

	long long int coinDenomination;

	while (input >> coinDenomination)
	{
		BytelandianMoneyConsultant consultant(coinDenomination, output);

		output << consultant.calculateUSD() << "\n";
	}

	return 0;
}

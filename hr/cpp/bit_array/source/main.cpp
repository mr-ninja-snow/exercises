#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>

using namespace std;

class HashTableCounter
{
public:
	HashTableCounter() :
		m_bitArrya(HASH_TABLE_SIZE, 0),
		uniqueCounter(0)
	{
	}

	~HashTableCounter() = default;

	void insert(long long num)
	{
		long long index = num / (sizeof(long long) * 8);
		long long bitIndex = num - index*(sizeof(long long) * 8);

		if (m_bitArrya[index] & (long long)1 << bitIndex) {

		}
		else {
			m_bitArrya[index] = m_bitArrya[index] | (long long)1 << bitIndex;
			uniqueCounter++;
		}
	}

	int getUniqueCount() const { return uniqueCounter; }

private:

	enum
	{
		HASH_TABLE_SIZE = 2147483648 / (sizeof(long long) * 8)
	};
	std::vector<long long> m_bitArrya;
	int collitionCounter;
	int uniqueCounter;
};

int main(int argc, char const *argv[]) {

	std::istream& input = std::cin;

	std::ostream& output = std::cout;

	long long n;
	input >> n;
	long long s;
	input >> s;
	long long p;
	input >> p;
	long long q;
	input >> q;

	const long long maxNum = 2147483648; // 2^31

	long long prev = s % maxNum;

	HashTableCounter htc;

	htc.insert(prev);

	for (unsigned i = 1; i < n; ++i) {
		prev = (prev * p + q) % maxNum;

		htc.insert(prev);
	}

	output << htc.getUniqueCount() << "\n";

	return 0;
}
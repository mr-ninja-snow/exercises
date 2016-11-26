#include <iostream>
#include <fstream>
#include <sstream>

#include "quick_find.hpp"

class TestRunHelper {
private:
	std::vector<std::pair<unsigned int, unsigned int>> m_inputUnionArray;
	unsigned int m_unionArraySize;
public:
	TestRunHelper(std::string inputFile)
	{
		std::ifstream infile(inputFile);

		std::string line;
		std::getline(infile, line);
		std::istringstream iss(line);
		iss >> m_unionArraySize;

		while (std::getline(infile, line))
		{
			std::cout << "debug: line '" << line << "'\n";
			std::cout << "debug: size of m_inputUnionArray - " << m_inputUnionArray.size() << "\n";
			std::istringstream iss(line);
			int a, b;
			if (!(iss >> a >> b)) { break; } // error

			m_inputUnionArray.push_back(std::pair<unsigned int, unsigned int>(a, b));
		}
	}

	unsigned int getTestArraySize()
	{
		return m_unionArraySize;
	}

	const std::vector<std::pair<unsigned int, unsigned int>>& getUnionArrayRef() { return m_inputUnionArray; }
};

int main(int argc, char const *argv[]) {
	TestRunHelper trh("../testing/test1.txt");

	QuickFind qf(trh.getTestArraySize());

	for (const auto& p : trh.getUnionArrayRef())
	{
		std::cout << p.first << " - " << p.second << "\n";

		qf.doUnion(p.first, p.second);
		std::cout << "\n\n";
	}
	return 0;
}
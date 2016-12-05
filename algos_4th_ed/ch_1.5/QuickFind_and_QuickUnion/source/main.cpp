#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "quick_find.hpp"

class TestRunHelper {
private:
	using NodePair = std::pair<unsigned int, unsigned int>;
	std::vector<NodePair> m_inputUnionArray;
	std::vector<std::pair<NodePair, bool>> m_testCaseArray;
	unsigned int m_unionArraySize;
public:
	TestRunHelper(std::string inputFile, std::string testCaseFile)
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

		std::cout << "test case input\n";
		std::ifstream tcFile(testCaseFile);

		while (std::getline(tcFile, line))
		{
			std::cout << "debug: line '" << line << "'\n";

			std::smatch m;
			std::regex e ("(\\d*) - (\\d*): (\\w*)");
			std::regex_search (line, m, e);

			int nodeA = std::stoi(m[1]);
			int nodeB = std::stoi(m[2]);

			NodePair np = NodePair(nodeA, nodeB);

			bool res = std::string(m[3]) == std::string("true") ? true : false;
			m_testCaseArray.push_back(std::pair<NodePair, bool>(np, res));
		}
	}

	unsigned int getTestArraySize()
	{
		return m_unionArraySize;
	}

	const std::vector<NodePair>& getUnionArrayRef() { return m_inputUnionArray; }
	const std::vector<std::pair<NodePair, bool>>& getTestCaseArrayRef() { return m_testCaseArray; }
};

int main(int argc, char const *argv[]) {
	TestRunHelper trh("../testing/tinyUF.txt", "../testing/tinyUFTestCases.txt");

	QuickFind qf(trh.getTestArraySize());

	for (const auto& p : trh.getUnionArrayRef())
	{
		std::cout << p.first << " - " << p.second << "\n";

		qf.doUnion(p.first, p.second);
		std::cout << "\n\n";
	}

	for(const auto& testCase : trh.getTestCaseArrayRef()) {
		int nodeA = testCase.first.first;
		int nodeB = testCase.first.second;
		bool res = testCase.second;

		std::string TCRes = qf.connected(nodeA, nodeB) == res ? "Passed" : "Failed";

		std::cout << nodeA << " - " <<  nodeB << " connected? " << res << " (" << TCRes << ")\n";
	}

	return 0;
}
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

class FifteenPuzzle{
public :
	FifteenPuzzle(int m) :
		m_m(m ),
		m_evenCycleSolution(false )
	{};

	friend std::istream& operator>>( std::istream & input, FifteenPuzzle& p)
	{
		int mSqr = p.m_m * p. m_m;
		bool startingEven = false;
		bool currentSolutionType;

		p.m_distance = 0;
		for ( unsigned z = 0; z < p.m_m; ++z ) {
			currentSolutionType = startingEven;

			for ( unsigned y = 0; y < p.m_m; ++y ) {
				for ( unsigned x = 0; x < p.m_m; ++x ) {

					int index = mSqr * z + p. m_m * y + x + 1;
					int num;

					input >> num;
					p.m_puzzle. push_back(num );
					std::cout << currentSolutionType << ", ";

					if ( num == 0) {

						if (p.m_m * p.m_m * p. m_m != index) {
							p.m_distance++;
						}

						p.m_evenCycleSolution = currentSolutionType;
						p.m_puzzleMap. insert(std::pair< int, int>(p.m_m * p.m_m * p. m_m, index));
					}
					else {
						if (num != index) {
							p.m_distance++;
						}

						p.m_puzzleMap. insert(std::pair< int, int>(num , index));
					}

					currentSolutionType = ! currentSolutionType;
				}
			currentSolutionType = ! currentSolutionType;
			}
			startingEven = ! startingEven;
		}
		return input;
	}

	int getPermutationCycle (int missplacedNum, int nextNum , int numsInCycle)
	{
		numsInCycle++;
		//std::cout << "nextNum - " << nextNum << "; m_puzzleMap[nextNum] - " << m_puzzleMap[ nextNum] << "\n";
		int num = m_puzzleMap[nextNum ];

		if ( missplacedNum != num) {
			numsInCycle = getPermutationCycle( missplacedNum, num, numsInCycle );
		}

		m_puzzleMap[nextNum ] = nextNum;
		return numsInCycle;
	}

	enum res
	{
		NONE,
		ODD,
		EVEN
	};

	void debugPrint ()
	{
		int mSqr = m_m * m_m;
		for ( unsigned z = 0; z < m_m; ++z ) {
			for ( unsigned y = 0; y < m_m; ++y ) {
				for ( unsigned x = 0; x < m_m; ++x ) {
					std::cout << m_puzzle[mSqr * z + m_m * y + x];
				}
				std::cout << " | ";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
		std::cout << "\n";
	}

	std::string canBeSolved()
	{
		if (m_distance == 0) {
			return std::string( "Puzzle can be solved.\n" );
		}

		debugPrint();
		std::vector <int> permutationCycles;
		for ( auto& nPair : m_puzzleMap) {
			// std::cout << "nPair.first - " << nPair.first << "; nPair.second - " << nPair.second << "\n";
			if ( nPair.first != nPair.second ) {
				int numInCycle = getPermutationCycle(nPair.first, nPair.second , 0 );
				m_puzzleMap[nPair.first] = nPair.first;
				// std::cout << "numInCycle - " << numInCycle << "\n";
				permutationCycles.push_back (numInCycle);
			}
		}

		res currentSolutionType = NONE;
		bool isEven;
		for ( auto i : permutationCycles)
		{
			isEven = (i % 2 == 0);
			if ( currentSolutionType == NONE)
			{
				if ( isEven)
				{
					currentSolutionType = EVEN;
				}
				else
				{
					currentSolutionType = ODD;
				}
			}
			else
			{
				if ( isEven)
				{
					if ( currentSolutionType != EVEN)
					{
						currentSolutionType = ODD;
					}
				}
				else
				{
					if ( currentSolutionType == ODD)
					{
						currentSolutionType = EVEN;
					}
					else
					{
						currentSolutionType = ODD;
					}
				}
			}
		}

		if ( currentSolutionType == EVEN && m_evenCycleSolution || currentSolutionType == ODD && !m_evenCycleSolution )
		{
			return std::string( "Puzzle can be solved.\n" );
		}
		else
		{
			return std::string( "Puzzle is unsolvable.\n" );
		}
	}

private :
	std::map <int, int> m_puzzleMap;
	std::vector <int> m_puzzle;
	int m_m;
	int m_distance;
	bool m_evenCycleSolution;
};

int main( int argc , char const *argv[]) {
	std::fstream file_out( "ans.txt" , std::fstream::out);
	std::fstream file( "slovable.txt" , std::fstream::in);

	std::string input( "1 2 2 1 3 5 6 0 4 7" );
	std::istringstream iss( input);

	//std::istream& input = std::cin;
	std::istream& input = iss;
	// std::istream& input = file;

	std::ostream& output = std::cout;
	std::ostream& output = iss;

	int t;
	input >> t;

	for ( unsigned i = 0; i < t; ++i ) {
		int m;

		input >> m;
		FifteenPuzzle fp (m);

		input >> fp;

		std::cout << fp.canBeSolved () << "\n";
	}

	file.close();
	file_out.close();

	return 0;
}
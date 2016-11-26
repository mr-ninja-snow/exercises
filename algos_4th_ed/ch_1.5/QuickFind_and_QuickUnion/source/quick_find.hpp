#include <vector>

using T = int;

class QuickFind
{
private:
	std::vector<T> m_idArray;
public:
	QuickFind(unsigned int size);

	void doUnion(unsigned int nodeA, unsigned int nodeB);
	bool connected(unsigned int nodeA, unsigned int nodeB);

	inline bool rangeCheck(unsigned int nodeA, unsigned int nodeB);

	inline void debugPrint();
};

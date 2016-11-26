#include <iostream>

#include "quick_find.hpp"

QuickFind::QuickFind(unsigned int size) : m_idArray(size)
{
	unsigned int index = 0;
	for(auto&& i : m_idArray) {
		i = index;
		index++;
	}

	debugPrint();
}

void QuickFind::debugPrint()
{
	for(auto&& i : m_idArray) {
		std::cout << i << " ";
	}
	std::cout << "\n";
}

bool QuickFind::rangeCheck(unsigned int nodeA, unsigned int nodeB)
{
	if (nodeA >= m_idArray.size() && nodeB >= m_idArray.size())
	{
		std::cerr << "Error: node index out of range\n";
		return false;
	}
	return true;
}

void QuickFind::doUnion(unsigned int nodeA, unsigned int nodeB)
{
	if(!rangeCheck(nodeA, nodeB)) { return; }

	std::cout << "\nUnion node " << nodeA << " and node " << nodeB << "\n";
	std::cout << "Before:\n\t";
	debugPrint();

	unsigned int groupIdToChange = m_idArray[nodeA];
	unsigned int groupIdToChangeTo = m_idArray[nodeB];
	for(auto&& i : m_idArray) {
		if(i == groupIdToChange) {
			i = groupIdToChangeTo;
		}
	}

	std::cout << "After:\n\t";
	debugPrint();
}

bool QuickFind::connected(unsigned int nodeA, unsigned int nodeB)
{
	if(rangeCheck(nodeA, nodeB)) { return false; }

	if(m_idArray[nodeB] == m_idArray[nodeA]) {
		return true;
	}

	return false;
}
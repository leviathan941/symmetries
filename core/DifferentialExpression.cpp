/*
	Symmetries
	Copyright (C) 2014 Alexey Kuzin <amkuzink@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DifferentialExpression.h"
#include "DifferentialItem.h"
#include "Exceptions.h"

#include <boost/foreach.hpp>
#include <sstream>
#include <iostream>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////
DifferentialExpression::DifferentialExpression() : m_vecItems()
{
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression::DifferentialExpression(const DifferentialItem& item)
{
	pushItem(item);
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression::DifferentialExpression(const DifferentialExpression& otherExp)
{
	m_vecItems = otherExp.m_vecItems;
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression::~DifferentialExpression()
{
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
DifferentialExpression& DifferentialExpression::operator=(const DifferentialExpression& otherExp)
{
	if(&otherExp != this)
	{
		m_vecItems = otherExp.m_vecItems;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialExpression::operator==(const DifferentialExpression& otherExp) const
{
	if(m_vecItems.size() != otherExp.m_vecItems.size())
		return false;

	for(unsigned i = 0; i < m_vecItems.size(); ++i)
	{
		if(m_vecItems[i] != otherExp.m_vecItems[i])
			return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialExpression::operator!=(const DifferentialExpression& otherExp) const
{
	return !(*this == otherExp);
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression& DifferentialExpression::operator+=(const DifferentialExpression& otherExp)
{
	BOOST_FOREACH(const DifferentialItem& item, otherExp.m_vecItems)
	{
		int foundItem = isSimilarItemInExpression(item);
		if(foundItem >= 0)
		{
			setItemMultiplier((unsigned)foundItem,
				m_vecItems[foundItem].getMultiplier() + item.getMultiplier());
		}
		else
		{
			pushItem(item);
		}
	}

	findRemoveEmptyItems();
	return *this;
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression DifferentialExpression::operator+(const DifferentialExpression& otherExp) const
{
	DifferentialExpression tempExp(*this);
	tempExp += otherExp;
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression DifferentialExpression::operator-(const DifferentialExpression& otherExp) const
{
	DifferentialExpression tempExp(*this);
	BOOST_FOREACH(DifferentialItem item, otherExp.m_vecItems)
	{
		int foundItem = isSimilarItemInExpression(item);
		if(foundItem >= 0)
		{
			tempExp.setItemMultiplier((unsigned)foundItem,
				m_vecItems[foundItem].getMultiplier() - item.getMultiplier());
		}
		else
		{
			tempExp.pushItem(item);
			foundItem = tempExp.isSimilarItemInExpression(item);
			tempExp.setItemMultiplier((unsigned)foundItem, -item.getMultiplier());
		}
	}

	tempExp.findRemoveEmptyItems();
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression DifferentialExpression::operator*(const DifferentialExpression& otherExp) const
{
	DifferentialExpression tempExp = otherExp;
	DifferentialExpression outExp;
	BOOST_FOREACH(DifferentialItem& item, tempExp.m_vecItems)
	{
		BOOST_FOREACH(const DifferentialItem& otherItem, otherExp.m_vecItems)
		{
			outExp.m_vecItems.push_back(static_cast<DifferentialItem&>(item * otherItem));
		}
	}

	outExp.findRemoveEmptyItems();
	return outExp;
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression DifferentialExpression::operator/(const DifferentialExpression& otherExp) const
{
	//Placeholder
	std::cout << "It isn't implemented yet." << std::endl;
	return *this;
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression DifferentialExpression::operator*(const double nNumber) const
{
	DifferentialExpression tempExp(*this);
	BOOST_FOREACH(DifferentialItem& item, tempExp.m_vecItems)
	{
		item.setMultiplier(item.getMultiplier() * nNumber);
	}

	tempExp.findRemoveEmptyItems();
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
DifferentialExpression DifferentialExpression::operator/(const double nNumber) const
{
	DifferentialExpression tempExp(*this);
	BOOST_FOREACH(DifferentialItem& item, tempExp.m_vecItems)
	{
		item.setMultiplier(item.getMultiplier() / nNumber);
	}

	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
const DifferentialItem& DifferentialExpression::getItem(unsigned nItemPosition) const
{
	if (nItemPosition >= m_vecItems.size())
	{
		throw coreException("No such element");
	}
	return m_vecItems[nItemPosition];
}

///////////////////////////////////////////////////////////////////////////
void DifferentialExpression::setItemMultiplier(const unsigned nItemPosition,
	const double nNewMultiplier)
{
	m_vecItems[nItemPosition].setMultiplier(nNewMultiplier);
}

///////////////////////////////////////////////////////////////////////////
int DifferentialExpression::isSimilarItemInExpression(const DifferentialItem &item) const
{
	for(int i = 0; i < m_vecItems.size(); ++i)
	{
		if(item.isSubitemsEqual(m_vecItems[i]))
		{
			return i;
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////
void DifferentialExpression::pushItem(const DifferentialItem& newItem)
{
	m_vecItems.push_back(newItem);
}

///////////////////////////////////////////////////////////////////////////
void DifferentialExpression::eraseItem(const unsigned nPosition)
{
	m_vecItems.erase(m_vecItems.begin() + nPosition);
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialExpression::isEmpty()
{
	return (m_vecItems.empty() ? true : false);
}

///////////////////////////////////////////////////////////////////////////
void DifferentialExpression::clear()
{
	m_vecItems.clear();
}

///////////////////////////////////////////////////////////////////////////
std::string DifferentialExpression::toString() const
{
	std::stringstream strStream;

	for(int i = 0; i < m_vecItems.size(); ++i)
	{
		strStream << m_vecItems[i].toString();
		if(i != m_vecItems.size() - 1)
			strStream << " + ";
	}

	if (strStream.str().empty())
	{
		strStream << "0";
	}

	return strStream.str();
}

///////////////////////////////////////////////////////////////////////////
void DifferentialExpression::print()
{
	std::cout << toString();
}

///////////////////////////////////////////////////////////////////////////
void DifferentialExpression::findRemoveEmptyItems()
{
	auto pend = std::remove_if(m_vecItems.begin(), m_vecItems.end(),
		[](const DifferentialItem &item)
		{
			return (item.getMultiplier() == 0);
		});
	m_vecItems.erase(pend, m_vecItems.end());
}


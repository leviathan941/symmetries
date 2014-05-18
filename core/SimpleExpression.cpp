/*
	Symmetries
	Copyright (C) 2013, 2014 Alexey Kuzin <amkuzink@gmail.com>

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


#include "SimpleExpression.h"
#include "SimpleItem.h"

#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////
SimpleExpression::SimpleExpression() : m_vecItems()
{
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression::SimpleExpression(const SimpleItem& item)
{
	pushItem(item);
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression::SimpleExpression(const SimpleExpression& otherExp)
{
	m_vecItems = otherExp.m_vecItems;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression::~SimpleExpression()
{
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
SimpleExpression& SimpleExpression::operator=(const SimpleExpression& otherExp)
{
	if(&otherExp != this)
	{
		m_vecItems = otherExp.m_vecItems;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool SimpleExpression::operator==(const SimpleExpression& otherExp) const
{
	if(m_vecItems.size() != otherExp.m_vecItems.size())
		return false;

	for(unsigned i = 0; i < m_vecItems.size(); ++i)
	{
		if((Item&)m_vecItems[i] != (Item&)otherExp.m_vecItems[i])
			return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
bool SimpleExpression::operator!=(const SimpleExpression& otherExp) const
{
	return !(*this == otherExp);
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression SimpleExpression::operator+(const SimpleExpression& otherExp) const
{
	SimpleExpression tempExp(*this);
	BOOST_FOREACH(SimpleItem item, otherExp.m_vecItems)
	{
		int foundItem = tempExp.isSimilarItemInExpression(item);
		if(foundItem >= 0)
		{
			tempExp.setItemMultiplier((unsigned)foundItem,
				m_vecItems[foundItem].getMultiplier() + item.getMultiplier());
		}
		else
		{
			tempExp.pushItem(item);
		}
	}

	tempExp.findRemoveEmptyItems();
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression SimpleExpression::operator-(const SimpleExpression& otherExp) const
{
	SimpleExpression tempExp(*this);
	BOOST_FOREACH(SimpleItem item, otherExp.m_vecItems)
	{
		int foundItem = tempExp.isSimilarItemInExpression(item);
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
SimpleExpression& SimpleExpression::operator*=(const SimpleExpression& otherExp)
{
	SimpleExpression tempExp(*this);
	m_vecItems.clear();
	BOOST_FOREACH(SimpleItem& item, tempExp.m_vecItems)
	{
		BOOST_FOREACH(const SimpleItem& otherItem, otherExp.m_vecItems)
		{
			m_vecItems.push_back(static_cast<const SimpleItem&>(item * otherItem));
		}
	}

	findRemoveEmptyItems();
	return *this;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression SimpleExpression::operator*(const SimpleExpression& otherExp) const
{
	SimpleExpression tempExp(*this);
	tempExp *= otherExp;
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression& SimpleExpression::operator*=(const SimpleItem& sepItem)
{
	BOOST_FOREACH(SimpleItem& item, m_vecItems)
	{
		item *= sepItem;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression SimpleExpression::operator*(const SimpleItem& sepItem) const
{
	SimpleExpression tempExp(*this);
	tempExp *= sepItem;
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression& SimpleExpression::operator/=(const SimpleItem& sepItem)
{
	BOOST_FOREACH(SimpleItem& item, m_vecItems)
	{
		item /= sepItem;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression SimpleExpression::operator/(const SimpleItem& sepItem) const
{
	SimpleExpression tempExp(*this);
	tempExp /= sepItem;
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression& SimpleExpression::operator/=(const SimpleExpression& otherExp)
{
	//Placeholder
	std::cout << "It isn't implemented yet." << std::endl;
	findRemoveEmptyItems();
	return *this;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression SimpleExpression::operator/(const SimpleExpression& otherExp) const
{
	SimpleExpression tempExp(*this);
	tempExp /= otherExp;
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression SimpleExpression::operator*(const double nNumber) const
{
	SimpleExpression tempExp(*this);
	BOOST_FOREACH(SimpleItem& item, tempExp.m_vecItems)
	{
		item.setMultiplier(item.getMultiplier() * nNumber);
	}

	tempExp.findRemoveEmptyItems();
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression SimpleExpression::operator/(const double nNumber) const
{
	SimpleExpression tempExp(*this);
	BOOST_FOREACH(SimpleItem& item, tempExp.m_vecItems)
	{
		item.setMultiplier(item.getMultiplier() / nNumber);
	}

	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
SimpleItem SimpleExpression::getItem(const unsigned nItemPosition) const
{
	return m_vecItems[nItemPosition];
}

///////////////////////////////////////////////////////////////////////////
void SimpleExpression::setItemMultiplier(const unsigned nItemPosition, const double nNewMultiplier)
{
	m_vecItems[nItemPosition].setMultiplier(nNewMultiplier);
}

///////////////////////////////////////////////////////////////////////////
std::vector<SimpleItem> SimpleExpression::getVectorItems() const
{
	return m_vecItems;
}

///////////////////////////////////////////////////////////////////////////
int SimpleExpression::isSimilarItemInExpression(const SimpleItem& item) const
{
	for(int i = 0; i < m_vecItems.size(); ++i)
	{
		if(item.isSubitemsEqual((Item&)m_vecItems[i]))
		{
			return i;
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////
void SimpleExpression::pushItem(const SimpleItem& newItem)
{
	m_vecItems.push_back(newItem);
}

///////////////////////////////////////////////////////////////////////////
void SimpleExpression::eraseItem(const unsigned nPosition)
{
	m_vecItems.erase(m_vecItems.begin() + nPosition);
}

///////////////////////////////////////////////////////////////////////////
bool SimpleExpression::isEmpty()
{
	return (m_vecItems.empty() ? true : false);
}

///////////////////////////////////////////////////////////////////////////
void SimpleExpression::clear()
{
	m_vecItems.clear();
}

///////////////////////////////////////////////////////////////////////////
std::string SimpleExpression::toString()
{
	std::stringstream strStream;

	for(int i = 0; i < m_vecItems.size(); ++i)
	{
		strStream << m_vecItems[i].toString();
		if(i != m_vecItems.size() - 1)
			strStream << "+";
	}

	if (strStream.str().empty())
	{
		strStream << "0";
	}

	return strStream.str();
}

///////////////////////////////////////////////////////////////////////////
void SimpleExpression::print()
{
	std::cout << toString();
}

///////////////////////////////////////////////////////////////////////////
void SimpleExpression::findRemoveEmptyItems()
{
	auto pend = std::remove_if(m_vecItems.begin(), m_vecItems.end(),
		[](const SimpleItem &item)
		{
			return (item.getMultiplier() == 0);
		});
	m_vecItems.erase(pend, m_vecItems.end());
}

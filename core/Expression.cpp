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


#include "Expression.h"
#include "SimpleItem.h"

#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////
Expression::Expression() : m_vecItems()
{
}

///////////////////////////////////////////////////////////////////////////
Expression::Expression(const SimpleItem& item)
{
	pushItem(item);
}

///////////////////////////////////////////////////////////////////////////
Expression::Expression(const Expression& otherExp)
{
	m_vecItems = otherExp.m_vecItems;
}

///////////////////////////////////////////////////////////////////////////
Expression::~Expression()
{
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
Expression& Expression::operator=(const Expression& otherExp)
{
	if(&otherExp != this)
	{
		m_vecItems = otherExp.m_vecItems;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool Expression::operator==(const Expression& otherExp) const
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
bool Expression::operator!=(const Expression& otherExp) const
{
	return !(*this == otherExp);
}

///////////////////////////////////////////////////////////////////////////
Expression Expression::operator+(const Expression& otherExp) const
{
	Expression tempExp(*this);
	BOOST_FOREACH(SimpleItem item, otherExp.m_vecItems)
	{
		int foundItem = isSimilarItemInExpression(item);
		if(foundItem >= 0)
		{
			tempExp.setItemMultiplier((unsigned)isSimilarItemInExpression(item),
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
Expression Expression::operator-(const Expression& otherExp) const
{
	Expression tempExp(*this);
	BOOST_FOREACH(SimpleItem item, otherExp.m_vecItems)
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
Expression Expression::operator*(const Expression& otherExp) const
{
	Expression tempExp;
	BOOST_FOREACH(const SimpleItem& item, m_vecItems)
	{
		BOOST_FOREACH(SimpleItem otherItem, otherExp.m_vecItems)
		{
			tempExp.m_vecItems.push_back(item * otherItem);
		}
	}

	tempExp.findRemoveEmptyItems();
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
Expression Expression::operator/(const Expression& otherExp) const
{
	//Placeholder
	std::cout << "It isn't implemented yet." << std::endl;
	return *this;
}

///////////////////////////////////////////////////////////////////////////
Expression Expression::operator*(const double nNumber) const
{
	Expression tempExp(*this);
	BOOST_FOREACH(const SimpleItem& item, m_vecItems)
	{
		tempExp.setItemMultiplier((unsigned)isSimilarItemInExpression(item),
			item.getMultiplier() * nNumber);
	}

	tempExp.findRemoveEmptyItems();
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
Expression Expression::operator/(const double nNumber) const
{
	Expression tempExp(*this);
	BOOST_FOREACH(const SimpleItem& item, m_vecItems)
	{
		tempExp.setItemMultiplier((unsigned)isSimilarItemInExpression(item),
			item.getMultiplier() / nNumber);
	}

	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
SimpleItem Expression::getItem(const unsigned nItemPosition) const
{
	return m_vecItems[nItemPosition];
}

///////////////////////////////////////////////////////////////////////////
void Expression::setItemMultiplier(const unsigned nItemPosition, const double nNewMultiplier)
{
	m_vecItems[nItemPosition].setMultiplier(nNewMultiplier);
}

///////////////////////////////////////////////////////////////////////////
std::vector<SimpleItem> Expression::getVectorItems() const
{
	return m_vecItems;
}

///////////////////////////////////////////////////////////////////////////
int Expression::isSimilarItemInExpression(const SimpleItem& item) const
{
	for(int i = 0; i < m_vecItems.size(); ++i)
	{
		if(item.isVariablesEqual(m_vecItems[i]))
		{
			return i;
		}
	}
	return -1;
}

///////////////////////////////////////////////////////////////////////////
void Expression::pushItem(const SimpleItem& newItem)
{
	m_vecItems.push_back(newItem);
}

///////////////////////////////////////////////////////////////////////////
void Expression::eraseItem(const unsigned nPosition)
{
	m_vecItems.erase(m_vecItems.begin() + nPosition);
}

///////////////////////////////////////////////////////////////////////////
bool Expression::isEmpty()
{
	return (m_vecItems.empty() ? true : false);
}

///////////////////////////////////////////////////////////////////////////
void Expression::clear()
{
	m_vecItems.clear();
}

///////////////////////////////////////////////////////////////////////////
std::string Expression::toString()
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
void Expression::print()
{
	std::cout << toString();
}

///////////////////////////////////////////////////////////////////////////
void Expression::findRemoveEmptyItems()
{
	auto pend = std::remove_if(m_vecItems.begin(), m_vecItems.end(),
		[](const SimpleItem &item)
		{
			return (item.getMultiplier() == 0);
		});
	m_vecItems.erase(pend, m_vecItems.end());
}

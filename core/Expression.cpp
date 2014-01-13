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
#include "Item.h"

#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>

///////////////////////////////////////////////////////////////////////////
Expression::Expression() : m_vecItems()
{
}

///////////////////////////////////////////////////////////////////////////
Expression::Expression(const Item& item)
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
Expression Expression::operator+(const Expression& otherExp)
{
	//	otherExp.print();
	//	print();
	Expression tempExp(*this);
	BOOST_FOREACH(Item item, otherExp.m_vecItems)
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
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
Expression Expression::operator-(const Expression& otherExp)
{
	Expression tempExp(*this);
	BOOST_FOREACH(Item item, otherExp.m_vecItems)
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
			tempExp.setItemMultiplier((unsigned)foundItem, -item.getMultiplier());
		}
	}
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
Expression Expression::operator*(const Expression& otherExp)
{
	Expression tempExp;
	BOOST_FOREACH(Item& item, m_vecItems)
	{
		BOOST_FOREACH(Item otherItem, otherExp.m_vecItems)
		{
			tempExp.m_vecItems.push_back(item * otherItem);
		}
	}
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
Expression Expression::operator/(const Expression& otherExp)
{
	//Placeholder
	std::cout << "It isn't implemented yet." << std::endl;
	return *this;
}

///////////////////////////////////////////////////////////////////////////
Expression Expression::operator*(const double nNumber)
{
	Expression tempExp(*this);
	BOOST_FOREACH(Item& item, m_vecItems)
	{
		tempExp.setItemMultiplier((unsigned)isSimilarItemInExpression(item),
		nNumber * item.getMultiplier());
	}
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
Expression Expression::operator/(const double nNumber)
{
	Expression tempExp(*this);
	BOOST_FOREACH(Item& item, m_vecItems)
	{
		tempExp.setItemMultiplier((unsigned)isSimilarItemInExpression(item),
		nNumber / item.getMultiplier());
	}
	return tempExp;
}

///////////////////////////////////////////////////////////////////////////
Item Expression::getItem(const unsigned nItemPosition) const
{
	return m_vecItems[nItemPosition];
}

///////////////////////////////////////////////////////////////////////////
void Expression::setItemMultiplier(const unsigned nItemPosition, const double nNewMultiplier)
{
	m_vecItems[nItemPosition].setMultiplier(nNewMultiplier);
}

///////////////////////////////////////////////////////////////////////////
std::vector<Item> Expression::getVectorItems() const
{
	return m_vecItems;
}

///////////////////////////////////////////////////////////////////////////
int Expression::isSimilarItemInExpression(const Item& item) const
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
void Expression::pushItem(const Item& newItem)
{
	m_vecItems.push_back(newItem);
}

///////////////////////////////////////////////////////////////////////////
void Expression::eraseItem(const unsigned nPosition)
{
	m_vecItems.erase(m_vecItems.begin() + nPosition);
}

///////////////////////////////////////////////////////////////////////////
std::string Expression::toString()
{
	std::stringstream strStream;

	for(int i = 0; i < m_vecItems.size(); ++i)
	{
		strStream << m_vecItems[i].toString();
		if(i != m_vecItems.size() - 1)
			strStream << " + ";
	}

	return strStream.str();
}

///////////////////////////////////////////////////////////////////////////
void Expression::print()
{
	std::cout << toString();
}


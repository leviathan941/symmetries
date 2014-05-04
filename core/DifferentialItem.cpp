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


#include "DifferentialItem.h"
#include "Exceptions.h"

#include <boost/foreach.hpp>

///////////////////////////////////////////////////////////////////////////
DifferentialItem::DifferentialItem():
m_Differentials()
{
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem::DifferentialItem(const VariablesType &variables, double nMultiplier,
	std::string& sDiff, double nDiffPower)
{
	if (!sDiff.empty())
	{
		SimpleItem item(variables, nMultiplier);
		m_Differentials[sDiff] = std::pair<double, SimpleItem>(nDiffPower, item);
	}
	else
	{
		throw coreException("DifferentialItem::DifferentialItem."
			"Differential index cannot be empty.");
	}
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem::DifferentialItem(std::string& sVariable, double nPower, double nMultiplier,
	std::string &sDiff, double nDiffPower)
{
	if (!sVariable.empty() && !sDiff.empty())
	{
		SimpleItem item(sVariable, nPower, nMultiplier);
		m_Differentials[sDiff] = std::pair<double, SimpleItem>(nDiffPower, item);
	}
	else
	{
		throw coreException("DifferentialItem::DifferentialItem."
			"Differential index and variable cannot be empty.");
	}
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem::DifferentialItem(const DifferentialItem& item)
{
	m_Differentials = item.m_Differentials;
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem::~DifferentialItem()
{
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem& DifferentialItem::operator=(const DifferentialItem& otherItem)
{
	if (*this != otherItem)
	{
		m_Differentials = otherItem.m_Differentials;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialItem::operator==(const DifferentialItem& otherItem) const
{
	if (m_Differentials.size() != otherItem.m_Differentials.size()
		|| std::equal(m_Differentials.begin(), m_Differentials.end(),
		otherItem.m_Differentials.begin()))
	{
		return false;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialItem::operator!=(const DifferentialItem& otherItem) const
{
	return !(*this == otherItem);
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem DifferentialItem::operator*(const DifferentialItem& otherItem) const
{
	DifferentialItem tempItem(*this);
	try
	{
		BOOST_FOREACH(DifferentialMap::value_type subItem, otherItem.m_Differentials)
		{
			if (tempItem.m_Differentials.find(subItem.first) != tempItem.m_Differentials.end())
			{
				if (tempItem.m_Differentials[subItem.first].second == subItem.second.second)
				{
					// Adding mathematical powers
					tempItem.m_Differentials[subItem.first].first += subItem.second.first;
				}
				else
				{
					// Multiplying SimpleItems
					tempItem.m_Differentials[subItem.first].second *= subItem.second.second;
				}
			}
			else
			{
				tempItem.m_Differentials.insert(subItem);
			}
		}
	}
	CATCH_CORE

	return tempItem;
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem DifferentialItem::operator/(const DifferentialItem& otherItem) const
{
	DifferentialItem tempItem(*this);
	try
	{
		BOOST_FOREACH(DifferentialMap::value_type subItem, otherItem.m_Differentials)
		{
			if (tempItem.m_Differentials.find(subItem.first) != tempItem.m_Differentials.end())
			{
				if (tempItem.m_Differentials[subItem.first].second == subItem.second.second)
				{
					// Subtraction of mathematical powers
					tempItem.m_Differentials[subItem.first].first -= subItem.second.first;
				}
				else
				{
					// Dividing SimpleItems
					tempItem.m_Differentials[subItem.first].second /= subItem.second.second;
				}
			}
			else
			{
				subItem.second.first *= -1;
				tempItem.m_Differentials.insert(subItem);
			}
		}
	}
	CATCH_CORE

	return tempItem;
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialItem::isDifferentialsEqual(const DifferentialItem& otherItem) const
{
	if (m_Differentials.size() != otherItem.m_Differentials.size())
	{
		return false;
	}

	BOOST_FOREACH(DifferentialMap::value_type subItem, otherItem.m_Differentials)
	{
		if (m_Differentials.find(subItem.first) == m_Differentials.end())
		{
			return false;
		}
	}

	return true;
}

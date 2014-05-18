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
#include <sstream>

///////////////////////////////////////////////////////////////////////////
DifferentialItem::DifferentialItem():
m_Differentials(), m_nDiffMultiplier(0)
{
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem::DifferentialItem(const VariablesType &variables, double nMultiplier,
	std::string sDiff, double nDiffPower, double nDiffMultiplier)
{
	if (!sDiff.empty())
	{
		SimpleItem item(variables, nMultiplier);
		m_Differentials[sDiff] = std::pair<double, SimpleItem>(nDiffPower, item);
		m_nDiffMultiplier = nDiffMultiplier;
	}
	else
	{
		throw coreException("DifferentialItem::DifferentialItem."
			"Differential index cannot be empty.");
	}
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem::DifferentialItem(std::string sVariable, double nPower, double nMultiplier,
	std::string sDiff, double nDiffPower, double nDiffMultiplier)
{
	if (!sVariable.empty() && !sDiff.empty())
	{
		SimpleItem item(sVariable, nPower, nMultiplier);
		m_Differentials[sDiff] = std::pair<double, SimpleItem>(nDiffPower, item);
		m_nDiffMultiplier = nDiffMultiplier;
	}
	else
	{
		throw coreException("DifferentialItem::DifferentialItem."
			"Differential index and variable cannot be empty.");
	}
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem::DifferentialItem(const SimpleItem& simple, std::string sDiff, double nDiffPower,
	double nDiffMultiplier)
{
	if (!sDiff.empty())
	{
		m_Differentials[sDiff] = std::pair<double, SimpleItem>(nDiffPower, simple);
		m_nDiffMultiplier = nDiffMultiplier;
	}
	else
	{
		throw coreException("DifferentialItem::DifferentialItem."
			"Differential index cannot be empty.");
	}
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem::DifferentialItem(const DifferentialItem& item)
{
	m_Differentials = item.m_Differentials;
	m_nDiffMultiplier = item.m_nDiffMultiplier;
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem::~DifferentialItem()
{
}

///////////////////////////////////////////////////////////////////////////
Item& DifferentialItem::operator=(const Item& otherItem)
{
	if (this != &otherItem)
	{
		const DifferentialItem& diffItem = static_cast<const DifferentialItem&> (otherItem);
		m_Differentials = diffItem.m_Differentials;
		m_nDiffMultiplier = diffItem.m_nDiffMultiplier;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
DifferentialItem& DifferentialItem::operator=(const DifferentialItem& otherItem)
{
	if (this != &otherItem)
	{
		m_Differentials = otherItem.m_Differentials;
		m_nDiffMultiplier = otherItem.m_nDiffMultiplier;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialItem::operator==(const Item& otherItem) const
{
	const DifferentialItem& diffItem = static_cast<const DifferentialItem&> (otherItem);
	if (m_Differentials.size() != diffItem.m_Differentials.size()
		|| std::equal(m_Differentials.begin(), m_Differentials.end(),
			diffItem.m_Differentials.begin()))
	{
		return false;
	}

	if (m_nDiffMultiplier != diffItem.m_nDiffMultiplier)
	{
		return false;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialItem::operator!=(const Item& otherItem) const
{
	return !(*this == otherItem);
}

///////////////////////////////////////////////////////////////////////////
Item& DifferentialItem::operator*=(const Item& otherItem)
{
	const DifferentialItem& diffItem = static_cast<const DifferentialItem&> (otherItem);
	try
	{
		BOOST_FOREACH(DifferentialMap::value_type subItem, diffItem.m_Differentials)
		{
			if (m_Differentials.find(subItem.first) != m_Differentials.end())
			{
				if (m_Differentials[subItem.first].second == subItem.second.second)
				{
					// Adding mathematical powers
					m_Differentials[subItem.first].first += subItem.second.first;
				}
				else
				{
					// Multiplying SimpleItems
					m_Differentials[subItem.first].second *= subItem.second.second;
				}
			}
			else
			{
				m_Differentials.insert(subItem);
			}
		}
	}
	CATCH_CORE

	m_nDiffMultiplier *= diffItem.m_nDiffMultiplier;
	if (m_nDiffMultiplier == 0)
	{
		m_Differentials.clear();
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////
Item& DifferentialItem::operator*(const Item& otherItem)
{
	return (*this) *= otherItem;
}

///////////////////////////////////////////////////////////////////////////
Item& DifferentialItem::operator/=(const Item& otherItem)
{
	const DifferentialItem& diffItem = static_cast<const DifferentialItem&> (otherItem);
	if (diffItem.m_nDiffMultiplier == 0)
	{
		std::cerr << "Error. Division by zero." << std::endl;
		return *this;
	}
	else
	{
		try
		{
			BOOST_FOREACH(DifferentialMap::value_type subItem, diffItem.m_Differentials)
			{
				if (m_Differentials.find(subItem.first) != m_Differentials.end())
				{
					if (m_Differentials[subItem.first].second == subItem.second.second)
					{
						// Subtraction of mathematical powers
						m_Differentials[subItem.first].first -= subItem.second.first;
					}
					else
					{
						// Dividing SimpleItems
						m_Differentials[subItem.first].second /= subItem.second.second;
					}
				}
				else
				{
					subItem.second.first *= -1;
					m_Differentials.insert(subItem);
				}
			}
		}
		CATCH_CORE
	}

	m_nDiffMultiplier /= diffItem.m_nDiffMultiplier;
	if (m_nDiffMultiplier == 0)
	{
		m_Differentials.clear();
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////
Item& DifferentialItem::operator/(const Item& otherItem)
{
	return (*this) /= otherItem;
}

///////////////////////////////////////////////////////////////////////////
double DifferentialItem::getMultiplier() const
{
	return m_nDiffMultiplier;
}

///////////////////////////////////////////////////////////////////////////
void DifferentialItem::setMultiplier(const double newMultiplier)
{
	BOOST_FOREACH(DifferentialMap::value_type subItem, m_Differentials)
	{
		subItem.second.second.setMultiplier(1.0);
	}

	m_nDiffMultiplier = newMultiplier;
	if (m_nDiffMultiplier == 0.0)
	{
		m_Differentials.clear();
	}
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialItem::isSubitemsEqual(const Item& otherItem) const
{
	const DifferentialItem& diffItem = static_cast<const DifferentialItem&> (otherItem);
	if (m_Differentials.size() != diffItem.m_Differentials.size())
	{
		return false;
	}

	BOOST_FOREACH(DifferentialMap::value_type subItem, diffItem.m_Differentials)
	{
		DifferentialMap::const_iterator iter = m_Differentials.find(subItem.first);
		if (iter == m_Differentials.end())
		{
			return false;
		}
		else
		{
			if (iter->second.first != subItem.second.first
				|| !iter->second.second.isSubitemsEqual(subItem.second.second))
			{
				return false;
			}
		}
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////
std::string DifferentialItem::toString() const
{
	std::stringstream strStream;

	if (m_nDiffMultiplier == -1.0)
	{
		strStream << "-";
	} else if (m_nDiffMultiplier == 1.0)
	{
		if (m_Differentials.empty())
			strStream << m_nDiffMultiplier << "*";
	} else
	{
		strStream << m_nDiffMultiplier << "*";
	}

	BOOST_FOREACH(DifferentialMap::value_type subItem, m_Differentials)
	{
		if(!subItem.first.empty())
			strStream << "d_" << subItem.first;

		if(subItem.second.first != 1.0)
			strStream << "^" << subItem.second.first;

		strStream << "( " << subItem.second.second.toString() << " )";
	}

	return strStream.str();
}

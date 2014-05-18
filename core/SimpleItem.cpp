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

#include "SimpleItem.h"
#include "Exceptions.h"

#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>

///////////////////////////////////////////////////////////////////////////
SimpleItem::SimpleItem():
m_Variables(), m_nMultiplier(0)
{
}

///////////////////////////////////////////////////////////////////////////
SimpleItem::SimpleItem(const VariablesType &variable, double nMultiplier)
{
	try
	{
		BOOST_FOREACH(VariablesType::value_type mapElement, variable)
		{
			m_Variables.insert(mapElement);
		}
	}
	CATCH_CORE

	m_nMultiplier = nMultiplier;
}

///////////////////////////////////////////////////////////////////////////
SimpleItem::SimpleItem(std::string strVar, double nVarPower, double nMultiplier)
{
	if(!strVar.empty())
		m_Variables[strVar] = nVarPower;

	m_nMultiplier = nMultiplier;
}

///////////////////////////////////////////////////////////////////////////
SimpleItem::SimpleItem(const SimpleItem& otherItem)
{
	m_Variables = otherItem.m_Variables;
	m_nMultiplier = otherItem.m_nMultiplier;
}

///////////////////////////////////////////////////////////////////////////
SimpleItem::~SimpleItem()
{
}

///////////////////////////////////////////////////////////////////////////
Item& SimpleItem::operator=(const Item& otherItem)
{
	if(&otherItem != this)
	{
		const SimpleItem& simple = static_cast<const SimpleItem&>(otherItem);
		m_Variables = simple.m_Variables;
		m_nMultiplier = simple.m_nMultiplier;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
SimpleItem& SimpleItem::operator=(const SimpleItem& otherItem)
{
	if(&otherItem != this)
	{
		m_Variables = otherItem.m_Variables;
		m_nMultiplier = otherItem.m_nMultiplier;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool SimpleItem::operator==(const Item& otherItem) const
{
	if((m_nMultiplier != otherItem.getMultiplier()) || !isSubitemsEqual(otherItem))
	{
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
bool SimpleItem::operator!=(const Item& otherItem) const
{
	if((m_nMultiplier != otherItem.getMultiplier()) || !isSubitemsEqual(otherItem))
	{
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
Item& SimpleItem::operator*=(const Item& otherItem)
{
	const SimpleItem& simple = static_cast<const SimpleItem&>(otherItem);
	try
	{
		BOOST_FOREACH(VariablesType::value_type mapElement, simple.m_Variables.getInternalMap())
		{
			if(m_Variables.find(mapElement.first) != m_Variables.end())
			{
				m_Variables[mapElement.first] += mapElement.second;
				if(m_Variables[mapElement.first] == 0)
				{
					m_Variables.erase(mapElement.first);
				}
			}
			else
			{
				m_Variables.insert(mapElement);
			}
		}
	}
	CATCH_CORE

	m_nMultiplier *= simple.m_nMultiplier;
	if(m_nMultiplier == 0)
	{
		m_Variables.clear();
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////
Item& SimpleItem::operator*(const Item& otherItem)
{
	return (*this) *= otherItem;
}

///////////////////////////////////////////////////////////////////////////
Item& SimpleItem::operator/=(const Item& otherItem)
{
	const SimpleItem& simple = static_cast<const SimpleItem&>(otherItem);
	if(simple.m_nMultiplier == 0)
	{
		std::cerr << "Error. Division by zero." << std::endl;
		return *this;
	}
	else
	{
		try
		{
			BOOST_FOREACH(VariablesType::value_type mapElement, simple.m_Variables.getInternalMap())
			{
				if(m_Variables.find(mapElement.first) != m_Variables.end())
				{
					m_Variables[mapElement.first] -= mapElement.second;
					if(m_Variables[mapElement.first] == 0)
					{
						m_Variables.erase(mapElement.first);
					}
				}
				else
				{
					VariablesType::value_type tempElement = mapElement;
					tempElement.second *= -1;
					m_Variables.insert(tempElement);
				}

			}
		}
		CATCH_CORE

		m_nMultiplier /= simple.m_nMultiplier;
		if(m_nMultiplier == 0)
		{
			m_Variables.clear();
		}
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////
Item& SimpleItem::operator/(const Item& otherItem)
{
	return (*this) /= otherItem;
}

///////////////////////////////////////////////////////////////////////////
double SimpleItem::getMultiplier() const
{
	return m_nMultiplier;
}

///////////////////////////////////////////////////////////////////////////
void SimpleItem::setMultiplier(const double newMultiplier)
{
	m_nMultiplier = newMultiplier;
	if(m_nMultiplier == 0.0)
	{
		m_Variables.clear();
	}
}

///////////////////////////////////////////////////////////////////////////
VariablesType SimpleItem::getVariables() const
{
	return m_Variables.getInternalMap();
}

///////////////////////////////////////////////////////////////////////////
void SimpleItem::setVariablePower(const std::string sVariable, const double nPower)
{
	if(m_Variables.find(sVariable) != m_Variables.end())
	{
		if(nPower == 0.0)
		{
			m_Variables.erase(sVariable);
			return;
		}
		m_Variables[sVariable] = nPower;
	}
	else
	{
		std::cerr << "No such variable in the item." << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////
bool SimpleItem::isSubitemsEqual(const Item& otherItem) const
{
	const SimpleItem& simple = static_cast<const SimpleItem&>(otherItem);
	if(m_Variables.size() != simple.m_Variables.size())
	{
		return false;
	}

	for(VariablesType::const_iterator i = m_Variables.begin();
		i != m_Variables.end(); ++i)
	{
		if (simple.m_Variables.find(i->first) == simple.m_Variables.end()
				|| i->second != simple.m_Variables.at(i->first))
			return false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////
std::string SimpleItem::toString() const
{
	std::stringstream strStream;

	if (m_nMultiplier == -1.0)
	{
		strStream << "-";
	} else if (m_nMultiplier == 1.0)
	{
		if (m_Variables.empty())
			strStream << m_nMultiplier;
	} else
	{
		strStream << m_nMultiplier;
	}

	for(VariablesType::const_iterator iter = m_Variables.begin();
		iter != m_Variables.end(); ++iter)
	{
		if(!iter->first.empty())
			strStream << iter->first;

		if(iter->second != 1.0)
			strStream << "^" << iter->second;
	}

	return strStream.str();
}

///////////////////////////////////////////////////////////////////////////
void SimpleItem::print()
{
	std::cout << toString();
}


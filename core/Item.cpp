/*
	Symmetries
	Copyright (C) 2013  Alexey Kuzin <amkuzink@gmail.com>

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

#include "Item.h"
#include "Exceptions.h"

#include <iostream>
#include <sstream>
#include <boost/foreach.hpp>

///////////////////////////////////////////////////////////////////////////
Item::Item():
m_Variables(), m_nMultiplier(0)
{
}

///////////////////////////////////////////////////////////////////////////
Item::Item(VariablesType& variable, double nMultiplier)
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
Item::Item(std::string strVar, double nVarPower, double nMultiplier)
{
	try
	{
		m_Variables[strVar] = nVarPower;
	}
	CATCH_CORE

	m_nMultiplier = nMultiplier;
}

///////////////////////////////////////////////////////////////////////////
Item::Item(const Item& otherItem)
{
	m_Variables = otherItem.m_Variables;
	m_nMultiplier = otherItem.m_nMultiplier;
}

///////////////////////////////////////////////////////////////////////////
Item::~Item()
{
}

///////////////////////////////////////////////////////////////////////////
Item& Item::operator=(const Item& otherItem)
{
	if(&otherItem != this)
	{
		m_Variables = otherItem.m_Variables;
		m_nMultiplier = otherItem.m_nMultiplier;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool Item::operator==(const Item& otherItem) const
{
	if((m_nMultiplier != otherItem.getMultiplier()) || !isVariablesEqual(otherItem))
	{
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
bool Item::operator!=(const Item& otherItem) const
{
	if((m_nMultiplier != otherItem.getMultiplier()) || !isVariablesEqual(otherItem))
	{
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
Item Item::operator*(const Item& otherItem)
{
	Item tempItem(*this);
	try
	{
		BOOST_FOREACH(VariablesType::value_type mapElement, otherItem.m_Variables.getInternalMap())
		{
			if(tempItem.m_Variables.find(mapElement.first) != tempItem.m_Variables.end())
			{
				tempItem.m_Variables[mapElement.first] += mapElement.second;
				if(tempItem.m_Variables[mapElement.first] == 0)
				{
					tempItem.m_Variables.erase(mapElement.first);
				}
			}
			else
			{
				tempItem.m_Variables.insert(mapElement);
			}
		}
	}
	CATCH_CORE

	tempItem.m_nMultiplier *= otherItem.m_nMultiplier;
	if(tempItem.m_nMultiplier == 0)
	{
		tempItem.m_Variables.clear();
	}
	
	return tempItem;
}

///////////////////////////////////////////////////////////////////////////
Item Item::operator/(const Item& otherItem)
{
	Item tempItem(*this);
	if(otherItem.m_nMultiplier == 0)
	{
		std::cerr << "Error. Division by zero." << std::endl;
	}
	else
	{
		try
		{
			BOOST_FOREACH(VariablesType::value_type mapElement, otherItem.m_Variables.getInternalMap())
			{
				if(tempItem.m_Variables.find(mapElement.first) != tempItem.m_Variables.end())
				{
					tempItem.m_Variables[mapElement.first] -= mapElement.second;
					if(tempItem.m_Variables[mapElement.first] == 0)
					{
						tempItem.m_Variables.erase(mapElement.first);
					}
				}
				else
				{
					tempItem.m_Variables.insert(mapElement);
				}

			}
		}
		CATCH_CORE
		
		tempItem.m_nMultiplier /= otherItem.m_nMultiplier;
		if(tempItem.m_nMultiplier == 0)
		{
			tempItem.m_Variables.clear();
		}
	}
	
	return tempItem;
}

///////////////////////////////////////////////////////////////////////////
double Item::getMultiplier() const
{
	return m_nMultiplier;
}

///////////////////////////////////////////////////////////////////////////
void Item::setMultiplier(const double newMultiplier)
{
	m_nMultiplier = newMultiplier;
	if(m_nMultiplier == 0.0)
	{
		m_Variables.clear();
	}
}

///////////////////////////////////////////////////////////////////////////
VariablesType Item::getVariables() const
{
	return m_Variables.getInternalMap();
}

///////////////////////////////////////////////////////////////////////////
void Item::setVariablePower(const std::string sVariable, const double nPower)
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
bool Item::isVariablesEqual(const Item& otherItem) const
{
	//	std::cout << "m_Variables.size() = " << m_Variables.size() <<
	//		", otherItem.getVariables().size() = " << otherItem.getVariables().size() << std::endl;
	if(m_Variables.size() != otherItem.m_Variables.size())
	{
		return false;
	}

	for(VariablesType::const_iterator i = m_Variables.begin();
		i != m_Variables.end(); ++i)
	{
		for(VariablesType::const_iterator j = otherItem.m_Variables.begin();
			j != otherItem.m_Variables.end(); ++j)
		{
			if((i->first != j->first) || (i->second != j->second))
			{
				return false;
			}
		}
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////
std::string Item::toString()
{
	std::stringstream strStream;

	strStream << m_nMultiplier;

	for(VariablesType::const_iterator iter = m_Variables.begin(); iter != m_Variables.end(); ++iter)
	{
		if(!iter->first.empty())
			strStream << iter->first;

		if(iter->second != 1.0)
			strStream << "^" << iter->second;
	}

	return strStream.str();
}

///////////////////////////////////////////////////////////////////////////
void Item::print()
{
	std::cout << toString();
}


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

#include "VariablesMap.h"
#include "Exceptions.h"

CVariablesMap::CVariablesMap()
{
}

///////////////////////////////////////////////////////////////////////////
CVariablesMap::CVariablesMap(std::string &strVariables, double nPower)
{
	if(strVariables.empty())
		throw coreException("CVariablesMap: Empty strVariables was passed.");

	std::pair<std::string, double> element(strVariables, nPower);
	m_mapInternal.insert(element);
}

///////////////////////////////////////////////////////////////////////////
CVariablesMap::CVariablesMap(const CVariablesMap &newVariablesMap)
{
	m_mapInternal = newVariablesMap.m_mapInternal;
}

///////////////////////////////////////////////////////////////////////////
CVariablesMap::~CVariablesMap()
{
}

///////////////////////////////////////////////////////////////////////////
CVariablesMap& CVariablesMap::operator=(const CVariablesMap& newVariablesMap)
{
	if(this != &newVariablesMap)
	{
		m_mapInternal = newVariablesMap.m_mapInternal;
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////
double& CVariablesMap::operator[](const std::string& strVariables)
{
	if(strVariables.empty())
		throw coreException("CVariablesMap::operator[]: Empty strVariables was passed.");

	return m_mapInternal[strVariables];
}

///////////////////////////////////////////////////////////////////////////
const VariablesType& CVariablesMap::getInternalMap() const
{
	return m_mapInternal;
}

///////////////////////////////////////////////////////////////////////////
VariablesType::iterator CVariablesMap::find(const std::string& key)
{
	if(key.empty())
		throw coreException("CVariablesMap::find: Empty key was passed.");
	return m_mapInternal.find(key);
}

///////////////////////////////////////////////////////////////////////////
VariablesType::const_iterator CVariablesMap::begin() const
{
	return m_mapInternal.begin();
}

///////////////////////////////////////////////////////////////////////////
VariablesType::const_iterator CVariablesMap::end() const
{
	return m_mapInternal.end();
}
///////////////////////////////////////////////////////////////////////////
VariablesType::iterator CVariablesMap::end()
{
	return m_mapInternal.end();
}

///////////////////////////////////////////////////////////////////////////
bool CVariablesMap::empty()
{
	return m_mapInternal.empty();
}

///////////////////////////////////////////////////////////////////////////
std::pair<VariablesType::iterator, bool>
	CVariablesMap::insert(const std::pair<std::string, double>& mapElement)
{
	if(mapElement.first.empty())
		throw coreException("CVariablesMap::insert: Empty 'first' in pair was passed.");

	return m_mapInternal.insert(mapElement);
}

///////////////////////////////////////////////////////////////////////////
void CVariablesMap::erase(VariablesType::iterator position)
{
	m_mapInternal.erase(position);
}

///////////////////////////////////////////////////////////////////////////
void CVariablesMap::erase(const std::string& key)
{
	m_mapInternal.erase(key);
}

///////////////////////////////////////////////////////////////////////////
void CVariablesMap::clear()
{
	m_mapInternal.clear();
}

///////////////////////////////////////////////////////////////////////////
VariablesType::size_type CVariablesMap::size() const
{
	return m_mapInternal.size();
}

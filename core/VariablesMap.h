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

#ifndef VARIABLES_MAP_H
#define VARIABLES_MAP_H

#include <map>
#include <string>

typedef std::map<std::string, double> VariablesType;

class CVariablesMap
{
public:
	CVariablesMap();
	CVariablesMap(std::string& strVariables, double nPower);
	CVariablesMap(const CVariablesMap& newVariablesMap);
	virtual ~CVariablesMap();

	CVariablesMap& operator=(const CVariablesMap& newVariablesMap);
	double& operator[](const std::string& strVariables);

	const VariablesType& getInternalMap() const;
	VariablesType::iterator find(const std::string& key);
	VariablesType::const_iterator begin() const;
	VariablesType::iterator end();
	VariablesType::const_iterator end() const;
	bool empty();
	std::pair<VariablesType::iterator, bool> insert(const std::pair<std::string, double>& mapElement);
	void erase(VariablesType::iterator position);
	void erase(const std::string& key);
	void clear();
	VariablesType::size_type size() const;
private:
	VariablesType m_mapInternal;
};

#endif // VARIABLES_MAP_H

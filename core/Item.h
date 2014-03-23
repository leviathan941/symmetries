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

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <map>
#include "VariablesMap.h"

class Item
{
public:
	Item();
	Item(VariablesType& variable, double nMultiplier);
	Item(std::string strVar, double nVarPower, double nMultiplier);
	Item(const Item& otherItem);
	virtual ~Item();
	virtual Item& operator=(const Item& otherItem);
	virtual bool operator==(const Item& otherItem) const;
	virtual bool operator!=(const Item& otherItem) const;

	virtual Item operator*(const Item& otherItem) const;
	virtual Item operator/(const Item& otherItem) const;

	double getMultiplier() const;
	void setMultiplier(const double newMultiplier);

	VariablesType getVariables() const;
	void setVariablePower(const std::string sVariable, const double nPower);

	virtual bool isVariablesEqual(const Item& otherItem) const;

	std::string toString();

	void print();
private:
	CVariablesMap m_Variables;
	double m_nMultiplier;
};

#endif // ITEM_H

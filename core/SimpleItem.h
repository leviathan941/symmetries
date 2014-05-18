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

#ifndef SIMPLE_ITEM_H
#define SIMPLE_ITEM_H

#include "VariablesMap.h"
#include "Item.h"

#include <string>
#include <map>

class SimpleItem : public Item
{
public:
	SimpleItem();
	SimpleItem(const VariablesType& variable, double nMultiplier);
	SimpleItem(std::string strVar, double nVarPower, double nMultiplier);
	SimpleItem(const SimpleItem& otherItem);
	virtual ~SimpleItem();
	virtual Item& operator=(const Item& otherItem);
	virtual SimpleItem& operator=(const SimpleItem& otherItem);
	virtual bool operator==(const Item& otherItem) const;
	virtual bool operator!=(const Item& otherItem) const;

	virtual Item& operator*=(const Item& otherItem);
	virtual Item& operator*(const Item& otherItem);
	virtual Item& operator/=(const Item& otherItem);
	virtual Item& operator/(const Item& otherItem);

	virtual double getMultiplier() const;
	virtual void setMultiplier(const double newMultiplier);

	VariablesType getVariables() const;
	void setVariablePower(const std::string sVariable, const double nPower);

	virtual bool isSubitemsEqual(const Item& otherItem) const;

	std::string toString() const;

	void print();
protected:
	CVariablesMap m_Variables;
	double m_nMultiplier;
};

#endif // SIMPLE_ITEM_H

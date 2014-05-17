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

#include <string>
#include <map>
#include "VariablesMap.h"

class SimpleItem
{
public:
	SimpleItem();
	SimpleItem(const VariablesType& variable, double nMultiplier);
	SimpleItem(std::string strVar, double nVarPower, double nMultiplier);
	SimpleItem(const SimpleItem& otherItem);
	virtual ~SimpleItem();
	virtual SimpleItem& operator=(const SimpleItem& otherItem);
	virtual bool operator==(const SimpleItem& otherItem) const;
	virtual bool operator!=(const SimpleItem& otherItem) const;

	virtual SimpleItem& operator*=(const SimpleItem& otherItem);
	virtual SimpleItem operator*(const SimpleItem& otherItem) const;
	virtual SimpleItem& operator/=(const SimpleItem& otherItem);
	virtual SimpleItem operator/(const SimpleItem& otherItem) const;

	virtual double getMultiplier() const;
	virtual void setMultiplier(const double newMultiplier);

	VariablesType getVariables() const;
	void setVariablePower(const std::string sVariable, const double nPower);

	virtual bool isVariablesEqual(const SimpleItem& otherItem) const;

	std::string toString() const;

	void print();
protected:
	CVariablesMap m_Variables;
	double m_nMultiplier;
};

#endif // SIMPLE_ITEM_H

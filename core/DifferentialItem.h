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


#ifndef DIFFERENTIAL_ITEM_H
#define DIFFERENTIAL_ITEM_H

#include "SimpleItem.h"
#include "Item.h"

// map: key - differentila index, value - pair: first - power of the differential,
// second - SimpleItem.
typedef std::map<std::string, std::pair<double, SimpleItem> > DifferentialMap;

class DifferentialItem : public Item
{
public:
	DifferentialItem();
	DifferentialItem(const VariablesType &variables, double nMultiplier,
		std::string sDiff, double nDiffPower, double nDiffMultiplier);
	DifferentialItem(std::string sVariable, double nPower, double nMultiplier,
		std::string sDiff, double nDiffPower, double nDiffMultiplier);
	DifferentialItem(const SimpleItem& simple, std::string sDiff, double nDiffPower,
		double nDiffMultiplier);
	DifferentialItem(const DifferentialItem& item);
	virtual ~DifferentialItem();

	virtual Item& operator=(const Item& otherItem);
	DifferentialItem& operator=(const DifferentialItem& otherItem);
	virtual bool operator==(const Item& otherItem) const;
	virtual bool operator!=(const Item& otherItem) const;

	virtual Item& operator*=(const Item& otherItem);
	virtual Item& operator*(const Item& otherItem);
	virtual Item& operator/=(const Item& otherItem);
	virtual Item& operator/(const Item& otherItem);

	virtual double getMultiplier() const;
	virtual void setMultiplier(const double newMultiplier);

	virtual bool isSubitemsEqual(const Item& otherItem) const;

	virtual std::string toString() const;

private:
	DifferentialMap m_Differentials;
	double m_nDiffMultiplier;
};

#endif // DIFFERENTIAL_ITEM_H

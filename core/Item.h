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


#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
public:
	virtual Item& operator=(const Item& otherItem) = 0;
	virtual bool operator==(const Item& otherItem) const = 0;
	virtual bool operator!=(const Item& otherItem) const = 0;

	virtual Item& operator*(const Item& otherItem) = 0;
	virtual Item& operator/(const Item& otherItem) = 0;

	virtual double getMultiplier() const = 0;
	virtual void setMultiplier(const double newMultiplier) = 0;

	virtual bool isSubitemsEqual(const Item& otherItem) const = 0;

	virtual std::string toString() const = 0;
};

#endif // ITEM_H

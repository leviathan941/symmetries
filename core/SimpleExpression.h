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


#ifndef SIMPLE_EXPRESSION_H
#define SIMPLE_EXPRESSION_H

#include <vector>
#include <string>

class SimpleItem;

class SimpleExpression
{
public:
	SimpleExpression();
	SimpleExpression(const SimpleItem& item);
	SimpleExpression(const SimpleExpression& other);
	virtual ~SimpleExpression();

	virtual SimpleExpression& operator=(const SimpleExpression& otherExp);
	virtual bool operator==(const SimpleExpression& otherExp) const;
	virtual bool operator!=(const SimpleExpression& otherExp) const;

	SimpleExpression operator+(const SimpleExpression& otherExp) const;
	SimpleExpression operator-(const SimpleExpression& otherExp) const;

	SimpleExpression& operator*=(const SimpleExpression& otherExp);
	SimpleExpression operator*(const SimpleExpression& otherExp) const;

	SimpleExpression& operator*=(const SimpleItem& sepItem);
	SimpleExpression operator*(const SimpleItem& sepItem) const;

	SimpleExpression& operator/=(const SimpleItem& sepItem);
	SimpleExpression operator/(const SimpleItem& sepItem) const;

	SimpleExpression& operator/=(const SimpleExpression& otherExp);
	SimpleExpression operator/(const SimpleExpression& otherExp) const;

	SimpleExpression operator*(const double nNumber) const;
	SimpleExpression operator/(const double nNumber) const;

	SimpleItem getItem(const unsigned nItemPosition) const;
	void setItemMultiplier(const unsigned nItemPosition, const double nNewMultiplier);
	std::vector<SimpleItem> getVectorItems() const;
	int isSimilarItemInExpression(const SimpleItem& item) const;
	void pushItem(const SimpleItem& newItem);
	void eraseItem(const unsigned nPosition);
	bool isEmpty();
	void clear();
	std::string toString();
	void print();

private:
	void findRemoveEmptyItems();

	std::vector<SimpleItem> m_vecItems;
};

#endif // SIMPLE_EXPRESSION_H

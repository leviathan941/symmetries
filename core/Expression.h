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


#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <string>

class Item;

class Expression
{
public:
	Expression();
	Expression(const Item& item);
	Expression(const Expression& other);
	virtual ~Expression();

	virtual Expression& operator=(const Expression& otherExp);
	virtual bool operator==(const Expression& otherExp) const;
	virtual bool operator!=(const Expression& otherExp) const;

	Expression operator+(const Expression& otherExp);
	Expression operator-(const Expression& otherExp);
	Expression operator*(const Expression& otherExp);
	Expression operator/(const Expression& otherExp);

	Expression operator*(const double nNumber);
	Expression operator/(const double nNumber);

	Item getItem(const unsigned nItemPosition) const;
	void setItemMultiplier(const unsigned nItemPosition, const double nNewMultiplier);
	std::vector<Item> getVectorItems() const;
	int isSimilarItemInExpression(const Item& item) const;
	void pushItem(const Item& newItem);
	void eraseItem(const unsigned nPosition);
	std::string toString();
	void print();

private:
	std::vector<Item> m_vecItems;
};

#endif // EXPRESSION_H

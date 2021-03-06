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


#ifndef DIFFERENTIAL_EXPRESSION_H
#define DIFFERENTIAL_EXPRESSION_H

#include <vector>
#include <string>

class DifferentialItem;

class DifferentialExpression
{
public:
	DifferentialExpression();
	DifferentialExpression(const DifferentialItem& item);
	DifferentialExpression(const DifferentialExpression& other);
	virtual ~DifferentialExpression();

	virtual DifferentialExpression& operator=(const DifferentialExpression& otherExp);
	virtual bool operator==(const DifferentialExpression& otherExp) const;
	virtual bool operator!=(const DifferentialExpression& otherExp) const;

	DifferentialExpression& operator+=(const DifferentialExpression& otherExp);
	DifferentialExpression operator+(const DifferentialExpression& otherExp) const;
	DifferentialExpression operator-(const DifferentialExpression& otherExp) const;
	DifferentialExpression operator*(const DifferentialExpression& otherExp) const;
	DifferentialExpression operator/(const DifferentialExpression& otherExp) const;

	DifferentialExpression operator*(const double nNumber) const;
	DifferentialExpression operator/(const double nNumber) const;

	const DifferentialItem& getItem(unsigned nItemPosition) const;
	void setItemMultiplier(const unsigned nItemPosition, const double nNewMultiplier);
	int isSimilarItemInExpression(const DifferentialItem& item) const;
	void pushItem(const DifferentialItem& newItem);
	void eraseItem(const unsigned nPosition);
	bool isEmpty();
	void clear();
	std::string toString() const;
	void print();

private:
	void findRemoveEmptyItems();

	std::vector<DifferentialItem> m_vecItems;
};

#endif // DIFFERENTIAL_EXPRESSION_H

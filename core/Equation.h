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


#ifndef EQUATION_H
#define EQUATION_H

#include "Expression.h"

class Equation
{

public:
	Equation();
	Equation(Expression leftPart, Expression rightPart);
	Equation(const Equation& other);
	virtual ~Equation();
	virtual Equation& operator=(const Equation& other);
	virtual bool operator==(const Equation& other) const;
	virtual bool operator!=(const Equation& other) const;

	virtual Equation operator+(const Equation& other) const;
	virtual Equation operator-(const Equation& other) const;
	virtual Equation operator*(const Equation& other) const;
	virtual Equation operator/(const Equation& other) const;

	virtual Equation operator*(const double nNumber) const;
	virtual Equation operator/(const double nNumber) const;

	void toLeft();
	void toRight();

private:
	Expression m_leftExp;
	Expression m_rightExp;
};

#endif // EQUATION_H

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


#ifndef DIFFERENTIAL_EQUATION_H
#define DIFFERENTIAL_EQUATION_H

#include "DifferentialExpression.h"

class DifferentialEquation
{

public:
	DifferentialEquation();
	DifferentialEquation(const DifferentialExpression& leftPart,
		const DifferentialExpression& rightPart);
	DifferentialEquation(const DifferentialEquation& other);
	virtual ~DifferentialEquation();
	virtual DifferentialEquation& operator=(const DifferentialEquation& other);
	virtual bool operator==(const DifferentialEquation& other) const;
	virtual bool operator!=(const DifferentialEquation& other) const;

	virtual DifferentialEquation operator+(const DifferentialEquation& other) const;
	virtual DifferentialEquation operator-(const DifferentialEquation& other) const;
	virtual DifferentialEquation operator*(const DifferentialEquation& other) const;
	virtual DifferentialEquation operator/(const DifferentialEquation& other) const;

	virtual DifferentialEquation operator*(const double nNumber) const;
	virtual DifferentialEquation operator/(const double nNumber) const;

	const DifferentialExpression& getLeft() const;
	const DifferentialExpression& getRight() const;
	void toLeft();
	void toRight();

	std::string toString() const;

private:
	DifferentialExpression m_leftExp;
	DifferentialExpression m_rightExp;
};

#endif // DIFFERENTIAL_EQUATION_H

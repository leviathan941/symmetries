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


#include "Equation.h"

Equation::Equation()
: m_leftExp(), m_rightExp()
{
}

///////////////////////////////////////////////////////////////////////////
Equation::Equation(Expression leftPart, Expression rightPart)
: m_leftExp(leftPart)
, m_rightExp(rightPart)
{
}

///////////////////////////////////////////////////////////////////////////
Equation::Equation(const Equation& other)
{
	m_leftExp = other.m_leftExp;
	m_leftExp = other.m_rightExp;
}

///////////////////////////////////////////////////////////////////////////
Equation::~Equation()
{
}

///////////////////////////////////////////////////////////////////////////
Equation& Equation::operator=(const Equation& other)
{
	if (this != &other)
	{
		m_leftExp = other.m_leftExp;
		m_rightExp = other.m_rightExp;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool Equation::operator==(const Equation& other) const
{
	return ((m_leftExp == other.m_leftExp)
		&& (m_rightExp == other.m_rightExp));
}

///////////////////////////////////////////////////////////////////////////
bool Equation::operator!=(const Equation& other) const
{
	return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////
Equation Equation::operator+(const Equation& other) const
{
	Equation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp + other.m_leftExp;
	tempEquation.m_rightExp = this->m_rightExp + other.m_rightExp;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
Equation Equation::operator-(const Equation& other) const
{
	Equation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp - other.m_leftExp;
	tempEquation.m_rightExp = this->m_rightExp - other.m_rightExp;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
Equation Equation::operator*(const Equation& other) const
{
	Equation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp * other.m_leftExp;
	tempEquation.m_rightExp = this->m_rightExp * other.m_rightExp;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
Equation Equation::operator/(const Equation& other) const
{
	Equation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp / other.m_leftExp;
	tempEquation.m_rightExp = this->m_rightExp / other.m_rightExp;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
Equation Equation::operator*(const double nNumber) const
{
	Equation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp * nNumber;
	tempEquation.m_rightExp = this->m_rightExp * nNumber;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
Equation Equation::operator/(const double nNumber) const
{
	Equation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp / nNumber;
	tempEquation.m_rightExp = this->m_rightExp / nNumber;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
void Equation::toLeft()
{
	m_leftExp = m_leftExp - m_rightExp;
	m_rightExp.clear();
}

///////////////////////////////////////////////////////////////////////////
void Equation::toRight()
{
	m_rightExp = m_rightExp - m_leftExp;
	m_leftExp.clear();
}

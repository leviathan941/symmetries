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


#include "DifferentialEquation.h"
#include "Exceptions.h"

#include <sstream>
#include <iostream>

DifferentialEquation::DifferentialEquation()
: m_leftExp(), m_rightExp()
{
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation::DifferentialEquation(const DifferentialExpression& leftPart,
	const DifferentialExpression& rightPart)
: m_leftExp(leftPart)
, m_rightExp(rightPart)
{
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation::DifferentialEquation(const DifferentialEquation& other)
{
	m_leftExp = other.m_leftExp;
	m_rightExp = other.m_rightExp;
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation::~DifferentialEquation()
{
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation& DifferentialEquation::operator=(const DifferentialEquation& other)
{
	if (this != &other)
	{
		m_leftExp = other.m_leftExp;
		m_rightExp = other.m_rightExp;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialEquation::operator==(const DifferentialEquation& other) const
{
	return ((m_leftExp == other.m_leftExp)
		&& (m_rightExp == other.m_rightExp));
}

///////////////////////////////////////////////////////////////////////////
bool DifferentialEquation::operator!=(const DifferentialEquation& other) const
{
	return !(*this == other);
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation DifferentialEquation::operator+(const DifferentialEquation& other) const
{
	DifferentialEquation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp + other.m_leftExp;
	tempEquation.m_rightExp = this->m_rightExp + other.m_rightExp;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation DifferentialEquation::operator-(const DifferentialEquation& other) const
{
	DifferentialEquation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp - other.m_leftExp;
	tempEquation.m_rightExp = this->m_rightExp - other.m_rightExp;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation DifferentialEquation::operator*(const DifferentialEquation& other) const
{
	DifferentialEquation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp * other.m_leftExp;
	tempEquation.m_rightExp = this->m_rightExp * other.m_rightExp;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation DifferentialEquation::operator/(const DifferentialEquation& other) const
{
	DifferentialEquation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp / other.m_leftExp;
	tempEquation.m_rightExp = this->m_rightExp / other.m_rightExp;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation DifferentialEquation::operator*(const double nNumber) const
{
	DifferentialEquation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp * nNumber;
	tempEquation.m_rightExp = this->m_rightExp * nNumber;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
DifferentialEquation DifferentialEquation::operator/(const double nNumber) const
{
	if (nNumber == 0.0)
	{
		throw coreException("Division by zero");
	}

	DifferentialEquation tempEquation(*this);

	tempEquation.m_leftExp = this->m_leftExp / nNumber;
	tempEquation.m_rightExp = this->m_rightExp / nNumber;

	return tempEquation;
}

///////////////////////////////////////////////////////////////////////////
const DifferentialExpression& DifferentialEquation::getLeft() const
{
	return m_leftExp;
}

///////////////////////////////////////////////////////////////////////////
const DifferentialExpression& DifferentialEquation::getRight() const
{
	return m_rightExp;
}

///////////////////////////////////////////////////////////////////////////
void DifferentialEquation::toLeft()
{
	m_leftExp = m_leftExp - m_rightExp;
	m_rightExp.clear();
}

///////////////////////////////////////////////////////////////////////////
void DifferentialEquation::toRight()
{
	m_rightExp = m_rightExp - m_leftExp;
	m_leftExp.clear();
}

///////////////////////////////////////////////////////////////////////////
std::string DifferentialEquation::toString() const
{
	std::stringstream strStream;

	strStream << m_leftExp.toString() << " = " << m_rightExp.toString();
	return strStream.str();
}

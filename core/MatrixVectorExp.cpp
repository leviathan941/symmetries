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


#include "MatrixVectorExp.h"

#include <sstream>

MatrixVectorExp::MatrixVectorExp():
m_content(0, 0)
{
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp::MatrixVectorExp(const unsigned nRowNumber, const unsigned nColumnNumber):
m_content(nRowNumber, nColumnNumber)
{
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp::MatrixVectorExp(const std::vector<MatrixVector<Expression>::boostMatrix> &vecMatrices,
	const unsigned nRowNumber, const unsigned nColumnNumber)
: m_content(vecMatrices, nRowNumber, nColumnNumber)
{
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp::MatrixVectorExp(const MatrixVectorExp& other)
{
	m_content = other.m_content;
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp::~MatrixVectorExp()
{
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
MatrixVectorExp& MatrixVectorExp::operator=(const MatrixVectorExp& other)
{
	if(&other != this)
	{
		m_content = other.m_content;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
bool MatrixVectorExp::operator==(const MatrixVectorExp& other) const
{
	return (m_content == other.m_content);
}

///////////////////////////////////////////////////////////////////////////
bool MatrixVectorExp::operator!=(const MatrixVectorExp& other) const
{
	return (m_content != other.m_content);
}

///////////////////////////////////////////////////////////////////////////
Expression& MatrixVectorExp::operator()(const unsigned nPosition, const unsigned nRow,
const unsigned nColumn)
{
	//	std:: cout << m_content.getVectorSize() << " " << m_content.getMatrixRowSize() <<
	//		" " << m_content.getMatrixColumnSize() << std::endl;
	if(!(nPosition < m_content.getVectorSize() &&
	nRow < m_content.getMatrixRowSize() &&
	nColumn < m_content.getMatrixColumnSize())
	)
	{
		std::cout << "No such element" << std::endl;
	}
	return m_content(nPosition, nRow, nColumn);
}

///////////////////////////////////////////////////////////////////////////
MatrixVector<Expression>::boostMatrix& MatrixVectorExp::operator[](const unsigned nPosition)
{
	return m_content[nPosition];
}

///////////////////////////////////////////////////////////////////////////
void MatrixVectorExp::addMatrix(unsigned int nPosition, MatrixVector<Expression>::boostMatrix& matr)
{
	m_content.addMatrix(nPosition, matr);
}

///////////////////////////////////////////////////////////////////////////
void MatrixVectorExp::addMatrix(MatrixVector<Expression>::boostMatrix& matr)
{
	m_content.addMatrix(matr);
}

///////////////////////////////////////////////////////////////////////////
void MatrixVectorExp::removeMatrix(unsigned int nPosition)
{
	m_content.removeMatrix(nPosition);
}

///////////////////////////////////////////////////////////////////////////
void MatrixVectorExp::setMatrix(unsigned int nPosition, MatrixVector<Expression>::boostMatrix& matr)
{
	m_content.setMatrix(nPosition, matr);
}

///////////////////////////////////////////////////////////////////////////
void MatrixVectorExp::setElement(unsigned int nPosition, unsigned int nRow, unsigned int nColumn, Expression& value)
{
	m_content.setElement(nPosition, nRow, nColumn, value);
}

///////////////////////////////////////////////////////////////////////////
void MatrixVectorExp::allocateSize(const unsigned int vectorSize, const unsigned int matrixRowSize, const unsigned int matrixColumSize)
{
	m_content.allocateSize(vectorSize, matrixRowSize, matrixColumSize);
}

///////////////////////////////////////////////////////////////////////////
void MatrixVectorExp::clear()
{
	m_content.clear();
}

///////////////////////////////////////////////////////////////////////////
MatrixVector<Expression> MatrixVectorExp::getContent() const
{
	return m_content;
}

///////////////////////////////////////////////////////////////////////////
Expression MatrixVectorExp::getExpression(const unsigned position, const unsigned row, const unsigned column) const
{
	return m_content.getElement(position, row, column);
}

///////////////////////////////////////////////////////////////////////////
std::string MatrixVectorExp::toString()
{
	std::stringstream strStream;

	for(unsigned i = 0; i < m_content.getVectorSize(); ++i)
	{
		for(unsigned j = 0; j < m_content.getMatrixRowSize(); ++j)
		{
			for(unsigned k = 0; k < m_content.getMatrixColumnSize(); ++k)
			{
				strStream << getExpression(i, j, k).toString();
				if(k != m_content.getMatrixColumnSize() - 1)
					strStream << " ";
			}
			strStream << std::endl;
		}
		strStream << std::endl;
	}

	return strStream.str();
}

///////////////////////////////////////////////////////////////////////////
void MatrixVectorExp::print()
{
	std::cout << toString();
}


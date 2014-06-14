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


#ifndef MATRIX_VECTOR_EXP_H
#define MATRIX_VECTOR_EXP_H

#include "MatrixVector.h"
#include "SimpleExpression.h"

class MatrixVectorExp
{

public:
	typedef MatrixVector<SimpleExpression>::boostMatrix expBoostMatrix;

	MatrixVectorExp();
	MatrixVectorExp(const unsigned nRowNumber, const unsigned nColumnNumber);
	MatrixVectorExp(const std::vector<expBoostMatrix>& vecMatrices,
		const unsigned nRowNumber, const unsigned nColumnNumber);
	MatrixVectorExp(const MatrixVectorExp& other);
	virtual ~MatrixVectorExp();
	virtual MatrixVectorExp& operator=(const MatrixVectorExp& other);
	virtual bool operator==(const MatrixVectorExp& other) const;
	virtual bool operator!=(const MatrixVectorExp& other) const;
	virtual SimpleExpression& operator()(const unsigned nPosition, const unsigned nRow, const unsigned nColumn);
	virtual expBoostMatrix& operator[](const unsigned nPosition);

	void addMatrix(unsigned nPosition, expBoostMatrix& matr);
	void addMatrix(MatrixVector<SimpleExpression>::boostMatrix& matr);
	void removeMatrix(unsigned nPosition);
	void setMatrix(unsigned nPosition, expBoostMatrix& matr);
	void setElement(unsigned nPosition, unsigned nRow, unsigned nColumn, SimpleExpression& value);
	void allocateSize(const unsigned vectorSize, const unsigned matrixRowSize, const unsigned matrixColumSize);
	void clear();

	MatrixVector<SimpleExpression> getContent() const;
	SimpleExpression getExpression(const unsigned item, const unsigned row, const unsigned column) const;
	std::string toString();
	void print();
private:
	MatrixVector<SimpleExpression> m_content;
};

#endif // MATRIX_VECTOR_EXP_H

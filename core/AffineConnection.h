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

#ifndef AFFINE_CONNECTION_H
#define AFFINE_CONNECTION_H

#include "Expression.h"
#include "MatrixVectorExp.h"

#include <boost/numeric/ublas/matrix.hpp>

typedef boost::numeric::ublas::matrix<Expression> boostMatrixExp;

class AffineConnection
{
public:
	AffineConnection();
	AffineConnection(const AffineConnection& otherAC);
	virtual ~AffineConnection();

	virtual AffineConnection& operator=(const AffineConnection& otherAC);

	boostMatrixExp getMetricTensor() const;
	MatrixVectorExp getTorsionTensor() const;
	MatrixVectorExp getChristoffelSymbols() const;

	void allocateSize(const unsigned vectorSize, const unsigned matrixRowSize, const unsigned matrixColumnSize);
	void setMetricTensor(boost::numeric::ublas::matrix<Expression>& matrixExp);
	void setTorsionTensor(MatrixVectorExp& matrixVectorExp);

	void calculateChristoffelSymbols();
	void printChristoffelSymbols();
private:
	boostMatrixExp m_metricTensor;
	MatrixVectorExp m_torsionTensor;
	MatrixVectorExp m_christoffelSymbols;
	unsigned m_nDimension;
};

#endif // AFFINE_CONNECTION_H

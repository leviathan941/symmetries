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

#include "AffineConnection.h"

#include <iostream>
#include <boost/foreach.hpp>

AffineConnection::AffineConnection()
:m_metricTensor()
, m_torsionTensor()
, m_christoffelSymbols()
, m_nDimension(0)
{
}

///////////////////////////////////////////////////////////////////////////
AffineConnection::AffineConnection(const AffineConnection& otherAC)
{
	m_metricTensor = otherAC.m_metricTensor;
	m_torsionTensor = otherAC.m_torsionTensor;
}

///////////////////////////////////////////////////////////////////////////
AffineConnection::~AffineConnection()
{
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
AffineConnection& AffineConnection::operator=(const AffineConnection& otherAC)
{
	if(&otherAC != this)
	{
		m_metricTensor = otherAC.m_metricTensor;
		m_torsionTensor = otherAC.m_torsionTensor;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
boostMatrixExp AffineConnection::getMetricTensor() const
{
	return m_metricTensor;
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp AffineConnection::getTorsionTensor() const
{
	return m_torsionTensor;
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp AffineConnection::getChristoffelSymbols() const
{
	return m_christoffelSymbols;
}

///////////////////////////////////////////////////////////////////////////
void AffineConnection::allocateSize(const unsigned int vectorSize, const unsigned int matrixRowSize,
const unsigned int matrixColumnSize)
{
	m_christoffelSymbols.allocateSize(vectorSize, matrixRowSize, matrixColumnSize);
}

///////////////////////////////////////////////////////////////////////////
void AffineConnection::setMetricTensor(boost::numeric::ublas::matrix<Expression>& matrExp)
{
	m_metricTensor = matrExp;
}

///////////////////////////////////////////////////////////////////////////
void AffineConnection::setTorsionTensor(MatrixVectorExp& matrVectorExp)
{
	m_torsionTensor = matrVectorExp;
}

///////////////////////////////////////////////////////////////////////////
void AffineConnection::calculateChristoffelSymbols()
{
	if(m_metricTensor.size1() != m_torsionTensor.getContent().getMatrixRowSize() ||
	m_metricTensor.size2() != m_torsionTensor.getContent().getMatrixColumnSize() ||
	m_torsionTensor.getContent().getVectorSize() != m_metricTensor.size1() ||
	m_torsionTensor.getContent().getVectorSize() != m_metricTensor.size2()
	)
	{
		std::cerr << "Error. All matrices must have the same dimension." << std::endl;
		return;
	}
	else
	{
		m_nDimension = m_torsionTensor.getContent().getVectorSize();
		m_christoffelSymbols.allocateSize(m_nDimension, m_nDimension, m_nDimension);
	}

	for(unsigned k = 0; k < m_torsionTensor.getContent().getVectorSize(); ++k)
	{
		for(unsigned i = 0; i < m_torsionTensor.getContent().getMatrixRowSize(); ++i)
		{
			for(unsigned j = 0; j < m_torsionTensor.getContent().getMatrixColumnSize(); ++j)
			{
				for(unsigned s = 0; s < m_nDimension; ++s)
				{
					for(unsigned m = 0; m < m_nDimension; ++m)
					{
						Expression metricTensorIM(m_metricTensor(i, m));
						Expression metricTensorKS(m_metricTensor(k, s));
						Expression metricTensorMJ(m_metricTensor(m, j));
						Expression torsionTensorMSJ(m_torsionTensor(m, s, j));
						Expression torsionTensorMSI(m_torsionTensor(m, s, i));

						Expression tempChristoffel = metricTensorKS *
							(metricTensorIM * torsionTensorMSJ +
							metricTensorMJ * torsionTensorMSI);

						m_christoffelSymbols(k, i, j) = m_christoffelSymbols(k, i, j) + tempChristoffel;
						std::cout << "m_christoffelSymbols(" << k << ", " << i <<", " << j <<") = ";
						m_christoffelSymbols(k, i, j).print();
						std::cout << std::endl;
					}
				}
				Expression torsionTensorKIJ(m_torsionTensor(k, i, j));
				m_christoffelSymbols(k, i, j) = (m_christoffelSymbols(k, i, j) + torsionTensorKIJ) * 0.5;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////
void AffineConnection::printChristoffelSymbols()
{
	m_christoffelSymbols.print();
}


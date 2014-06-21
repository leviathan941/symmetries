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
#include "Exceptions.h"

#include <iostream>
#include <boost/foreach.hpp>

AffineConnection::AffineConnection()
: m_metricTensor()
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
	m_christoffelSymbols = otherAC.m_christoffelSymbols;
	m_nDimension = otherAC.m_nDimension;
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
		m_christoffelSymbols = otherAC.m_christoffelSymbols;
		m_nDimension = otherAC.m_nDimension;
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
void AffineConnection::setMetricTensor(boost::numeric::ublas::matrix<SimpleExpression>& matrExp)
{
	m_metricTensor = matrExp;
}

///////////////////////////////////////////////////////////////////////////
void AffineConnection::setTorsionTensor(MatrixVectorExp& matrVectorExp)
{
	m_torsionTensor = matrVectorExp;
}

///////////////////////////////////////////////////////////////////////////
const MatrixVectorExp& AffineConnection::calculateChristoffelSymbols()
{
	if(m_metricTensor.size1() != m_torsionTensor.getContent().getMatrixRowSize() ||
		m_metricTensor.size2() != m_torsionTensor.getContent().getMatrixColumnSize() ||
		m_torsionTensor.getContent().getVectorSize() != m_metricTensor.size1() ||
		m_torsionTensor.getContent().getVectorSize() != m_metricTensor.size2())
	{
		std::cerr << "Error. All matrices must have the same dimension." << std::endl;
		throw coreException("Incorrect matrix dimentions.");
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
						SimpleExpression metricTensorIM(m_metricTensor(i, m));
						SimpleExpression metricTensorKS(m_metricTensor(k, s));
						SimpleExpression metricTensorMJ(m_metricTensor(m, j));
						SimpleExpression torsionTensorMSJ(m_torsionTensor(m, s, j));
						SimpleExpression torsionTensorMSI(m_torsionTensor(m, s, i));

						SimpleExpression tempChristoffel = metricTensorKS *
							(metricTensorIM * torsionTensorMSJ +
							metricTensorMJ * torsionTensorMSI);

						m_christoffelSymbols(k, i, j) = m_christoffelSymbols(k, i, j) + tempChristoffel;
						std::cout << "m_christoffelSymbols(" << k << ", " << i <<", " << j <<") = ";
						m_christoffelSymbols(k, i, j).print();
						std::cout << std::endl;
					}
				}
				SimpleExpression torsionTensorKIJ(m_torsionTensor(k, i, j));
				m_christoffelSymbols(k, i, j) = (m_christoffelSymbols(k, i, j) + torsionTensorKIJ) * 0.5;
			}
		}
	}

	return m_christoffelSymbols;
}

///////////////////////////////////////////////////////////////////////////
const MatrixVectorExp& AffineConnection::calculateTorsion()
{
	using namespace boost::numeric::ublas;

	if (m_christoffelSymbols.getContent().getVectorSize() == 0
		|| m_christoffelSymbols.getContent().getMatrixRowSize() == 0
		|| m_christoffelSymbols.getContent().getMatrixColumnSize() == 0)
	{
		std::cerr << "Error. Incorrect dimension of the christoffel's matrix." << std::endl;
		throw coreException("Incorrect matrix dimentions.");
	} else
	{
		m_torsionTensor.clear();
		m_nDimension = m_christoffelSymbols.getContent().getVectorSize();
		m_torsionTensor.allocateSize(m_nDimension, m_nDimension, m_nDimension);
	}

	for (unsigned i = 0; i < m_christoffelSymbols.getContent().getVectorSize(); ++i)
	{
		boostMatrixExp transMatrix = trans(m_christoffelSymbols.getContent()[i]);
		m_torsionTensor[i] = m_christoffelSymbols[i] - transMatrix;
	}

	return m_torsionTensor;
}

///////////////////////////////////////////////////////////////////////////
void AffineConnection::printChristoffelSymbols()
{
	m_christoffelSymbols.print();
}

///////////////////////////////////////////////////////////////////////////
void AffineConnection::printTorsion()
{
	m_torsionTensor.print();
}

/*
	Symmetries
	Copyright (C) 2013, 2014  Alexey Kuzin <amkuzink@gmail.com>

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

#ifndef MATRIX_VECTOR_H
#define MATRIX_VECTOR_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <iostream>

template <typename T = double>
class MatrixVector
{
public:
	typedef boost::numeric::ublas::matrix<T> boostMatrix;
	
	MatrixVector(const unsigned nRowNumber = 0, const unsigned nColumnNumber = 0);
	MatrixVector(const std::vector<boostMatrix>& vecMatrices, const unsigned nRowNumber, const unsigned nColumnNumber);
	MatrixVector(const MatrixVector& otherVector);
	virtual ~MatrixVector();
	
	virtual MatrixVector<T>& operator=(const MatrixVector<T>& otherVector);
	virtual bool operator==(const MatrixVector<T>& otherVector) const;
	virtual bool operator!=(const MatrixVector<T>& otherVector) const;
	virtual T& operator()(const unsigned nPosition, const unsigned nRow, const unsigned nColumn);
	
	/**
	 * This method returns the vector which stores in the class
	 * @return The vector, which contains matrices
	 */
	std::vector<boostMatrix> getVector() const;
	unsigned getMatrixRowSize() const;
	unsigned getMatrixColumnSize() const;
	unsigned getVectorSize() const;
	
	/**
	 * This method adds the matrix @matr to selected position of the vector
	 * @param nPosition - position where @matr must be added
	 * @param matr - Matrix to add to the vector
	 * @return none
	 */
	void addMatrix(unsigned nPosition, boostMatrix& matr);
	
	/**
	 * This method adds the matrix @matr to the back of the vector
	 * @param matr - Matrix to add to the vector
	 * @return none
	 */
	void addMatrix(boostMatrix& matr);
	
	/**
	 * This method removes matrix from the vector
	 * @param nPosition - Remove the matrix from this position
	 * @return none
	 */
	void removeMatrix(unsigned nPosition);
	
	/**
	 * This method changes matrix on some position in the vector
	 * @param nPosition - Position of the matrix for changing
	 * @param matr - Change a matrix from @nPosition to this matrix
	 * @return none
	 */
	void setMatrix(unsigned nPosition,
	boostMatrix& matr);
	
	boostMatrix getMatrix(unsigned nPosition) const;
	
	T getElement(unsigned nPosition,
	unsigned nRow,
	unsigned nColumn) const;
	
	void setElement(unsigned nPosition,
	unsigned nRow,
	unsigned nColumn,
	T value);
	
	void allocateSize(const unsigned vectorSize, const unsigned matrixRowSize, const unsigned matrixColumSize);
	
	//	void printMatrix(unsigned nPosition) const;
	
private:
	std::vector<boostMatrix> m_matrVec;
	unsigned m_nRowNumber;
	unsigned m_nColumnNumber;
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
template <typename T>
MatrixVector<T>::MatrixVector(const unsigned nRowNumber, const unsigned nColumnNumber):
m_matrVec(), m_nRowNumber(nRowNumber), m_nColumnNumber(nColumnNumber)
{
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
MatrixVector<T>::MatrixVector(const std::vector<boostMatrix>& vecMatrices,
	const unsigned nRowNumber, const unsigned nColumnNumber)
: m_matrVec(vecMatrices)
, m_nRowNumber(nRowNumber)
, m_nColumnNumber(nColumnNumber)
{
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
MatrixVector<T>::MatrixVector(const MatrixVector& otherVector)
{
	m_matrVec = otherVector.m_matrVec;
	m_nRowNumber = otherVector.m_nRowNumber;
	m_nColumnNumber = otherVector.m_nColumnNumber;
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
MatrixVector<T>::~MatrixVector()
{
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
MatrixVector<T>& MatrixVector<T>::operator=(const MatrixVector<T>& otherVector)
{
	if(&otherVector != this)
	{
		m_matrVec = otherVector.m_matrVec;
		m_nRowNumber = otherVector.m_nRowNumber;
		m_nColumnNumber = otherVector.m_nColumnNumber;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
bool MatrixVector<T>::operator==(const MatrixVector& otherVector) const
{
	if(m_matrVec.size() != otherVector.getVector().size() ||
	m_nRowNumber != otherVector.getMatrixRowSize() ||
	m_nColumnNumber != otherVector.getMatrixColumnSize())
	{
		return false;
	}
	
	for(unsigned pos = 0; pos < m_matrVec.size(); ++pos)
	{
		for(unsigned i = 0; i < m_matrVec[pos].size1(); ++i)
		{
			for(unsigned j = 0; j < m_matrVec[pos].size2(); ++j)
			{
				if(m_matrVec[pos](i, j) != otherVector.m_matrVec[pos](i, j))
				{
					return false;
				}
			}
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
bool MatrixVector<T>::operator!=(const MatrixVector<T>& otherVector) const
{
	return !(*this == otherVector);
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
T& MatrixVector<T>::operator()(const unsigned int nPosition, const unsigned int nRow, const unsigned int nColumn)
{
	return m_matrVec[nPosition](nRow, nColumn);
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
std::vector<boost::numeric::ublas::matrix<T> > MatrixVector<T>::getVector() const
{
	return m_matrVec;
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
unsigned MatrixVector<T>::getMatrixRowSize() const
{
	return m_nRowNumber;
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
unsigned MatrixVector<T>::getMatrixColumnSize() const
{
	return m_nColumnNumber;
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
unsigned MatrixVector<T>::getVectorSize() const
{
	return m_matrVec.size();
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
void MatrixVector<T>::addMatrix(unsigned nPosition, boostMatrix& matr)
{
	if(m_matrVec.size() < nPosition ||
	matr.size1() != m_nRowNumber ||
	matr.size2() != m_nColumnNumber)
	{
		std::cerr << "MatrixVector::addMatrix\tCannot add a matrix."
		<< std::endl;
	}
	m_matrVec.insert(m_matrVec.begin() + nPosition, matr);
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
void MatrixVector<T>::addMatrix(boostMatrix& matr)
{
	if(matr.size1() != m_nRowNumber ||
	matr.size2() != m_nColumnNumber)
	{
		std::cerr << "MatrixVector::addMatrix\tCannot add a matrix."
		<< std::endl;
	}
	m_matrVec.push_back(matr);
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
void MatrixVector<T>::removeMatrix(unsigned nPosition)
{
	if(m_matrVec.size() < nPosition)
	{
		std::cerr << "MatrixVector::removeMatrix\tCannot remove a matrix from position "
		<< nPosition <<" because the position doesn't exist" << std::endl;
	}
	m_matrVec.erase(m_matrVec.begin() + nPosition);
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
void MatrixVector<T>::setMatrix(unsigned nPosition, boostMatrix& matr)
{
	if(m_matrVec.size() < nPosition ||
	matr.size1() != m_nRowNumber ||
	matr.size2() != m_nColumnNumber)
	{
		std::cerr << "MatrixVector::setMatrix\tCannot set a matrix."
		<< std::endl;
	}
	m_matrVec[nPosition] = matr;
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
boost::numeric::ublas::matrix<T> MatrixVector<T>::getMatrix(unsigned nPosition) const
{
	if(m_matrVec.size() < nPosition)
	{
		std::cerr << "MatrixVector::getMatrix\tCannot get a matrix from position "
		<< nPosition << " because the matrix doesn't exist. Please add a matrix first"
		<< std::endl;
	}
	return m_matrVec[nPosition];
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
T MatrixVector<T>::getElement(unsigned nPosition, unsigned nRow, unsigned nColumn) const
{
	if(m_matrVec.size() < nPosition ||
	m_nRowNumber < nRow ||
	m_nColumnNumber < nColumn)
	{
		std::cerr << "MatrixVector::getElement\tCannot get the element of the matrix "
		<< nPosition << " because the matrix doesn't exist" << std::endl;
		T element;
		return element;
	}
	return m_matrVec[nPosition](nRow, nColumn);
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
void MatrixVector<T>::setElement(unsigned nPosition, unsigned nRow, unsigned nColumn, T value)
{
	if(m_matrVec.size() < nPosition ||
	m_nRowNumber < nRow ||
	m_nColumnNumber < nColumn)
	{
		std::cerr << "MatrixVector::setElement\tCannot set an element of a matrix "
		<< nPosition << " because that position doesn't exist" << std::endl;
	}
	m_matrVec[nPosition].insert_element(nRow, nColumn, value);
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
void MatrixVector<T>::allocateSize(const unsigned vectorSize, 
const unsigned matrixRowSize,
const unsigned matrixColumSize)
{
	m_matrVec.resize(vectorSize);
	BOOST_FOREACH(boostMatrix& matrix, m_matrVec)
	{
		matrix.resize(matrixRowSize, matrixColumSize);
	}
	m_nRowNumber = matrixRowSize;
	m_nColumnNumber = matrixColumSize;
}

///////////////////////////////////////////////////////////////////////////
//template <typename T>
//void MatrixVector<T>::printMatrix(unsigned nPosition) const
//{
//	for (unsigned i = 0; i < m_nRowNumber; ++i)
//	{
//		for(unsigned j = 0; j < m_nColumnNumber; ++j)
//		{
//			std::cout << m_matrVec[nPosition](i, j) << " ";
//		}
//		std::cout << std::endl;
//	}
//}

#endif // MATRIX_VECTOR_H

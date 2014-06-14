/*
	Symmetries
	Copyright (C) 2014 Mikhail Barenboim <mikelbn@yandex.ru>
	Copyright (C) 2014 Alexey Kuzin <amkuzink@gmail.com>

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

#include "TensorStore.h"
#include "Exceptions.h"

#include <QStringList>

typedef std::map<unsigned, TensorStore::TensorProperties> TensorsMap;

TensorStore::TensorProperties::TensorProperties(QString& sTensorName, MatrixVectorExp& tensor)
{
	m_tensorName = sTensorName;
	m_tensor = tensor;
}

///////////////////////////////////////////////////////////////////////////
QString TensorStore::TensorProperties::getTensorName() const
{
	return m_tensorName;
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp& TensorStore::TensorProperties::getTensor()
{
	return m_tensor;
}

///////////////////////////////////////////////////////////////////////////
TensorStore::TensorStore()
{
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void TensorStore::addTensor(QString sTensorName, MatrixVectorExp& tensor)
{
	static unsigned newTensorIndex = m_tensors.size();
	TensorStore::TensorProperties newTensor(sTensorName, tensor);
	m_tensors.insert(std::make_pair(newTensorIndex++, newTensor));
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp& TensorStore::getTensor(unsigned nIndex)
{
	TensorsMap::iterator it = m_tensors.find(nIndex);
	if (it == m_tensors.end())
	{
		throw guiException("No such tensor");
	}
	return it->second.getTensor();
}

///////////////////////////////////////////////////////////////////////////
MatrixVector<QString> TensorStore::getStringTensor(unsigned nIndex)
{
	TensorsMap::iterator it = m_tensors.find(nIndex);
	if (it == m_tensors.end())
	{
		throw guiException("No such tensor");
	}

	MatrixVectorExp& tensor = it->second.getTensor();
	unsigned matrixRowNumber = tensor.getContent().getMatrixRowSize();
	unsigned matrixColumnNumber = tensor.getContent().getMatrixColumnSize();
	MatrixVector<QString> stringTensor(matrixRowNumber, matrixColumnNumber);

	std::vector<MatrixVectorExp::expBoostMatrix> vec = tensor.getContent().getVector();


	BOOST_FOREACH(MatrixVectorExp::expBoostMatrix& matrix, vec)
	{
		boost::numeric::ublas::matrix<QString> tempMatrix;
		tempMatrix.resize(matrixRowNumber, matrixColumnNumber);
		for(unsigned i = 0; i < matrixRowNumber; i++)
		{
			for(unsigned j = 0; j < matrixColumnNumber; j++)
			{
				tempMatrix(i, j) = QString::fromStdString(matrix(i, j).toString());
			}
		}
		stringTensor.addMatrix(tempMatrix);
	}
	return stringTensor;
}

///////////////////////////////////////////////////////////////////////////
QString TensorStore::getTensorName(unsigned nIndex) const
{
	TensorsMap::const_iterator it = m_tensors.find(nIndex);
	if (it == m_tensors.end())
	{
		throw guiException("No such tensor");
	}
	return it->second.getTensorName();
}

///////////////////////////////////////////////////////////////////////////
QStringList TensorStore::getTensorNames() const
{
	QStringList tensorNames;
	BOOST_FOREACH(const TensorsMap::value_type& tensorItem, m_tensors)
	{
		tensorNames.append(tensorItem.second.getTensorName());
	}
	return tensorNames;
}

///////////////////////////////////////////////////////////////////////////
void TensorStore::removeTensor(unsigned nIndex)
{
	m_tensors.erase(nIndex);
}

///////////////////////////////////////////////////////////////////////////
void TensorStore::removeAllTensors()
{
	m_tensors.clear();
}

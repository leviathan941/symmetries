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
#include "TensorParser.h"

#include <QStringList>

typedef std::map<unsigned, TensorStore::TensorProperties> TensorsMap;

TensorStore& TensorStore::getInstance()
{
	static TensorStore instance;
	return instance;
}

///////////////////////////////////////////////////////////////////////////
TensorStore::TensorProperties::TensorProperties(const QString& sTensorName, MatrixVectorExp& tensor)
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
TensorStore::TensorStore() : QObject()
{
}

///////////////////////////////////////////////////////////////////////////
TensorStore::TensorStore(const TensorStore& otherStore)
{
	m_tensors = otherStore.m_tensors;
}

///////////////////////////////////////////////////////////////////////////
TensorStore& TensorStore::operator=(const TensorStore& otherStore)
{
	if (&otherStore != this)
	{
		m_tensors = otherStore.m_tensors;
	}
	return *this;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void TensorStore::addTensor(const QString& sTensorName, MatrixVector<QString>& stringTensor)
{
	MatrixVectorExp expTensor = TensorParser::fromMatrixVecQStringToMatrixVecExp(stringTensor);
	addTensor(sTensorName, expTensor);
}

///////////////////////////////////////////////////////////////////////////
void TensorStore::addTensor(const QString& sTensorName, MatrixVectorExp& tensor)
{
	QStringList existedNames = getTensorNames();
	if (existedNames.contains(sTensorName))
	{
		throw guiException("There is a matrix with that name. "
			"Please enter another name for the matrix.");
	}

	unsigned newTensorIndex = m_tensors.size();
	TensorStore::TensorProperties newTensor(sTensorName, tensor);
	m_tensors.insert(std::make_pair(newTensorIndex, newTensor));

	emit storeUpdated();
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
	return TensorParser::fromMatrixVecExpToMatrixVecQString(tensor);
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
	int nDeleted = m_tensors.erase(nIndex);
	if (nDeleted)
	{
		emit storeUpdated();
	}
}

///////////////////////////////////////////////////////////////////////////
void TensorStore::removeAllTensors()
{
	bool bUpdated = m_tensors.size();
	m_tensors.clear();
	if (bUpdated)
		emit storeUpdated();
}

///////////////////////////////////////////////////////////////////////////
unsigned TensorStore::size() const
{
	return m_tensors.size();
}

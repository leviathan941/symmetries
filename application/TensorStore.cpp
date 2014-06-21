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

typedef std::map<QString, MatrixVectorExp> TensorsMap;

TensorStore& TensorStore::getInstance()
{
	static TensorStore instance;
	return instance;
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
			"Please rename for the matrix.");
	}

	m_tensors.insert(std::make_pair(sTensorName, tensor));

	emit storeUpdated();
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp& TensorStore::getTensor(const QString& sTensorName)
{
	TensorsMap::iterator it = m_tensors.find(sTensorName);
	if (it == m_tensors.end())
	{
		throw guiException("No such tensor");
	}
	return it->second;
}

///////////////////////////////////////////////////////////////////////////
MatrixVector<QString> TensorStore::getStringTensor(const QString& sTensorName)
{
	TensorsMap::iterator it = m_tensors.find(sTensorName);
	if (it == m_tensors.end())
	{
		throw guiException("No such tensor");
	}

	return TensorParser::fromMatrixVecExpToMatrixVecQString(it->second);
}

///////////////////////////////////////////////////////////////////////////
QStringList TensorStore::getTensorNames() const
{
	QStringList tensorNames;
	BOOST_FOREACH(const TensorsMap::value_type& tensorItem, m_tensors)
	{
		tensorNames.append(tensorItem.first);
	}
	return tensorNames;
}

///////////////////////////////////////////////////////////////////////////
void TensorStore::removeTensor(const QString& sTensorName)
{
	int nDeleted = m_tensors.erase(sTensorName);
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

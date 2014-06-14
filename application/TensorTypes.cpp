/*
	Symmetries
	Copyright (C) 2014 Mikhail Barenboim <mikelbn@yandex.ru>

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

#include "TensorTypes.h"
#include "Exceptions.h"

#include <QString>
#include <QStringList>
#include <utility>
#include <boost/foreach.hpp>

typedef std::map<TensorTypes::TensorType, QString> tensorTypeMap;

tensorTypeMap TensorTypes::m_tensorTypes(TensorTypes::init());

///////////////////////////////////////////////////////////////////////////
QString TensorTypes::getTensorTypeAsString(TensorType type)
{
	tensorTypeMap::iterator typeIter = m_tensorTypes.find(type);
	if(typeIter == m_tensorTypes.end())
	{
		throw guiException("Fatal error. No such tensor type.");
	}
	return typeIter->second;
}

///////////////////////////////////////////////////////////////////////////
QStringList TensorTypes::getAllTypes()
{
	QStringList listStringTypes;

	BOOST_FOREACH(tensorTypeMap::value_type &typePair, m_tensorTypes)
	{
		listStringTypes.append(typePair.second);
	}

	return listStringTypes;
}

///////////////////////////////////////////////////////////////////////////
tensorTypeMap TensorTypes::init()
{
	tensorTypeMap tensorTypes;
	tensorTypes.insert(std::make_pair(METRIC_TENSOR, "Metric tensor"));
	tensorTypes.insert(std::make_pair(TORSION_TENSOR, "Torsion tensor"));
	tensorTypes.insert(std::make_pair(AFFINE_CONNECTION, "Affine Connection"));
	return tensorTypes;
}

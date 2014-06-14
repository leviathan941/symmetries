/*
	Symmetries
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


#include "OperationItems.h"
#include "Exceptions.h"

#include <QStringList>
#include <utility>
#include <boost/foreach.hpp>

typedef std::map<OperationItems::AllowableItem, OperationItems::ItemProperties> OperationItemMap;

OperationItemMap OperationItems::m_operationItems = []()->OperationItemMap
{
	OperationItemMap operationItems;

	std::vector<TensorTypes::TensorType> tempReqTensors;
	tempReqTensors.push_back(TensorTypes::METRIC_TENSOR);
	tempReqTensors.push_back(TensorTypes::TORSION_TENSOR);
	QString operItemName = TensorTypes::getTensorTypeAsString(TensorTypes::AFFINE_CONNECTION);
	OperationItems::ItemProperties affineConn(operItemName, tempReqTensors);
	operationItems.insert(std::make_pair(OperationItems::AFFINE_CONNECTION, affineConn));
	tempReqTensors.clear();

	tempReqTensors.push_back(TensorTypes::AFFINE_CONNECTION);
	OperationItems::ItemProperties affineLieAlgebra(QString("Affine Lie Algebra"), tempReqTensors);
	operationItems.insert(std::make_pair(OperationItems::AFFINE_LIE_ALGEBRA, affineLieAlgebra));
	tempReqTensors.clear();

	return operationItems;
}();

///////////////////////////////////////////////////////////////////////////
QString OperationItems::getStringItemById(AllowableItem itemId)
{
	OperationItemMap::iterator operIter = m_operationItems.find(itemId);
	if (operIter == m_operationItems.end())
	{
		throw coreException("Fatal error. No such item.");
	}
	return operIter->second.getItemName();
}

///////////////////////////////////////////////////////////////////////////
QStringList OperationItems::getAllowableItems()
{
	QStringList operItemsList;
	BOOST_FOREACH(OperationItemMap::value_type& operItem, m_operationItems)
	{
		operItemsList.append(operItem.second.getItemName());
	}
	return operItemsList;
}

///////////////////////////////////////////////////////////////////////////
std::vector<TensorTypes::TensorType> OperationItems::getTensorTypesByItemId(AllowableItem itemId)
{
	OperationItemMap::iterator operIter = m_operationItems.find(itemId);
	if (operIter == m_operationItems.end())
	{
		throw coreException("Fatal error. No such item.");
	}
	return operIter->second.getRequiredTensors();
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
OperationItems::ItemProperties::ItemProperties(QString sItemName,
	std::vector<TensorTypes::TensorType> reqTensors)
: m_itemName(sItemName)
, m_requiredTensors(reqTensors)
{
}

///////////////////////////////////////////////////////////////////////////
QString OperationItems::ItemProperties::getItemName() const
{
	return m_itemName;
}

///////////////////////////////////////////////////////////////////////////
std::vector<TensorTypes::TensorType> OperationItems::ItemProperties::getRequiredTensors() const
{
	return m_requiredTensors;
}

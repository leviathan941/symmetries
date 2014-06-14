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


#ifndef OPERATION_ITEMS_H
#define OPERATION_ITEMS_H

#include "TensorTypes.h"

#include <vector>
#include <map>
#include <QString>

class QStringList;

class OperationItems
{
public:
	OperationItems();

	enum AllowableItem
	{
		AFFINE_CONNECTION,
		AFFINE_LIE_ALGEBRA
	};

	class ItemProperties
	{
	public:
		ItemProperties(QString sItemName, std::vector<TensorTypes::TensorType> reqTensors);
		QString getItemName() const;
		std::vector<TensorTypes::TensorType> getRequiredTensors() const;
	private:
		QString m_itemName;
		std::vector<TensorTypes::TensorType> m_requiredTensors;
	};

	static QString getStringItemById(AllowableItem itemId);
	static QStringList getAllowableItems();
	static std::vector<TensorTypes::TensorType> getTensorTypesByItemId(AllowableItem itemId);

private:
	static std::map<AllowableItem, ItemProperties> m_operationItems;
};

#endif // OPERATION_ITEMS_H

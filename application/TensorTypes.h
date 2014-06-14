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

#ifndef TENSOR_TYPES_H
#define TENSOR_TYPES_H

#include <map>

class QString;
class QStringList;

class TensorTypes
{
public:
	enum TensorType
	{
		METRIC_TENSOR,
		TORSION_TENSOR,
		AFFINE_CONNECTION
	};

	static QString getTensorTypeAsString(TensorType type);
	static QStringList getAllTypes();

private:
	static std::map<TensorType, QString> init();
	static std::map<TensorType, QString> m_tensorTypes;
};

#endif // TENSOR_TYPES_H

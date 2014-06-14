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

#ifndef TENSOR_STORE_H
#define TENSOR_STORE_H

#include "MatrixVectorExp.h"

#include <QString>
#include <map>
#include <boost/noncopyable.hpp>

class TensorStore : public boost::noncopyable
{
public:
	static TensorStore& getInstance()
	{
		static TensorStore instance;
		return instance;
	}
	void addTensor(QString sTensorName, MatrixVectorExp& tensor);
	MatrixVectorExp& getTensor(unsigned nIndex);
	MatrixVector<QString> getStringTensor(unsigned nIndex);
	QString getTensorName(unsigned nIndex) const;
	QStringList getTensorNames() const;
	void removeTensor(unsigned nIndex);
	void removeAllTensors();

	class TensorProperties
	{
	public:
		TensorProperties(QString& sTensorName, MatrixVectorExp& tensor);
		QString getTensorName() const;
		MatrixVectorExp& getTensor();

	private:
		QString m_tensorName;
		MatrixVectorExp m_tensor;
	};

private:
	TensorStore();

	std::map<unsigned, TensorProperties> m_tensors;
};

#endif // TENSOR_STORE_H

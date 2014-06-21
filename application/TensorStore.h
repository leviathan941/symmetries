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
#include <QObject>
#include <map>

class TensorStore : public QObject
{
	Q_OBJECT
public:
	static TensorStore& getInstance();

	void addTensor(const QString& sTensorName, MatrixVectorExp& tensor);
	void addTensor(const QString& sTensorName, MatrixVector<QString>& stringTensor);
	MatrixVectorExp& getTensor(unsigned nIndex);
	MatrixVector<QString> getStringTensor(unsigned nIndex);
	QString getTensorName(unsigned nIndex) const;
	QStringList getTensorNames() const;
	void removeTensor(unsigned nIndex);
	void removeAllTensors();
	unsigned size() const;

	class TensorProperties
	{
	public:
		TensorProperties(const QString& sTensorName, MatrixVectorExp& tensor);
		QString getTensorName() const;
		MatrixVectorExp& getTensor();

	private:
		QString m_tensorName;
		MatrixVectorExp m_tensor;
	};

signals:
	void storeUpdated();

private:
	TensorStore();
	TensorStore(const TensorStore& otherStore);
	TensorStore& operator=(const TensorStore& otherStore);

	std::map<unsigned, TensorProperties> m_tensors;
};

#endif // TENSOR_STORE_H

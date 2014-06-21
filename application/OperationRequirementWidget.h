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


#ifndef OPERATION_REQUIREMENT_WIDGET_H
#define OPERATION_REQUIREMENT_WIDGET_H

#include "TensorTypes.h"

#include <QWidget>
#include <vector>
#include <map>

class QFormLayout;
class QComboBox;

class OperationRequirementWidget : public QWidget
{
	Q_OBJECT
public:
	OperationRequirementWidget(QWidget *parent);

	void addItem(TensorTypes::TensorType tensorType);
	void addItems(std::vector<TensorTypes::TensorType> tensorTypes);
	std::map<TensorTypes::TensorType, QString> getItems();
	void clear();

private:
	QFormLayout* m_mainLayout;

	// map key: tensor type, value: QComboBox
	std::map<TensorTypes::TensorType, QComboBox*> m_calcTensors;

	void clearLayout(QLayout* layout);
	void addRow(TensorTypes::TensorType tensorType);

protected:
	void paintEvent(QPaintEvent* event);

private slots:
	void onReqTensorComBoxActivated(int nIndex);

signals:
	void tensorChoosed(QString sTensorName);
};

#endif // OPERATION_REQUIREMENT_WIDGET_H

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


#include "OperationRequirementWidget.h"
#include "OperationItems.h"
#include "Exceptions.h"
#include "TensorStore.h"

#include <QFormLayout>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <boost/foreach.hpp>

#define MAIN_STYLESHEET\
	"OperationRequirementWidget { border: 1px solid; border-color: #999999;\
	background-color: white; }"

typedef std::map<TensorTypes::TensorType, QComboBox*> ComBoxMap;

OperationRequirementWidget::OperationRequirementWidget(QWidget *parent) :
	QWidget(parent), m_calcTensors()
{
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Ignored);
	setStyleSheet(MAIN_STYLESHEET);

	m_mainLayout = new QFormLayout;
	setLayout(m_mainLayout);
}

///////////////////////////////////////////////////////////////////////////
void OperationRequirementWidget::addItem(TensorTypes::TensorType tensorType)
{
	try
	{
		if (m_calcTensors.find(tensorType) == m_calcTensors.end())
		{
			addRow(tensorType);
		}
	}
	CATCH_CORE
}

///////////////////////////////////////////////////////////////////////////
void OperationRequirementWidget::addItems(std::vector<TensorTypes::TensorType> tensorTypes)
{
	BOOST_FOREACH(TensorTypes::TensorType& type, tensorTypes)
	{
		addItem(type);
	}
}

///////////////////////////////////////////////////////////////////////////
void OperationRequirementWidget::addRow(TensorTypes::TensorType tensorType)
{
	try
	{
		QLabel* tensorLabel = new QLabel(TensorTypes::getTensorTypeAsString(tensorType), this);
		QComboBox* tensorsChoice = new QComboBox(this);

		QStringList tensorNames = TensorStore::getInstance().getTensorNames();
		if (tensorNames.empty())
		{
			throw guiException("You need to add tensors to calculate anything");
		}
		tensorsChoice->addItems(tensorNames);
		tensorsChoice->setCurrentIndex(-1);
		connect(tensorsChoice, SIGNAL(activated(int)), this,
			SLOT(onReqTensorComBoxActivated(int)));

		m_calcTensors.insert(std::make_pair(tensorType, tensorsChoice));

		m_mainLayout->addRow(tensorLabel, tensorsChoice);
	}
	CATCH_GUI("Error")
}

///////////////////////////////////////////////////////////////////////////
std::map<TensorTypes::TensorType, unsigned> OperationRequirementWidget::getItems()
{
	std::map<TensorTypes::TensorType, unsigned> outMap;
	BOOST_FOREACH(ComBoxMap::value_type& reqTensor, m_calcTensors)
	{
		int tensorIndex = reqTensor.second->currentIndex();
		outMap.insert(std::make_pair(reqTensor.first, (tensorIndex < 0) ? 0 : tensorIndex));
	}
	return outMap;
}

///////////////////////////////////////////////////////////////////////////
void OperationRequirementWidget::clear()
{
	clearLayout(m_mainLayout);
	m_calcTensors.clear();
}

///////////////////////////////////////////////////////////////////////////
void OperationRequirementWidget::clearLayout(QLayout* layout)
{
	while (layout->count())
	{
		QLayoutItem* item = layout->takeAt(0);

		if (QWidget* widget = item->widget())
		{
			delete widget;
		}

		if (QLayout* childLayout = item->layout())
		{
			clearLayout(childLayout);
		}

		delete item;
	}
}

///////////////////////////////////////////////////////////////////////////
void OperationRequirementWidget::onReqTensorComBoxActivated(int nIndex)
{
	emit tensorChoosed(nIndex);
}

///////////////////////////////////////////////////////////////////////////
void OperationRequirementWidget::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

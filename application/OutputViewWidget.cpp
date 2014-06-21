/*
	Symmetries
	Copyright (C) 2014 Alexey Kuzin <amkuzink@gmail.com>
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


#include "OutputViewWidget.h"
#include "MatrixViewWidget.h"
#include "TensorStore.h"
#include "TabsWidget.h"

#include <QListWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QStackedLayout>
#include <QPainter>
#include <QTextEdit>

typedef std::map<unsigned, MatrixVectorExp> tensorMap;
typedef std::map<unsigned, QString> resultMap;

#define WIDGET_STYLESHEET\
	"OutputViewWidget {border: 1px solid; border-color: #999999}"

OutputViewWidget::OutputViewWidget(QWidget *parent) :
	QWidget(parent)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	setObjectName("OutputViewWidget");
	setStyleSheet(WIDGET_STYLESHEET);

	m_resultsList = new QListWidget(this);
	m_resultsList->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
	m_resultsList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

	m_removeButton = new QPushButton(this);
	m_removeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_removeButton->setText(tr("Remove"));

	m_addButton = new QPushButton(this);
	m_addButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_addButton->setText(tr("Add"));

	m_textResult = new QTextEdit(this);
	m_textResult->setReadOnly(true);

	m_tensorResult = new TabsWidget(this);

	// For test purpose only
//	MatrixVector<QString> testTensor = TensorStore::getInstance().getStringTensor(0);
//	m_tensorResult->setTensor(testTensor);
//	m_resultsList->addItem("Torsion 1");

	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(m_removeButton);
	buttonLayout->addWidget(m_addButton);
	buttonLayout->setAlignment(Qt::AlignRight);

	m_resultLayout = new QStackedLayout;
	m_resultLayout->addWidget(m_textResult);
	m_resultLayout->addWidget(m_tensorResult);

	QHBoxLayout* listAndResults = new QHBoxLayout;
	listAndResults->addWidget(m_resultsList);
	listAndResults->addLayout(m_resultLayout);

	QVBoxLayout* mainLayout = new QVBoxLayout;

	mainLayout->setContentsMargins(5, 5, 5, 5);
	mainLayout->addLayout(listAndResults);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	connect(m_resultsList, SIGNAL(currentRowChanged(int)), this, SLOT(onCurrentRowChanged(int)));
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::onTensorCalculated(MatrixVectorExp tensor)
{
	unsigned tensorIndex = m_resultsList->count();
	QString tensorName = "Tensor ";

	m_calcTensors.insert(std::make_pair(tensorIndex, tensor));

	tensorName.append(QString::number(m_calcTensors.size()));
	m_resultsList->addItem(tensorName);
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::onOtherCalculated(QString result)
{
	unsigned resultIndex = m_resultsList->count();
	QString resultName = "Result ";

	m_calcResults.insert(std::make_pair(resultIndex, result));

	resultName.append(QString::number(m_calcResults.size()));
	m_resultsList->addItem(resultName);
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::onCurrentRowChanged(int index)
{
	for(tensorMap::iterator tensorIt = m_calcTensors.begin(); tensorIt != m_calcTensors.end(); tensorIt++)
	{
		if(tensorIt->first == index)
		{
			m_resultLayout->setCurrentWidget(m_tensorResult);
			return;
		}
	}

	for(resultMap::iterator resultIt = m_calcResults.begin(); resultIt != m_calcResults.end(); resultIt++)
	{
		if(resultIt->first == index)
		{
			m_resultLayout->setCurrentWidget(m_textResult);
			return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

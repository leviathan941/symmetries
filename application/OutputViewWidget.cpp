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
#include "TensorParser.h"
#include "Exceptions.h"

#include <QListWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QStackedLayout>
#include <QPainter>
#include <QTextEdit>
#include <QDebug>
#include <QMessageBox>

#define MAIN_MARGIN 5

typedef std::map<QString, MatrixVectorExp> tensorMap;
typedef std::map<QString, QString> resultMap;

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
	m_removeButton->setEnabled(false);

	m_addButton = new QPushButton(this);
	m_addButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_addButton->setText(tr("Add"));
	m_addButton->setEnabled(false);

	m_textResult = new QTextEdit(this);
	m_textResult->setReadOnly(true);

	m_tensorResult = new TabsWidget(this);

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

	mainLayout->setContentsMargins(MAIN_MARGIN, MAIN_MARGIN, MAIN_MARGIN, MAIN_MARGIN);
	mainLayout->addLayout(listAndResults);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);

	connect(m_resultsList, SIGNAL(currentRowChanged(int)), this, SLOT(onCurrentRowChanged(int)));
	connect(m_removeButton, SIGNAL(clicked()), this, SLOT(onRemoveButtonClicked()));
	connect(m_addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::onTensorCalculated(MatrixVectorExp tensor)
{
	QString tensorName = "Tensor ";
	unsigned tensorNumber = m_calcTensors.size() + 1;
	tensorName.append(QString::number(tensorNumber));

	m_calcTensors.insert(std::make_pair(tensorName, tensor));

	m_resultsList->addItem(tensorName);
	m_removeButton->setEnabled(true);
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::onOtherCalculated(QString result)
{
	QString resultName = "Result ";
	unsigned resultNumber = m_calcResults.size() + 1;
	resultName.append(QString::number(resultNumber));

	m_calcResults.insert(std::make_pair(resultName, result));

	m_resultsList->addItem(resultName);
	m_removeButton->setEnabled(true);
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::onCurrentRowChanged(int nIndex)
{
	QListWidgetItem* resultListItem = m_resultsList->item(nIndex);
	if(resultListItem == NULL)
	{
		return;
	}

	tensorMap::iterator tensorIt = m_calcTensors.find(resultListItem->text());
	if(tensorIt != m_calcTensors.end())
	{
		m_addButton->setEnabled(true);
		m_resultLayout->setCurrentWidget(m_tensorResult);
		m_tensorResult->
			setTensor(TensorParser::fromMatrixVecExpToMatrixVecQString(tensorIt->second));
		return;
	}
	else
	{
		resultMap::iterator resultIt = m_calcResults.find(resultListItem->text());
		if(resultIt != m_calcResults.end())
		{
			m_addButton->setEnabled(false);
			m_resultLayout->setCurrentWidget(m_textResult);
			m_textResult->setText(resultIt->second);
			return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::onRemoveButtonClicked()
{
	QListWidgetItem* resultListItem = m_resultsList->item(m_resultsList->currentRow());
	if(resultListItem == NULL)
	{
		qDebug() << "onRemoveButtonClicked There is no such item to remove";
		return;
	}

	tensorMap::iterator tensorIt = m_calcTensors.find(resultListItem->text());
	if(tensorIt != m_calcTensors.end())
	{
		m_calcTensors.erase(tensorIt->first);
		m_resultsList->removeItemWidget(resultListItem);
	}
	else
	{
		resultMap::iterator resultIt = m_calcResults.find(resultListItem->text());
		if(resultIt != m_calcResults.end())
		{
			m_calcResults.erase(resultIt->first);
			m_resultsList->removeItemWidget(resultListItem);
		}
	}
	m_resultsList->takeItem(m_resultsList->currentRow());

	m_tensorResult->clear();
	m_textResult->clear();

	if(m_resultsList->count() == 0)
	{
		m_removeButton->setEnabled(false);
	}
	else
	{
		onCurrentRowChanged(m_resultsList->currentRow());
	}
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::onAddButtonClicked()
{
	int listItemIndex = m_resultsList->currentRow();
	QListWidgetItem* resultListItem = m_resultsList->item(listItemIndex);
	if(resultListItem == NULL)
	{
		qDebug() << "onAddButtonClicked There is no such item to add";
		return;
	}

	tensorMap::iterator tensorIt = m_calcTensors.find(resultListItem->text());
	if(tensorIt != m_calcTensors.end())
	{
		try
		{
			TensorStore::getInstance().addTensor(tensorIt->first, tensorIt->second);
		}
		CATCH_GUI("Error")
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

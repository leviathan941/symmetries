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


#include "CalculateWindow.h"
#include "OperationItems.h"
#include "OperationRequirementWidget.h"
#include "TabsWidget.h"
#include "Exceptions.h"

#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

#define MINIMUM_WIDTH 500
#define MINIMUM_HEIGHT 400
#define MARGIN_LEFT_TOP_RIGHT 10

CalculateWindow::CalculateWindow(QWidget *parent) :
	QDialog(parent)
{
	setWindowTitle(tr("Calculate"));
	setMinimumSize(QSize(MINIMUM_WIDTH, MINIMUM_HEIGHT));

	m_comBoxCalcItem = new QComboBox(this);
	m_comBoxCalcItem->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	m_comBoxCalcItem->addItems(OperationItems::getAllowableItems());
	m_calcReqWidget = new OperationRequirementWidget(this);
	QVBoxLayout* calcListLayout = new QVBoxLayout;
	calcListLayout->addWidget(m_comBoxCalcItem, 0, Qt::AlignTop);
	calcListLayout->addWidget(m_calcReqWidget, 1);

	m_tensorView = new TabsWidget(this);

	QHBoxLayout* listAndTensorViewLayout = new QHBoxLayout;
	listAndTensorViewLayout->addLayout(calcListLayout, 0);
	listAndTensorViewLayout->addWidget(m_tensorView, 1);

	m_pushBtnOk = new QPushButton(tr("OK"), this);
	m_pushBtnOk->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_pushBtnCancel = new QPushButton(tr("Cancel"), this);
	m_pushBtnCancel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	QHBoxLayout* okCancelLayout = new QHBoxLayout;
	okCancelLayout->addWidget(m_pushBtnOk, 1, Qt::AlignRight);
	okCancelLayout->addWidget(m_pushBtnCancel, 0, Qt::AlignRight);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(listAndTensorViewLayout);
	mainLayout->addLayout(okCancelLayout);
	mainLayout->setContentsMargins(MARGIN_LEFT_TOP_RIGHT, MARGIN_LEFT_TOP_RIGHT,
		MARGIN_LEFT_TOP_RIGHT, 0);

	setLayout(mainLayout);

	connect(m_pushBtnOk, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
	connect(m_pushBtnCancel, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
	connect(m_comBoxCalcItem, SIGNAL(currentIndexChanged(int)), this,
		SLOT(onCalcItemCurrentIndexChanged(int)));
	connect(m_calcReqWidget, SIGNAL(tensorChoosed(int)), this,
		SLOT(onReqWidgetTensorChoosed(int)));

	onCalcItemCurrentIndexChanged(0);
}

///////////////////////////////////////////////////////////////////////////
void CalculateWindow::onOkButtonClicked()
{
	// TODO Add start calculating here.
}

///////////////////////////////////////////////////////////////////////////
void CalculateWindow::onCancelButtonClicked()
{
	close();
}

///////////////////////////////////////////////////////////////////////////
void CalculateWindow::onCalcItemCurrentIndexChanged(int nIndex)
{
	m_calcReqWidget->clear();

	try
	{
		std::vector<TensorTypes::TensorType> reqTensors
			= OperationItems::getTensorTypesByItemId((OperationItems::AllowableItem) nIndex);
		m_calcReqWidget->addItems(reqTensors);
	}
	CATCH_CORE
}

///////////////////////////////////////////////////////////////////////////
void CalculateWindow::onReqWidgetTensorChoosed(int nTensorIndex)
{
	// TODO show tensor from the store in TabsWidget.
}

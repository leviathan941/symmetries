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
#include "TabsWidget.h"
#include "TensorStore.h"

#include <QListWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QPainter>

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

	// For test purpose only
	//TabsWidget* tabs = new TabsWidget(this);
	//MatrixVector<QString> testTensor = TensorStore::getInstance().getStringTensor(0);
	//tabs->setTensor(testTensor);
	//m_resultsList->addItem("Torsion 1");

	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(m_removeButton);
	buttonLayout->addWidget(m_addButton);
	buttonLayout->setAlignment(Qt::AlignRight);

	QHBoxLayout* listAndTabs = new QHBoxLayout;
	listAndTabs->addWidget(m_resultsList);
	//listAndTabs->addWidget(tabs);

	QVBoxLayout* mainLayout = new QVBoxLayout;

	mainLayout->setContentsMargins(5, 5, 5, 5);
	mainLayout->addLayout(listAndTabs);
	mainLayout->addLayout(buttonLayout);
	setLayout(mainLayout);
}

///////////////////////////////////////////////////////////////////////////
void OutputViewWidget::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

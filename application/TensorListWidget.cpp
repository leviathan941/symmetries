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


#include "TensorListWidget.h"
#include "TensorPropWindow.h"

#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#define BUTTON_WIDTH 24
#define BUTTON_HEIGHT 24
#define WIDGET_VERTICAL_SPACING 5
#ifdef __APPLE__
#define BUTTONS_HORIZONTAL_SPACING 12
#else
#define BUTTONS_HORIZONTAL_SPACING 0
#endif

TensorListWidget::TensorListWidget(QWidget *parent) :
	QWidget(parent)
{
	m_tensorList = new QListWidget(this);

	m_pushBtnAddTensor = new QPushButton(this);
	m_pushBtnAddTensor->setIcon(QIcon(":/icons/plus.png"));
	m_pushBtnAddTensor->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

	m_pushBtnRemoveTensor = new QPushButton(this);
	m_pushBtnRemoveTensor->setIcon(QIcon(":/icons/minus.png"));
	m_pushBtnRemoveTensor->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));

	QHBoxLayout* addRemoveLayout = new QHBoxLayout;
	addRemoveLayout->addWidget(m_pushBtnAddTensor);
	addRemoveLayout->addWidget(m_pushBtnRemoveTensor);
	addRemoveLayout->setAlignment(Qt::AlignLeft);
	addRemoveLayout->setSpacing(BUTTONS_HORIZONTAL_SPACING);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(m_tensorList);
	mainLayout->addLayout(addRemoveLayout);
	mainLayout->setSpacing(WIDGET_VERTICAL_SPACING);
	mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(mainLayout);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
	setObjectName(QString("TensorListWidget"));
	setContentsMargins(0, 0, 0, 0);

	connect(m_pushBtnAddTensor, SIGNAL(clicked()), this, SLOT(onAddTensorButtonClicked()));
	connect(m_pushBtnRemoveTensor, SIGNAL(clicked()), this, SLOT(onRemoveTensorButtonClicked()));
}

///////////////////////////////////////////////////////////////////////////
void TensorListWidget::onAddTensorButtonClicked()
{
	TensorPropWindow tensorWindow(this);
	tensorWindow.exec();
}

///////////////////////////////////////////////////////////////////////////
void TensorListWidget::onRemoveTensorButtonClicked()
{
	// Placeholder
}

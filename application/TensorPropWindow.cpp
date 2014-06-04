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


#include "TensorPropWindow.h"

#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QFormLayout>

#define MINIMUM_WIDTH 300
#define MINIMUM_HEIGHT 150
#define BUTTON_WIDTH 60
#define BUTTON_HEIGHT 30
#define TYPE_LABEL_WIDTH 75
#define TYPE_LABEL_HEIGHT 30
#define TYPE_COMBOBOX_WIDTH 200
#define TYPE_COMBOBOX_HEIGHT 30
#define DIMENSION_LABEL_WIDTH 75
#define DIMENSION_LABEL_HEIGHT 30
#define DIMENSION_SPINBOX_WIDTH 60
#define DIMENSION_SPINBOX_HEIGHT 30

TensorPropWindow::TensorPropWindow(QWidget *parent) :
	QDialog(parent)
{
	setWindowTitle(tr("Tensor properties"));
	setFixedSize(MINIMUM_WIDTH, MINIMUM_HEIGHT);

	m_typeLabel = new QLabel(this);
	m_typeLabel->setFixedSize(QSize(TYPE_LABEL_WIDTH, TYPE_LABEL_HEIGHT));
	m_typeLabel->setText(tr("Type"));

	m_typeComBox = new QComboBox(this);
	m_typeComBox->setFixedSize(QSize(TYPE_COMBOBOX_WIDTH, TYPE_COMBOBOX_HEIGHT));
	m_typeComBox->addItem(tr("Torsion tensor"));
	m_typeComBox->addItem(tr("Metric tensor"));

	m_dimLabel = new QLabel(this);
	m_dimLabel->setFixedSize(QSize(DIMENSION_LABEL_WIDTH, DIMENSION_LABEL_HEIGHT));
	m_dimLabel->setText(tr("Dimension"));

	m_dimSpinBox = new QSpinBox(this);
	m_dimSpinBox->setFixedSize(QSize(DIMENSION_SPINBOX_WIDTH, DIMENSION_SPINBOX_HEIGHT));
	m_dimSpinBox->setRange(1, 100);
	m_dimSpinBox->setSingleStep(1);
	m_dimSpinBox->setValue(1);

	m_okButton = new QPushButton(this);
	m_okButton->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_okButton->setText(tr("OK"));

	m_cancelButton = new QPushButton(this);
	m_cancelButton->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
	m_cancelButton->setText(tr("Cancel"));

	QFormLayout* mainFormLayout = new QFormLayout;
	mainFormLayout->addRow(m_typeLabel, m_typeComBox);
	mainFormLayout->addRow(m_dimLabel, m_dimSpinBox);

	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(m_okButton);
	buttonLayout->addWidget(m_cancelButton);
	buttonLayout->setAlignment(Qt::AlignRight);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(mainFormLayout);
	mainLayout->addLayout(buttonLayout);

	this->setLayout(mainLayout);

	connect(m_okButton, SIGNAL(clicked()), this, SLOT(onOkClicked()));
	connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}

///////////////////////////////////////////////////////////////////////////
void TensorPropWindow::onOkClicked()
{
	// Placeholder
}

///////////////////////////////////////////////////////////////////////////
void TensorPropWindow::onCancelClicked()
{
	close();
}

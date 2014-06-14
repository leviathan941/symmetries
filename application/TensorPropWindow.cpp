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
#include "TensorTypes.h"
#include "ImportTensorWindow.h"

#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QFormLayout>

#define SPIN_BOX_MAX_VALUE 100
#define SPIN_BOX_MIN_VALUE 1

TensorPropWindow::TensorPropWindow(QWidget *parent) :
	QDialog(parent)
{
	setWindowTitle(tr("Tensor properties"));

	m_typeLabel = new QLabel(this);
	m_typeLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_typeLabel->setText(tr("Type"));

	m_typeComBox = new QComboBox(this);
	m_typeComBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
	m_typeComBox->addItems(TensorTypes::getAllTypes());

	m_dimLabel = new QLabel(this);
	m_dimLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_dimLabel->setText(tr("Dimension"));

	m_dimSpinBox = new QSpinBox(this);
	m_dimSpinBox->setRange(SPIN_BOX_MIN_VALUE, SPIN_BOX_MAX_VALUE);
	m_dimSpinBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	m_okButton = new QPushButton(this);
	m_okButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_okButton->setText(tr("OK"));

	m_cancelButton = new QPushButton(this);
	m_cancelButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
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
	int dimension = m_dimSpinBox->value();
	ImportTensorWindow importTensorWindow(this, dimension);
	importTensorWindow.exec();
}

///////////////////////////////////////////////////////////////////////////
void TensorPropWindow::onCancelClicked()
{
	TensorPropWindow::close();
}

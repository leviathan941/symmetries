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

#include "ImportTensorWindow.h"
#include "TabsWidget.h"
#include "MatrixViewWidget.h"

#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>

ImportTensorWindow::ImportTensorWindow(QWidget *parent, int dimension) :
	QDialog(parent)
{
	setWindowTitle(tr("Enter the tensor"));

	m_nameLabel = new QLabel(this);
	m_nameLabel->setText(tr("Enter the name:"));

	m_nameLine = new QLineEdit(this);
	m_nameLine->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

	m_importButton = new QPushButton(this);
	m_importButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_importButton->setText(tr("Import"));
	m_importButton->setVisible(false);

	m_okButton = new QPushButton(this);
	m_okButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_okButton->setText(tr("OK"));

	m_cancelButton = new QPushButton(this);
	m_cancelButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	m_cancelButton->setText(tr("Cancel"));

	TabsWidget* inputTabs = new TabsWidget(this);
	QString matrixName = "";
	int matrixNumber = 1;

	while(matrixNumber < dimension + 1)
	{
		matrixName.append("matrix");
		matrixName.append(QString(" %1").arg(matrixNumber));
		inputTabs->addTab(new MatrixViewWidget(dimension, dimension), matrixName);
		matrixName.clear();
		matrixNumber++;
	}

	QFormLayout* nameLayout = new QFormLayout;
	nameLayout->addRow(m_nameLabel, m_nameLine);

	QHBoxLayout* importLayout = new QHBoxLayout;
	importLayout->addWidget(m_importButton);
	importLayout->setAlignment(Qt::AlignLeft);

	QHBoxLayout* okCancelLayout = new QHBoxLayout;
	okCancelLayout->addWidget(m_okButton);
	okCancelLayout->addWidget(m_cancelButton);
	okCancelLayout->setAlignment(Qt::AlignRight);

	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->addLayout(importLayout);
	buttonLayout->addLayout(okCancelLayout);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(nameLayout);
	mainLayout->addWidget(inputTabs);
	mainLayout->addLayout(buttonLayout);

	this->setLayout(mainLayout);

	connect(m_importButton, SIGNAL(clicked()), this, SLOT(onImportClicked()));
	connect(m_okButton, SIGNAL(clicked()), this, SLOT(onOkClicked()));
	connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(onCancelClicked()));
}

///////////////////////////////////////////////////////////////////////////
void ImportTensorWindow::onImportClicked()
{
	// Placeholder
}

///////////////////////////////////////////////////////////////////////////
void ImportTensorWindow::onOkClicked()
{
	// Placeholder
}

///////////////////////////////////////////////////////////////////////////
void ImportTensorWindow::onCancelClicked()
{
	ImportTensorWindow::close();
	parentWidget()->close();
}

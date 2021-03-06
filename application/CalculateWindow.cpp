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
#include "TensorStore.h"
#include "Calculation.h"
#include "AffineLieAlgebra.h"

#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>

#define MINIMUM_WIDTH 640
#define MINIMUM_HEIGHT 480
#define CONTENT_MARGIN 10
#define HORIZ_SPACING 5

CalculateWindow::CalculateWindow(QWidget *parent) :
	QDialog(parent)
{
	if (!TensorStore::getInstance().size())
	{
		throw guiException("You have to add at least one tensor to start a calculation.");
	}
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
	m_tensorView->setReadOnly(true);

	QHBoxLayout* listAndTensorViewLayout = new QHBoxLayout;
	listAndTensorViewLayout->setSpacing(HORIZ_SPACING);
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
	mainLayout->setContentsMargins(CONTENT_MARGIN, CONTENT_MARGIN, CONTENT_MARGIN, CONTENT_MARGIN);

	setLayout(mainLayout);

	qRegisterMetaType<MatrixVectorExp>("MatrixVectorExp");

	connect(m_pushBtnOk, SIGNAL(clicked()), this, SLOT(onOkButtonClicked()));
	connect(m_pushBtnCancel, SIGNAL(clicked()), this, SLOT(onCancelButtonClicked()));
	connect(m_comBoxCalcItem, SIGNAL(currentIndexChanged(int)), this,
		SLOT(onCalcItemCurrentIndexChanged(int)));
	connect(m_calcReqWidget, SIGNAL(tensorChoosed(QString)), this,
		SLOT(onReqWidgetTensorChosen(QString)));

	onCalcItemCurrentIndexChanged(0);
}

///////////////////////////////////////////////////////////////////////////
void CalculateWindow::calculateAffineConnection()
{
	std::map<TensorTypes::TensorType, QString> chosenTensors = m_calcReqWidget->getItems();

	std::map<TensorTypes::TensorType, QString>::iterator iter = chosenTensors.find(
		TensorTypes::METRIC_TENSOR);
	if (iter == chosenTensors.end())
	{
		throw guiException("Metric tensor has not been chosen.");
	}
	QString metricTensorName = iter->second;

	iter = chosenTensors.find(TensorTypes::TORSION_TENSOR);
	if (iter == chosenTensors.end())
	{
		throw guiException("Torsion tensor has not been chosen.");
	}
	QString torsionTensorName = iter->second;

	MatrixVectorExp metricTensor = TensorStore::getInstance().getTensor(metricTensorName);
	MatrixVectorExp torsionTensor = TensorStore::getInstance().getTensor(torsionTensorName);
	MatrixVectorExp christoffelSymbols;
	try
	{
		christoffelSymbols = Calculation::calculateAffineConnection(metricTensor, torsionTensor);
	}
	catch (coreException& e)
	{
		throw guiException(e.what());
	}

	emit connectionCalculated(christoffelSymbols);
}

///////////////////////////////////////////////////////////////////////////
void CalculateWindow::buildAffineLieAlgebra()
{
	std::map<TensorTypes::TensorType, QString> chosenTensors = m_calcReqWidget->getItems();
	std::map<TensorTypes::TensorType, QString>::iterator iter = chosenTensors.find(
		TensorTypes::AFFINE_CONNECTION);
	if (iter == chosenTensors.end())
	{
		throw guiException("Affine connection has not been chosen.");
	}
	QString affineConnectionName = iter->second;

	MatrixVectorExp affineConnection = TensorStore::getInstance().getTensor(affineConnectionName);

	AffineLieAlgebra lieAlgebra = Calculation::buildAffineLieAlgebra(affineConnection);
	std::string lieAlgebraAsString = lieAlgebra.toString();
	emit lieAlgebraBuilt(QString::fromStdString(lieAlgebraAsString));
}

///////////////////////////////////////////////////////////////////////////
void CalculateWindow::onOkButtonClicked()
{
	try
	{
		switch ((OperationItems::AllowableItem) m_comBoxCalcItem->currentIndex())
		{
			case OperationItems::AFFINE_CONNECTION:
				calculateAffineConnection();
				close();
				break;

			case OperationItems::AFFINE_LIE_ALGEBRA:
				buildAffineLieAlgebra();
				close();
				break;

			default:
				throw guiException("Operation item has not been chosen.");
				break;
		}
	}
	CATCH_GUI("Error")
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
	CATCH_GUI("Error")
}

///////////////////////////////////////////////////////////////////////////
void CalculateWindow::onReqWidgetTensorChosen(QString sTensorName)
{
	if (sTensorName < 0)
		return;

	MatrixVector<QString> tensor = TensorStore::getInstance().getStringTensor(sTensorName);
	m_tensorView->setTensor(tensor);
}

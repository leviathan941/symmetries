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


#include "MatrixViewWidget.h"
#include "MatrixElementWidget.h"
#include "Exceptions.h"

#include <QGridLayout>

typedef boost::numeric::ublas::matrix<std::string> stringMatrix;

MatrixViewWidget::MatrixViewWidget(unsigned nRowNumber, unsigned nColumnNumber, QWidget *parent) :
	QScrollArea(parent)
{
	QWidget* centralWidget = new QWidget(this); // central widget for scroll area.
	m_gridLayout = new QGridLayout;
	m_gridLayout->setSpacing(0);
	m_gridLayout->setHorizontalSpacing(0);

	for (unsigned i = 0; i < nRowNumber; ++i)
	{
		for (unsigned j = 0; j < nColumnNumber; ++j)
		{
			QString elementIndex = makeStringIndex(i, j);
			MatrixElementWidget* element = new MatrixElementWidget(centralWidget, elementIndex, QString(""));

			m_gridLayout->addWidget(element, i, j);
		}
	}

	centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	centralWidget->setLayout(m_gridLayout);

	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setWidget(centralWidget);
}

///////////////////////////////////////////////////////////////////////////
void MatrixViewWidget::setMatrix(stringMatrix matrix)
{
	if (matrix.size1() != m_gridLayout->rowCount()
		|| matrix.size2() != m_gridLayout->columnCount())
	{
		throw coreException("The matrix size must be equal to widget size.");
	}

	for (int i = 0; i < matrix.size1(); ++i)
	{
		for (int j = 0; j < matrix.size2(); ++j)
		{
			MatrixElementWidget* element = static_cast<MatrixElementWidget*>
				(m_gridLayout->itemAtPosition(i, j)->widget());
			element->setElement(QString::fromStdString(matrix(i, j).c_str()));
		}
	}
}

///////////////////////////////////////////////////////////////////////////
stringMatrix MatrixViewWidget::getMatrix() const
{
	stringMatrix matrix;
	matrix.resize(m_gridLayout->rowCount(), m_gridLayout->columnCount());

	for (int i = 0; i < m_gridLayout->rowCount(); ++i)
	{
		for (int j = 0; m_gridLayout->columnCount(); ++j)
		{
			MatrixElementWidget* element = static_cast<MatrixElementWidget*>
				(m_gridLayout->itemAtPosition(i, j)->widget());
			std::string elementString = element->getElement().toStdString();
			matrix.insert_element(i, j, elementString);
		}
	}

	return matrix;
}

///////////////////////////////////////////////////////////////////////////
QString MatrixViewWidget::makeStringIndex(unsigned nRow, unsigned nColumn)
{
	QString indexBuffer = "(" + QString::number(nRow) + ","
		+ QString::number(nColumn) + ")";
	return indexBuffer;
}

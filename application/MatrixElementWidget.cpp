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


#include "MatrixElementWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>

#define ELEMENT_EDIT_MINIMUM_WIDTH 50
#define CONTENT_MARGIN 5
#define CONTENT_RIGHT_MARGIN 10

MatrixElementWidget::MatrixElementWidget(QWidget *parent) :
	QWidget(parent)
{
	m_labelIndex = new QLabel(this);
	m_editElement = new QLineEdit(this);
	m_editElement->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	m_editElement->setFixedWidth(ELEMENT_EDIT_MINIMUM_WIDTH);

	QFormLayout* mainLayout = new QFormLayout;
	mainLayout->addRow(m_labelIndex, m_editElement);
	mainLayout->setFormAlignment(Qt::AlignRight);
	mainLayout->setContentsMargins(CONTENT_MARGIN, CONTENT_MARGIN, CONTENT_RIGHT_MARGIN,
		CONTENT_MARGIN);
	setLayout(mainLayout);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

///////////////////////////////////////////////////////////////////////////
MatrixElementWidget::MatrixElementWidget(QWidget *parent, const QString &sElementIndex,
	const QString &sElement) : MatrixElementWidget(parent)
{
	m_labelIndex->setText(sElementIndex);
	m_editElement->setText(sElement);
}

///////////////////////////////////////////////////////////////////////////
void MatrixElementWidget::setElementIndex(const QString& sElementIndex)
{
	m_labelIndex->setText(sElementIndex);
}
///////////////////////////////////////////////////////////////////////////
QString MatrixElementWidget::getElementIndex() const
{
	return m_labelIndex->text();
}

///////////////////////////////////////////////////////////////////////////
void MatrixElementWidget::setElement(const QString &sElement)
{
	m_editElement->setText(sElement);
}

///////////////////////////////////////////////////////////////////////////
QString MatrixElementWidget::getElement() const
{
	return m_editElement->text();
}

///////////////////////////////////////////////////////////////////////////
void MatrixElementWidget::setReadOnly(bool bEnable)
{
	m_editElement->setReadOnly(bEnable);
}

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

#include "TabsWidget.h"
#include "MatrixViewWidget.h"

#include <vector>
#include <boost/foreach.hpp>

TabsWidget::TabsWidget(QWidget *parent)
	: m_isReadOnly(false)
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

///////////////////////////////////////////////////////////////////////////
void TabsWidget::addMatrix(boost::numeric::ublas::matrix<QString> &matrix, const QString &tabName)
{
	MatrixViewWidget* matrixView = new MatrixViewWidget(matrix.size1(), matrix.size2(), this);
	matrixView->setReadOnly(m_isReadOnly);
	matrixView->setMatrix(matrix);
	addTab(matrixView, tabName);
}

///////////////////////////////////////////////////////////////////////////
void TabsWidget::setTensor(MatrixVector<QString> tensor)
{
	removeAll();

	std::vector<boost::numeric::ublas::matrix<QString> > vecMatr = tensor.getVector();
	int matrNumber = 0;
	BOOST_FOREACH(boost::numeric::ublas::matrix<QString>& matrix, vecMatr)
	{
		QString matrixName("matrix ");
		matrixName.append(QString::number(++matrNumber));
		addMatrix(matrix, matrixName);
	}
}

///////////////////////////////////////////////////////////////////////////
void TabsWidget::removeAll()
{
	for(int i = count(); i >= 0 && count() > 0; --i)
	{
		delete widget(i);
		QTabWidget::removeTab(i);
	}
}

///////////////////////////////////////////////////////////////////////////
void TabsWidget::setReadOnly(bool bEnable)
{
	m_isReadOnly = bEnable;
	for (int i = 0; i < count(); ++i)
	{
		MatrixViewWidget* matrixView = qobject_cast<MatrixViewWidget*>(widget(i));
		if (matrixView)
		{
			matrixView->setReadOnly(bEnable);
		}
	}
}

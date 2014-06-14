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

#ifndef TABS_WIDGET_H
#define TABS_WIDGET_H

#include "MatrixVectorExp.h"

#include <QTabWidget>

class TabsWidget : public QTabWidget
{
	Q_OBJECT
public:
	explicit TabsWidget(QWidget *parent);

	void addMatrix(boost::numeric::ublas::matrix<QString>& matrix, const QString& tabName);
	void setTensor(MatrixVector<QString> tensor);
	void removeAll();

private:
	QTabWidget *m_outputTabs;
};

#endif // TABS_WIDGET_H

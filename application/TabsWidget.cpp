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

#include "TabsWidget.h"

#include <QStackedLayout>

TabsWidget::TabsWidget(QWidget *parent)
{
	QStackedLayout* mainLayout = new QStackedLayout;
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	setLayout(mainLayout);
}

///////////////////////////////////////////////////////////////////////////
void TabsWidget::add(QWidget *widget, QString tabName)
{
	QTabWidget::addTab(widget, tabName);
}

///////////////////////////////////////////////////////////////////////////
void TabsWidget::remove(int tabNumber)
{
	QTabWidget::removeTab(tabNumber);
}

///////////////////////////////////////////////////////////////////////////
void TabsWidget::removeAll()
{
	for(int i = QTabWidget::count(); i > -1; --i)
	{
		delete widget(i);
		QTabWidget::removeTab(i);
	}
}

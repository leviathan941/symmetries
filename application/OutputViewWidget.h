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


#ifndef OUTPUT_VIEW_WIDGET_H
#define OUTPUT_VIEW_WIDGET_H

#include "MatrixVectorExp.h"

#include <QWidget>

class TabsWidget;
class QListWidget;
class QPushButton;
class QTextEdit;
class QStackedLayout;

class OutputViewWidget : public QWidget
{
	Q_OBJECT
public:
	explicit OutputViewWidget(QWidget *parent = 0);

public slots:
	void onTensorCalculated(MatrixVectorExp tensor);
	void onOtherCalculated(QString result);
	void onCurrentRowChanged(int nIndex);
	void onRemoveButtonClicked();
	void onAddButtonClicked();

private:
	QListWidget* m_resultsList;
	QPushButton* m_removeButton;
	QPushButton* m_addButton;
	TabsWidget* m_tensorResult;
	QTextEdit* m_textResult;
	QStackedLayout* m_resultLayout;

	std::map<QString, MatrixVectorExp> m_calcTensors;
	std::map<QString, QString> m_calcResults;

protected:
	void paintEvent(QPaintEvent* event);
};

#endif // OUTPUT_VIEW_WIDGET_H

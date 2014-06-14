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


#ifndef CALCULATE_WINDOW_H
#define CALCULATE_WINDOW_H

#include <QDialog>

class QComboBox;
class QTextEdit;
class QPushButton;
class QListWidget;
class OperationRequirementWidget;
class TabsWidget;

class CalculateWindow : public QDialog
{
	Q_OBJECT
public:
	explicit CalculateWindow(QWidget *parent = 0);

private:
	QComboBox* m_comBoxCalcItem;
	QPushButton* m_pushBtnOk;
	QPushButton* m_pushBtnCancel;
	OperationRequirementWidget* m_calcReqWidget;
	TabsWidget* m_tensorView;

private slots:
	void onOkButtonClicked();
	void onCancelButtonClicked();
	void onCalcItemCurrentIndexChanged(int nIndex);
	void onReqWidgetTensorChoosed(int nTensorIndex);
};

#endif // CALCULATE_WINDOW_H

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


#ifndef TENSOR_PROP_WINDOW_H
#define TENSOR_PROP_WINDOW_H

#include <QDialog>

class QLabel;
class QPushButton;
class QComboBox;
class QSpinBox;

class TensorPropWindow : public QDialog
{
	Q_OBJECT
public:
	explicit TensorPropWindow(QWidget *parent);

private:
	QPushButton* m_okButton;
	QPushButton* m_cancelButton;
	QLabel* m_typeLabel;
	QLabel* m_dimLabel;
	QComboBox* m_typeComBox;
	QSpinBox* m_dimSpinBox;

private slots:
	void onOkClicked();
	void onCancelClicked();
};

#endif // TENSOR_PROP_WINDOW_H

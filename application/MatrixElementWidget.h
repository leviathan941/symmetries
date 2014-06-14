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


#ifndef MATRIX_ELEMENT_WIDGET_H
#define MATRIX_ELEMENT_WIDGET_H

#include <QWidget>

class QLabel;
class QLineEdit;

class MatrixElementWidget : public QWidget
{
	Q_OBJECT
public:
	MatrixElementWidget(QWidget *parent = 0);
	MatrixElementWidget(QWidget *parent, const QString& sElementIndex, const QString& sElement);

	void setElementIndex(const QString& sElementIndex);
	QString getElementIndex() const;
	void setElement(const QString& sElement);
	QString getElement() const;

	void setReadOnly(bool bEnable);

private:
	QLabel* m_labelIndex;
	QLineEdit* m_editElement;
};

#endif // MATRIX_ELEMENT_WIDGET_H

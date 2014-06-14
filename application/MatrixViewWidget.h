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


#ifndef MATRIX_VIEW_WIDGET_H
#define MATRIX_VIEW_WIDGET_H

#include <boost/numeric/ublas/matrix.hpp>
#include <string>

#include <QScrollArea>
#include <QString>

class QGridLayout;

class MatrixViewWidget : public QScrollArea
{
	Q_OBJECT
public:
	MatrixViewWidget(unsigned nRowNumber, unsigned nColumnNumber, QWidget *parent = 0);

	void setMatrix(boost::numeric::ublas::matrix<QString> matrix);
	boost::numeric::ublas::matrix<QString> getMatrix() const;

private:
	// Fields
	QGridLayout* m_gridLayout;
	// Methods
	QString makeStringIndex(unsigned nRow, unsigned nColumn);
};

#endif // MATRIX_VIEW_WIDGET_H

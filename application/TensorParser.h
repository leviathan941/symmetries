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

#ifndef TENSOR_PARSER_H
#define TENSOR_PARSER_H

#include "MatrixVectorExp.h"

#include <QString>

class SimpleItem;
class SimpleExpression;

class TensorParser
{
public:
	typedef boost::numeric::ublas::matrix<QString> QStringMatrix;

	static SimpleExpression fromQStringToSimpleExpression(const QString& sExpression);
	static MatrixVector<QString> fromMatrixVecExpToMatrixVecQString(const MatrixVectorExp& tensor);
	static MatrixVectorExp fromMatrixVecQStringToMatrixVecExp(
		const MatrixVector<QString>& stringTensor);

protected:
	static SimpleItem fromQStringItemToSimpleItem(const QString& sItem);

private:
	TensorParser();
};

#endif // TENSOR_PARSER_H

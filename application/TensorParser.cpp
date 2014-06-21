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

#include "TensorParser.h"
#include "SimpleExpression.h"
#include "SimpleItem.h"

#include <QStringList>
#include <QRegExp>
#include <boost/foreach.hpp>

#define ITEM_DELIMETER '*'
#define EXP_DELIMITER_PLUS '+'

TensorParser::TensorParser()
{
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression TensorParser::fromQStringToSimpleExpression(const QString& sExpression)
{
	QStringList expItems = sExpression.split(EXP_DELIMITER_PLUS, QString::SkipEmptyParts);
	SimpleItem itemZero("", 1.0, 0.0);
	SimpleExpression outExp;
	for (unsigned i = 0; i < expItems.size(); ++i)
	{
		SimpleItem tempItem(fromQStringItemToSimpleItem(expItems[i]));
		if (tempItem != itemZero)
		{
			outExp.pushItem(tempItem);
		}
	}
	return outExp;
}

///////////////////////////////////////////////////////////////////////////
MatrixVector<QString> TensorParser::fromMatrixVecExpToMatrixVecQString(
	const MatrixVectorExp& tensor)
{
	unsigned matrixRowNumber = tensor.getContent().getMatrixRowSize();
	unsigned matrixColumnNumber = tensor.getContent().getMatrixColumnSize();
	MatrixVector<QString> stringTensor(matrixRowNumber, matrixColumnNumber);

	std::vector<MatrixVectorExp::expBoostMatrix> vec = tensor.getContent().getVector();

	BOOST_FOREACH(MatrixVectorExp::expBoostMatrix& matrix, vec)
	{
		QStringMatrix tempMatrix;
		tempMatrix.resize(matrixRowNumber, matrixColumnNumber);
		for(unsigned i = 0; i < matrixRowNumber; i++)
		{
			for(unsigned j = 0; j < matrixColumnNumber; j++)
			{
				tempMatrix(i, j) = QString::fromStdString(matrix(i, j).toString());
			}
		}
		stringTensor.addMatrix(tempMatrix);
	}
	return stringTensor;
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp TensorParser::fromMatrixVecQStringToMatrixVecExp(
	const MatrixVector<QString>& stringTensor)
{
	std::vector<QStringMatrix> vecMatrStr = stringTensor.getVector();
	MatrixVectorExp inputTensor(stringTensor.getMatrixRowSize(),
		stringTensor.getMatrixColumnSize());
	BOOST_FOREACH(std::vector<QStringMatrix>::value_type& tempMatrix, vecMatrStr)
	{
		MatrixVectorExp::expBoostMatrix inputMatrix;
		inputMatrix.resize(tempMatrix.size1(), tempMatrix.size2());
		for (unsigned i = 0; i < tempMatrix.size1(); ++i)
		{
			for (unsigned j = 0; j < tempMatrix.size2(); ++j)
			{
				SimpleExpression tempExp = fromQStringToSimpleExpression(tempMatrix(i, j));
				inputMatrix(i, j) = tempExp;
			}
		}
		inputTensor.addMatrix(inputMatrix);
	}
	return inputTensor;
}

///////////////////////////////////////////////////////////////////////////
SimpleItem TensorParser::fromQStringItemToSimpleItem(const QString& sItem)
{
	QStringList itemTokens = sItem.split(ITEM_DELIMETER, QString::SkipEmptyParts);
	QString expStr;
	double nMultiplier = 1.0;
	for (unsigned i = 0; i < itemTokens.size(); ++i)
	{
		bool bIsNumber = false;
		double nNumber = itemTokens[i].toDouble(&bIsNumber);
		if (!bIsNumber)
		{
			QRegExp notAlphaNumRegExp("[^a-zA-Z\\d]");
			QString tempString(itemTokens[i]);
			if (tempString.at(0) == QChar('-'))
			{
				nMultiplier *= -1;
			}
			expStr.append(tempString.remove(notAlphaNumRegExp));
		}
		else
		{
			nMultiplier *= nNumber;
		}
	}
	SimpleItem simItem(expStr.toStdString(), 1.0, nMultiplier);
	return simItem;
}

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

#include "ExpressionParser.h"
#include "SimpleExpression.h"
#include "SimpleItem.h"

#include <QStringList>
#include <QRegExp>

#define QSTRING_DELIMETER '*'

ExpressionParser::ExpressionParser()
{
}

///////////////////////////////////////////////////////////////////////////
SimpleExpression ExpressionParser::fromQStringToSimpleExp(const QString& exp)
{
	QStringList expItems = exp.split(QSTRING_DELIMETER);
	QString expStr;
	double nMultiplier = 1.0;
	for(unsigned i = 0; i < expItems.size(); i++)
	{
		bool bIsNumber = false;
		double nNumber = expItems[i].toDouble(&bIsNumber);
		if(bIsNumber)
		{
			QRegExp notAlphaNumRegExp("[^a-zA-Z\\d]");
			QString tempString(expItems[i]);
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
	SimpleExpression simExp(simItem);
	return simExp;
}

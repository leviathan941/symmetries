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


#include "AffineLieAlgebra.h"
#include "DifferentialExpression.h"
#include "DifferentialItem.h"

#include <boost/foreach.hpp>
#include <cstdarg>

#define DIFF_INDEX_SEPARATOR ','
#define VARIABLE_SYMBOL "X"

AffineLieAlgebra::AffineLieAlgebra(const AffineConnection &connection)
{
	m_affineConnection = connection;
}

///////////////////////////////////////////////////////////////////////////
void AffineLieAlgebra::buildLieAlgebra()
{
	MatrixVectorExp christoffels = m_affineConnection.getChristoffelSymbols();

	for (unsigned k = 0; k < christoffels.getContent().getVectorSize(); ++k)
	{
		for (unsigned i = 0; i < christoffels.getContent().getMatrixRowSize(); ++i)
		{
			for (unsigned j = 0; j < christoffels.getContent().getMatrixColumnSize(); ++j)
			{
				DifferentialItem itemDijXk(createVariable(VARIABLE_SYMBOL, k + 1, 1, 1),
					createDiffIndex(2, i + 1, j + 1), 1, 1);
				std::cout << "itemDijXk = " << itemDijXk.toString() << std::endl;
				DifferentialExpression tempExp(itemDijXk);
				for (unsigned s = 0; s < christoffels.getContent().getVectorSize(); ++s)
				{
					DifferentialExpression expDiXsGksj;
					SimpleItem simpleItem1 = createVariable(VARIABLE_SYMBOL, s + 1, 1, 1);
					BOOST_FOREACH(const SimpleItem& christItem, christoffels(k, s, j)
						.getVectorItems())
					{
						expDiXsGksj.pushItem(DifferentialItem(
							static_cast<const SimpleItem&>(simpleItem1 * christItem),
							createDiffIndex(1, i + 1), 1, 1));
					}
					std::cout << "expDiXsGksj = " << expDiXsGksj.toString() << std::endl;

					DifferentialExpression expDjXsGkis;
					SimpleItem simpleItem2 = createVariable(VARIABLE_SYMBOL, s + 1, 1, 1);
					BOOST_FOREACH(const SimpleItem& christItem, christoffels(k, i, s)
						.getVectorItems())
					{
						expDjXsGkis.pushItem(DifferentialItem(
							static_cast<const SimpleItem&>(simpleItem2 * christItem),
							createDiffIndex(1, j + 1), 1, 1));
					}
					std::cout << "expDjXsGkis = " << expDjXsGkis.toString() << std::endl;

					DifferentialExpression expDsXkGsij;
					SimpleItem simpleItem3 = createVariable(VARIABLE_SYMBOL, k + 1, 1, 1);
					BOOST_FOREACH(const SimpleItem& christItem, christoffels(s, i, j)
						.getVectorItems())
					{
						expDsXkGsij.pushItem(DifferentialItem(
							static_cast<const SimpleItem&>(simpleItem3 * christItem),
							createDiffIndex(1, s + 1), 1, -1));
					}
					std::cout << "expDsXkGsij = " << expDsXkGsij.toString() << std::endl;

					// TODO Add calculating XsDsGkij item.

					tempExp += expDiXsGksj + expDjXsGkis + expDsXkGsij;
				}
				m_vecLieSystem.push_back(tempExp);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////
const std::vector<DifferentialExpression>& AffineLieAlgebra::getLieSystem() const
{
	return m_vecLieSystem;
}

///////////////////////////////////////////////////////////////////////////
void AffineLieAlgebra::printLieSystem() const
{
	BOOST_FOREACH(const DifferentialExpression& exp, m_vecLieSystem)
	{
		std::cout << exp.toString() << std::endl;
	}
}

///////////////////////////////////////////////////////////////////////////
SimpleItem AffineLieAlgebra::createVariable(std::string sVariable, unsigned nNumber,
	double nPower, double nMultiplier)
{
	std::stringstream stream;
	stream << sVariable << nNumber;
	return SimpleItem(stream.str(), nPower, nMultiplier);
}

///////////////////////////////////////////////////////////////////////////
std::string AffineLieAlgebra::createDiffIndex(unsigned count, ...)
{
	std::stringstream stream;
	va_list arguments;
	va_start(arguments, count);
	for (int i = 0; i < count; ++i)
	{
		stream << va_arg(arguments, unsigned) << DIFF_INDEX_SEPARATOR;
	}
	va_end(arguments);
	std::string str = stream.str();
	str.erase(str.find_last_of(DIFF_INDEX_SEPARATOR));
	return str;
}

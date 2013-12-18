/*
    Symmetries
    Copyright (C) 2013  Alexey Kuzin <amkuzink@gmail.com>

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

#include <iostream>
#include "AffineConnection.h"
#include "Item.h"
#include "FileReader.h"

int main(int argc, const char * argv[])
{
	using namespace boost::numeric::ublas;

	boost::filesystem::path filePath("matrix.txt");
	FileReader reader(filePath);
	reader.FromFileToMatrixExp();

/*	boostMatrixExp metricTensor(2, 2);
	Expression exprOne(Item(std::string(""), 0, 1));
	Expression exprZero(Item(std::string(""), 0, 0));
	metricTensor(0, 0) = exprOne;
	metricTensor(0, 1) = exprZero;
	metricTensor(1, 0) = exprZero;
	metricTensor(1, 1) = exprOne;
	for(unsigned i = 0; i < metricTensor.size1(); ++i)
	{
		for(unsigned j = 0; j < metricTensor.size2(); ++j)
		{
			metricTensor(i, j).print();
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\n\n";
	
	MatrixVectorExp torsionTensor(2, 2);
	Expression exprMinusOne(Item(std::string(""), 0, -1));
	Expression exprTwo(Item(std::string(""), 0, 2));
	Expression exprMinusTwo(Item(std::string(""), 0, -2));
	boostMatrixExp torsionMatrixOne(2, 2);
	torsionMatrixOne(0, 0) = exprZero;
	torsionMatrixOne(0, 1) = exprOne;
	torsionMatrixOne(1, 0) = exprMinusOne;
	torsionMatrixOne(1, 1) = exprZero;
	boostMatrixExp torsionMatrixTwo(2, 2);
	torsionMatrixTwo(0, 0) = exprZero;
	torsionMatrixTwo(0, 1) = exprTwo;
	torsionMatrixTwo(1, 0) = exprMinusTwo;
	torsionMatrixTwo(1, 1) = exprZero;
	torsionTensor.addMatrix(torsionMatrixOne);
	torsionTensor.addMatrix(torsionMatrixTwo);
	torsionTensor.print();
	
	AffineConnection affine;
	affine.setMetricTensor(metricTensor);
	affine.setTorsionTensor(torsionTensor);
	affine.allocateSize(2, 2, 2);
	std::cout << "calculateChristoffelSymbols" << std::endl;
	affine.calculateChristoffelSymbols();
	std::cout << "printChristoffelSymbols" << std::endl;
	affine.printChristoffelSymbols();
*/
	return 0;
}

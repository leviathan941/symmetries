/*
	Symmetries
	Copyright (C) 2013, 2014 Alexey Kuzin <amkuzink@gmail.com>

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

#include <QApplication>

#include "FileReader.h"
#include "AffineConnection.h"
#include "Item.h"
#include "MainWindow.h"

void calcTestConst2DAffine()
{
	using namespace boost::numeric::ublas;

	boostMatrixExp metricTensor(2, 2);
	Item itemOne(std::string(""), 0, 1);
	Item itemZero(std::string(""), 0, 0);
	Expression expOne(itemOne);
	Expression expZero(itemZero);
	metricTensor.insert_element(0, 0, expOne);
	metricTensor.insert_element(0, 1, expZero);
	metricTensor.insert_element(1, 0, expZero);
	metricTensor.insert_element(1, 1, expOne);
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
	boostMatrixExp torsionMatrix1(2, 2);
	boostMatrixExp torsionMatrix2(2, 2);
	Item itemA(std::string("a"), 1, 1);
	Item itemMinusA(std::string("a"), 1, -1);
	Item itemB(std::string("b"), 1, 1);
	Item itemMinusB(std::string("b"), 1, -1);
	Expression expA(itemA);
	Expression expMinusA(itemMinusA);
	Expression expB(itemB);
	Expression expMinusB(itemMinusB);

	torsionMatrix1.insert_element(0, 0, expZero);
	torsionMatrix1.insert_element(0, 1, expA);
	torsionMatrix1.insert_element(1, 0, expMinusA);
	torsionMatrix1.insert_element(1, 1, expZero);

	torsionMatrix2.insert_element(0, 0, expZero);
	torsionMatrix2.insert_element(0, 1, expB);
	torsionMatrix2.insert_element(1, 0, expMinusB);
	torsionMatrix2.insert_element(1, 1, expZero);
	torsionTensor.addMatrix(torsionMatrix1);
	torsionTensor.addMatrix(torsionMatrix2);
	torsionTensor.print();

	AffineConnection affine;
	affine.setMetricTensor(metricTensor);
	affine.setTorsionTensor(torsionTensor);
	std::cout << "calculateChristoffelSymbols" << std::endl;
	affine.calculateChristoffelSymbols();
	std::cout << "printChristoffelSymbols" << std::endl;
	affine.printChristoffelSymbols();

	std::cout << "calculateTorsion" << std::endl;
	affine.calculateTorsion();
	std::cout << "printTorsion" << std::endl;
	affine.printTorsion();
}

void calcTestConst4DAffine()
{
	using namespace boost::numeric::ublas;

	boostMatrixExp metricTensor(4, 4);
	Item itemOne(std::string(""), 0, 1);
	Item itemZero(std::string(""), 0, 0);
	Expression expOne(itemOne);
	Expression expZero(itemZero);
	metricTensor.insert_element(0, 0, expOne);
	metricTensor.insert_element(0, 1, expZero);
	metricTensor.insert_element(0, 2, expZero);
	metricTensor.insert_element(0, 3, expZero);
	metricTensor.insert_element(1, 0, expZero);
	metricTensor.insert_element(1, 1, expOne);
	metricTensor.insert_element(1, 2, expZero);
	metricTensor.insert_element(1, 3, expZero);
	metricTensor.insert_element(2, 0, expZero);
	metricTensor.insert_element(2, 1, expZero);
	metricTensor.insert_element(2, 2, expOne);
	metricTensor.insert_element(2, 3, expZero);
	metricTensor.insert_element(3, 0, expZero);
	metricTensor.insert_element(3, 1, expZero);
	metricTensor.insert_element(3, 2, expZero);
	metricTensor.insert_element(3, 3, expOne);
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


	MatrixVectorExp torsionTensor(4, 4);
	boostMatrixExp torsionMatrix1(4, 4);
	boostMatrixExp torsionMatrix2(4, 4);
	boostMatrixExp torsionMatrix3(4, 4);
	boostMatrixExp torsionMatrix4(4, 4);

	Item itemA0(std::string("a0"), 1, 1);
	Item itemMinusA0(std::string("a0"), 1, -1);
	Item itemB0(std::string("b0"), 1, 1);
	Item itemMinusB0(std::string("b0"), 1, -1);
	Item itemC0(std::string("c0"), 1, 1);
	Item itemMinusC0(std::string("c0"), 1, -1);
	Item itemD0(std::string("d0"), 1, 1);
	Item itemMinusD0(std::string("d0"), 1, -1);
	Item itemE0(std::string("e0"), 1, 1);
	Item itemMinusE0(std::string("e0"), 1, -1);
	Item itemF0(std::string("f0"), 1, 1);
	Item itemMinusF0(std::string("f0"), 1, -1);

	Item itemA1(std::string("a1"), 1, 1);
	Item itemMinusA1(std::string("a1"), 1, -1);
	Item itemB1(std::string("b1"), 1, 1);
	Item itemMinusB1(std::string("b1"), 1, -1);
	Item itemC1(std::string("c1"), 1, 1);
	Item itemMinusC1(std::string("c1"), 1, -1);
	Item itemD1(std::string("d1"), 1, 1);
	Item itemMinusD1(std::string("d1"), 1, -1);
	Item itemE1(std::string("e1"), 1, 1);
	Item itemMinusE1(std::string("e1"), 1, -1);
	Item itemF1(std::string("f1"), 1, 1);
	Item itemMinusF1(std::string("f1"), 1, -1);

	Item itemA2(std::string("a2"), 1, 1);
	Item itemMinusA2(std::string("a2"), 1, -1);
	Item itemB2(std::string("b2"), 1, 1);
	Item itemMinusB2(std::string("b2"), 1, -1);
	Item itemC2(std::string("c2"), 1, 1);
	Item itemMinusC2(std::string("c2"), 1, -1);
	Item itemD2(std::string("d2"), 1, 1);
	Item itemMinusD2(std::string("d2"), 1, -1);
	Item itemE2(std::string("e2"), 1, 1);
	Item itemMinusE2(std::string("e2"), 1, -1);
	Item itemF2(std::string("f2"), 1, 1);
	Item itemMinusF2(std::string("f2"), 1, -1);

	Item itemA3(std::string("a3"), 1, 1);
	Item itemMinusA3(std::string("a3"), 1, -1);
	Item itemB3(std::string("b3"), 1, 1);
	Item itemMinusB3(std::string("b3"), 1, -1);
	Item itemC3(std::string("c3"), 1, 1);
	Item itemMinusC3(std::string("c3"), 1, -1);
	Item itemD3(std::string("d3"), 1, 1);
	Item itemMinusD3(std::string("d3"), 1, -1);
	Item itemE3(std::string("e3"), 1, 1);
	Item itemMinusE3(std::string("e3"), 1, -1);
	Item itemF3(std::string("f3"), 1, 1);
	Item itemMinusF3(std::string("f3"), 1, -1);

	Expression expA0(itemA0);
	Expression expMinusA0(itemMinusA0);
	Expression expB0(itemB0);
	Expression expMinusB0(itemMinusB0);
	Expression expC0(itemC0);
	Expression expMinusC0(itemMinusC0);
	Expression expD0(itemD0);
	Expression expMinusD0(itemMinusD0);
	Expression expE0(itemE0);
	Expression expMinusE0(itemMinusE0);
	Expression expF0(itemF0);
	Expression expMinusF0(itemMinusF0);

	Expression expA1(itemA1);
	Expression expMinusA1(itemMinusA1);
	Expression expB1(itemB1);
	Expression expMinusB1(itemMinusB1);
	Expression expC1(itemC1);
	Expression expMinusC1(itemMinusC1);
	Expression expD1(itemD1);
	Expression expMinusD1(itemMinusD1);
	Expression expE1(itemE1);
	Expression expMinusE1(itemMinusE1);
	Expression expF1(itemF1);
	Expression expMinusF1(itemMinusF1);

	Expression expA2(itemA2);
	Expression expMinusA2(itemMinusA2);
	Expression expB2(itemB2);
	Expression expMinusB2(itemMinusB2);
	Expression expC2(itemC2);
	Expression expMinusC2(itemMinusC2);
	Expression expD2(itemD2);
	Expression expMinusD2(itemMinusD2);
	Expression expE2(itemE2);
	Expression expMinusE2(itemMinusE2);
	Expression expF2(itemF2);
	Expression expMinusF2(itemMinusF2);

	Expression expA3(itemA3);
	Expression expMinusA3(itemMinusA3);
	Expression expB3(itemB3);
	Expression expMinusB3(itemMinusB3);
	Expression expC3(itemC3);
	Expression expMinusC3(itemMinusC3);
	Expression expD3(itemD3);
	Expression expMinusD3(itemMinusD3);
	Expression expE3(itemE3);
	Expression expMinusE3(itemMinusE3);
	Expression expF3(itemF3);
	Expression expMinusF3(itemMinusF3);

	torsionMatrix1.insert_element(0, 0, expZero);
	torsionMatrix1.insert_element(0, 1, expA0);
	torsionMatrix1.insert_element(0, 2, expB0);
	torsionMatrix1.insert_element(0, 3, expC0);
	torsionMatrix1.insert_element(1, 0, expMinusA0);
	torsionMatrix1.insert_element(1, 1, expZero);
	torsionMatrix1.insert_element(1, 2, expD0);
	torsionMatrix1.insert_element(1, 3, expE0);
	torsionMatrix1.insert_element(2, 0, expMinusB0);
	torsionMatrix1.insert_element(2, 1, expMinusD0);
	torsionMatrix1.insert_element(2, 2, expZero);
	torsionMatrix1.insert_element(2, 3, expF0);
	torsionMatrix1.insert_element(3, 0, expMinusC0);
	torsionMatrix1.insert_element(3, 1, expMinusE0);
	torsionMatrix1.insert_element(3, 2, expMinusF0);
	torsionMatrix1.insert_element(3, 3, expZero);

	torsionMatrix2.insert_element(0, 0, expZero);
	torsionMatrix2.insert_element(0, 1, expA1);
	torsionMatrix2.insert_element(0, 2, expB1);
	torsionMatrix2.insert_element(0, 3, expC1);
	torsionMatrix2.insert_element(1, 0, expMinusA1);
	torsionMatrix2.insert_element(1, 1, expZero);
	torsionMatrix2.insert_element(1, 2, expD1);
	torsionMatrix2.insert_element(1, 3, expE1);
	torsionMatrix2.insert_element(2, 0, expMinusB1);
	torsionMatrix2.insert_element(2, 1, expMinusD1);
	torsionMatrix2.insert_element(2, 2, expZero);
	torsionMatrix2.insert_element(2, 3, expF1);
	torsionMatrix2.insert_element(3, 0, expMinusC1);
	torsionMatrix2.insert_element(3, 1, expMinusE1);
	torsionMatrix2.insert_element(3, 2, expMinusF1);
	torsionMatrix2.insert_element(3, 3, expZero);

	torsionMatrix3.insert_element(0, 0, expZero);
	torsionMatrix3.insert_element(0, 1, expA2);
	torsionMatrix3.insert_element(0, 2, expB2);
	torsionMatrix3.insert_element(0, 3, expC2);
	torsionMatrix3.insert_element(1, 0, expMinusA2);
	torsionMatrix3.insert_element(1, 1, expZero);
	torsionMatrix3.insert_element(1, 2, expD2);
	torsionMatrix3.insert_element(1, 3, expE2);
	torsionMatrix3.insert_element(2, 0, expMinusB2);
	torsionMatrix3.insert_element(2, 1, expMinusD2);
	torsionMatrix3.insert_element(2, 2, expZero);
	torsionMatrix3.insert_element(2, 3, expF2);
	torsionMatrix3.insert_element(3, 0, expMinusC2);
	torsionMatrix3.insert_element(3, 1, expMinusE2);
	torsionMatrix3.insert_element(3, 2, expMinusF2);
	torsionMatrix3.insert_element(3, 3, expZero);

	torsionMatrix4.insert_element(0, 0, expZero);
	torsionMatrix4.insert_element(0, 1, expA3);
	torsionMatrix4.insert_element(0, 2, expB3);
	torsionMatrix4.insert_element(0, 3, expC3);
	torsionMatrix4.insert_element(1, 0, expMinusA3);
	torsionMatrix4.insert_element(1, 1, expZero);
	torsionMatrix4.insert_element(1, 2, expD3);
	torsionMatrix4.insert_element(1, 3, expE3);
	torsionMatrix4.insert_element(2, 0, expMinusB3);
	torsionMatrix4.insert_element(2, 1, expMinusD3);
	torsionMatrix4.insert_element(2, 2, expZero);
	torsionMatrix4.insert_element(2, 3, expF3);
	torsionMatrix4.insert_element(3, 0, expMinusC3);
	torsionMatrix4.insert_element(3, 1, expMinusE3);
	torsionMatrix4.insert_element(3, 2, expMinusF3);
	torsionMatrix4.insert_element(3, 3, expZero);

	torsionTensor.addMatrix(torsionMatrix1);
	torsionTensor.addMatrix(torsionMatrix2);
	torsionTensor.addMatrix(torsionMatrix3);
	torsionTensor.addMatrix(torsionMatrix4);
	torsionTensor.print();

	AffineConnection affine;
	affine.setMetricTensor(metricTensor);
	affine.setTorsionTensor(torsionTensor);
	std::cout << "calculateChristoffelSymbols" << std::endl;
	affine.calculateChristoffelSymbols();
	std::cout << "printChristoffelSymbols" << std::endl;
	affine.printChristoffelSymbols();
}

int main(int argc, char *argv[])
{
	calcTestConst2DAffine();
	//calcTestConst4DAffine();

	//QApplication app(argc, argv);
	//MainWindow window;
	//window.show();
	//app.exec();

	return 0;
}

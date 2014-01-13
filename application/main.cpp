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
#include <QMainWindow>

#include "FileReader.h"
#include "AffineConnection.h"
#include "Item.h"

int main(int argc, char *argv[])
{
	using namespace boost::numeric::ublas;

	boost::filesystem::path MetricFilePath("../metric_tensor.txt");
	FileReader metricTensorReader(MetricFilePath);
	boostMatrixExp metricTensor = metricTensorReader.FromFileToMatrixExp();
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

	boost::filesystem::path torsionFilePath("../torsion_tensor.txt");
	FileReader torsionTensorReader(torsionFilePath);
	MatrixVectorExp torsionTensor = torsionTensorReader.FromFileToMatrixVecExp();
	torsionTensor.print();

	AffineConnection affine;
	affine.setMetricTensor(metricTensor);
	affine.setTorsionTensor(torsionTensor);
	affine.allocateSize(2, 2, 2);
	std::cout << "calculateChristoffelSymbols" << std::endl;
	affine.calculateChristoffelSymbols();
	std::cout << "printChristoffelSymbols" << std::endl;
	affine.printChristoffelSymbols();

	QApplication app(argc, argv);
	QMainWindow window;
	window.show();
	app.exec();

	return 0;
}

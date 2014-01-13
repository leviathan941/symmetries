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


#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <boost/filesystem.hpp>

#include "MatrixVectorExp.h"

class FileReader
{
public:
	typedef boost::numeric::ublas::matrix<Expression> MatrixExp;

	FileReader(boost::filesystem::path& FilePath);
	virtual ~FileReader();

	MatrixExp FromFileToMatrixExp();
	MatrixVectorExp FromFileToMatrixVecExp();
private:
	std::string getMatrixString();
	void exciseMatrixSize(std::string& strInput, unsigned& nRowNumber, unsigned& nColumnNumber);
	MatrixExp getMatrixFromString(const std::string& strInput, unsigned nRowNumber, unsigned nColumnNumber);
	std::vector<std::string> splitStringToElements(const std::string& strInput, char cDelimeter);
	void removeBrackets(std::string& strInput, char cOpenBracket, char cCloseBracket);
	void removeWhitespaces(std::string& strInput);

	std::ifstream m_file;
};

#endif // FILEREADER_H

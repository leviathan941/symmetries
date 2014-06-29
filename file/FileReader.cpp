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


#include "FileReader.h"
#include "Exceptions.h"
#include "SimpleItem.h"

#include <algorithm>
#include <boost/lexical_cast.hpp>

#define MATRIX_SIZE_START_SYMBOL '['
#define MATRIX_SIZE_END_SYMBOL ']'
#define MATRIX_ELEMENT_DELIMITER ','
#define MATRIX_ELEMENT_START_SYMBOL '('
#define MATRIX_ELEMENT_END_SYMBOL ')'

///////////////////////////////////////////////////////////////////////////
FileReader::FileReader(boost::filesystem::path &FilePath)
{
	boost::system::error_code error;
	if(boost::filesystem::exists(FilePath, error) && boost::filesystem::is_regular_file(FilePath, error))
	{
		m_file.open(FilePath.c_str(), std::ios_base::in);
	}
	else
	{
		throw fileException(error.message().c_str());
	}
}

///////////////////////////////////////////////////////////////////////////
FileReader::~FileReader()
{
	m_file.close();
}

///////////////////////////////////////////////////////////////////////////
FileReader::MatrixExp FileReader::FromFileToMatrixExp()
{
	if(!m_file.is_open())
	{
		throw coreException("Read file isn't opened");
	}

	std::string strMatrixString = getMatrixString();
	unsigned nRow(0), nColumn(0);
	exciseMatrixSize(strMatrixString, nRow, nColumn);
	std::cout << "Row number: " << nRow << " Column number: " << nColumn << std::endl;
	std::cout << "String: " << strMatrixString << std::endl;

	return getMatrixFromString(strMatrixString, nRow, nColumn);
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp FileReader::FromFileToMatrixVecExp()
{
	if(!m_file.is_open())
	{
		throw coreException("Read file isn't opened");
	}

	std::vector<MatrixExp> vecMatrices;
	while(m_file.good())
	{
		MatrixExp exp = FromFileToMatrixExp();
		vecMatrices.push_back(exp);
	}

	unsigned nRow(0), nColumn(0);
	BOOST_FOREACH(MatrixExp& matr, vecMatrices)
	{
		if(!nRow || !nColumn)
		{
			nRow = matr.size1();
			nColumn = matr.size2();
		}

		if(nRow != matr.size1() ||
			nColumn != matr.size2())
			throw coreException("All matrices must have the same size");
	}

	MatrixVectorExp vecExpression(vecMatrices, nRow, nColumn);
	return vecExpression;
}

///////////////////////////////////////////////////////////////////////////
std::string FileReader::getMatrixString()
{
	if(!m_file.is_open())
	{
		throw coreException("Read file isn't opened");
	}

	std::string strMatrixString, strFileLine;
	do
	{
		std::getline(m_file, strFileLine);
		strMatrixString += strFileLine;
	}
	while(!strFileLine.empty() && m_file.good());

	std::cout << "Original String: " << strMatrixString << std::endl;
	removeWhitespaces(strMatrixString);

	return strMatrixString;
}

///////////////////////////////////////////////////////////////////////////
void FileReader::exciseMatrixSize(std::string &strInput, unsigned &nRowNumber, unsigned &nColumnNumber)
{
	size_t startPos, endPos;
	if( ((startPos = strInput.find_first_of(MATRIX_SIZE_START_SYMBOL)) == std::string::npos) ||
		((endPos = strInput.find_first_of(MATRIX_SIZE_END_SYMBOL)) == std::string::npos) )
	{
		throw fileException("Incorrect matrix description");
	}

	std::string strMatrixSize = strInput.substr(startPos, endPos - startPos + 1);
	strInput.erase(startPos, endPos - startPos + 1);
	removeBrackets(strMatrixSize, MATRIX_SIZE_START_SYMBOL, MATRIX_SIZE_END_SYMBOL);

	if((strMatrixSize.find(MATRIX_ELEMENT_DELIMITER) == std::string::npos) ||
		(std::count(strMatrixSize.begin(), strMatrixSize.end(), MATRIX_ELEMENT_DELIMITER) != 1))
	{
		throw fileException("Incorrect matrix size");
	}

	std::vector<std::string> vecMatrixSizes(splitStringToElements(strMatrixSize, MATRIX_ELEMENT_DELIMITER));
	if(vecMatrixSizes.size() != 2)
	{
		throw fileException("Matrix size must contain 2 digits");
	}

	try
	{
		nRowNumber = boost::lexical_cast<unsigned>(vecMatrixSizes[0]);
		nColumnNumber = boost::lexical_cast<unsigned>(vecMatrixSizes[1]);
	} catch (boost::bad_lexical_cast e)
	{
		throw fileException("Failed to cast Row anf Column numbers.");
	}
}

///////////////////////////////////////////////////////////////////////////
FileReader::MatrixExp FileReader::getMatrixFromString(const std::string &strInput, unsigned nRowNumber,
	unsigned nColumnNumber)
{
	std::string strTemp(strInput);

	removeBrackets(strTemp, MATRIX_ELEMENT_START_SYMBOL, MATRIX_ELEMENT_END_SYMBOL);
	std::cout << "String: " << strTemp << std::endl;

	std::vector<std::string> vecTemp = splitStringToElements(strTemp, MATRIX_ELEMENT_DELIMITER);

	MatrixExp matr(nRowNumber, nColumnNumber);
	unsigned nElem(0);
	try
	{
		for(unsigned i = 0; i < matr.size1(); ++i)
		{
			for(unsigned j = 0; j < matr.size2(); ++j)
			{
				// At the moment only matrix which contains digits can be read from a file
				// TODO: Add full support of reading from a file into Expression
				SimpleExpression exp(SimpleItem(std::string(""), 0,
					boost::lexical_cast<double>(vecTemp[nElem++])));
				matr.insert_element(i, j, exp);
			}
		}
	} catch (boost::bad_lexical_cast e)
	{
		throw fileException("Only digital matrices are supported.");
	}

	return matr;
}

///////////////////////////////////////////////////////////////////////////
std::vector<std::string> FileReader::splitStringToElements(const std::string &strInput, char cDelimeter)
{
	std::string strTemp(strInput);
	std::vector<std::string> vecOutput;

	auto pushFunc =[&vecOutput](const std::string& strElem){ if(!strElem.empty()) vecOutput.push_back(strElem); };

	size_t pos(0);
	while((pos = strTemp.find(cDelimeter)) != std::string::npos)
	{
		std::string strElement = strTemp.substr(0, pos);
		pushFunc(strElement);
		strTemp.erase(0, pos + 1);
	}
	pushFunc(strTemp);

	return vecOutput;
}

///////////////////////////////////////////////////////////////////////////
void FileReader::removeBrackets(std::string &strInput, char cOpenBracket, char cCloseBracket)
{
	strInput.erase(std::remove(strInput.begin(), strInput.end(), cOpenBracket), strInput.end());
	strInput.erase(std::remove(strInput.begin(), strInput.end(), cCloseBracket), strInput.end());
}

///////////////////////////////////////////////////////////////////////////
void FileReader::removeWhitespaces(std::string& strInput)
{
	strInput.erase(std::remove_if(strInput.begin(), strInput.end(), ::isspace),
		strInput.end());
}

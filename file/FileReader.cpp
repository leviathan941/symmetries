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


#include "FileReader.h"
#include "Exceptions.h"

#define MATRIX_SIZE_START_SYMBOL '['
#define MATRIX_SIZE_END_SYMBOL ']'
#define ELEMENT_DELIMER ','
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
		throw coreException(error.message().c_str());
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
	std::cout << strMatrixString << std::endl;
	unsigned nRow(0), nColumn(0);
	exciseMatrixSize(strMatrixString, nRow, nColumn);
	std::cout << "Row number: " << nRow << " Column number: " << nColumn << std::endl;
}

///////////////////////////////////////////////////////////////////////////
MatrixVectorExp FileReader::FromFileToMatrixVecExp()
{
	if(!m_file.is_open())
	{
		throw coreException("Read file isn't opened");
	}
}

///////////////////////////////////////////////////////////////////////////
std::string FileReader::getMatrixString()
{
	if(!m_file.is_open())
	{
		throw coreException("Read file isn't opened");
	}

	std::string strFileLine;
	std::getline(m_file, strFileLine);
	return strFileLine;
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
	deleteBorderSymbols(strMatrixSize, MATRIX_SIZE_START_SYMBOL, MATRIX_SIZE_END_SYMBOL);
	std::cout << strMatrixSize << "\n" << strInput << std::endl;

	size_t delimerPos;
	if((delimerPos = strMatrixSize.find(ELEMENT_DELIMER)) == std::string::npos)
	{
		throw fileException("Incorrect matrix size");
	}

	std::stringstream tempStream;
	tempStream << strMatrixSize.substr(0, delimerPos);
	tempStream >> nRowNumber;

	tempStream.clear();
	tempStream.str(std::string());

	tempStream << strMatrixSize.substr(delimerPos + 1);
	tempStream >> nColumnNumber;
}

///////////////////////////////////////////////////////////////////////////
FileReader::MatrixExp FileReader::getMatrixFromString(const std::string &strInput, unsigned nRowNumber,
	unsigned nColumnNumber)
{

}

///////////////////////////////////////////////////////////////////////////
std::vector<std::string> FileReader::parseMatrixToRows(const std::string &strMatrixString)
{

}

///////////////////////////////////////////////////////////////////////////
void FileReader::deleteBorderSymbols(std::string &strInput, char cStartSymbol, char cEndSymbol)
{
	if(strInput.find_first_of(cStartSymbol) != std::string::npos)
		strInput.erase(strInput.find_first_of(cStartSymbol), 1);

	if(strInput.find_last_of(cEndSymbol) != std::string::npos)
		strInput.erase(strInput.find_last_of(cEndSymbol), 1);
}

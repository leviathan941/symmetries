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

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <iostream>

class coreException: public std::exception
{
public:
	coreException(const char* strErrorMessage)
	{
		if(strErrorMessage)
			strError = strErrorMessage;
	}

	~coreException() throw() {}

	virtual const char* what() const throw()
	{
		return strError.c_str();
	}
private:
	std::string strError;
};

class fileException: public coreException
{
public:
	fileException(const char* strErrorMessage)
	: coreException(strErrorMessage) {}

	~fileException() throw() {}
};

#define CATCH_FILE catch(fileException& e)\
{\
	std::cout << "File error is happened: " << e.what() << std::endl;\
}

#define CATCH_CORE catch(coreException& e)\
{\
	std::cout << "Core error is happened: " << e.what() << std::endl;\
}

#endif // EXCEPTIONS_H

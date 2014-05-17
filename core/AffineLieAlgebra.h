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


#ifndef AFFINE_LIE_ALGEBRA_H
#define AFFINE_LIE_ALGEBRA_H

#include "AffineConnection.h"
#include "DifferentialExpression.h"

class AffineLieAlgebra
{
public:
	AffineLieAlgebra(const AffineConnection& connection);

	void buildLieAlgebra();
	const std::vector<DifferentialExpression> &getLieSystem() const;

	void printLieSystem() const;

private:
	SimpleItem createVariable(std::string sVariable, unsigned nNumber, double nPower,
		double nMultiplier);
	std::string createDiffIndex(unsigned count, ...);

	AffineConnection m_affineConnection;
	std::vector<DifferentialExpression> m_vecLieSystem;
};

#endif // AFFINE_LIE_ALGEBRA_H

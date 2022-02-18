#pragma once
#include "Matrices.h"
#include "CrystallCellType.h"



class Crystal
{
private:
	double a, b, c, alfa, beta, gamma;
	Matrix tenzor, i_tenzor;
	CrystallCellType cellType;
public:
	Crystal(void);
	Crystal(double a, double b, double c, double alfa, double beta, double gamma);
	Crystal(double a, double b, double c);
	~Crystal(void);

	double interplanarSpacing(double hkl_v[3]) const;
	CrystallCellType getCelltype(void) const {return cellType;}
	Matrix getTenzor(void) const {return tenzor;}
	Matrix getInvTenzor(void) const {return i_tenzor;}

	void printCrystalInfo(void)const;//Testing method
protected:
	bool initCrystal(void);
};


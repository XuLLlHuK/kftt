#define _USE_MATH_DEFINES
#include "math.h"
#include "Crystal.h"

Crystal::Crystal(void)
{
}

Crystal::Crystal(double a, double b, double c, double alfa, double beta, double gamma):
a(a), b(b), c(c), alfa(alfa), beta(beta), gamma(gamma)
{
	initCrystal();
}

Crystal::Crystal(double a, double b, double c):
a(a), b(b), c(c), alfa(90.0), beta(90.0), gamma(90.0)
{
	initCrystal();
}

Crystal::~Crystal(void)
{
}

bool Crystal::initCrystal(void)
{
	alfa *= M_PI/180.0;
	beta *= M_PI/180.0;
	gamma *= M_PI/180.0;

	tenzor = Matrix(3, 3);
	i_tenzor = Matrix(3, 3);

	tenzor(0, 0) = a*a;
	tenzor(0, 1) = a*b*cos(gamma);
	tenzor(0, 2) = a*c*cos(beta);

	tenzor(1, 0) = tenzor(0, 1);
	tenzor(1, 1) = b*b;
	tenzor(1, 2) = b*c*cos(alfa);

	tenzor(2, 0) = tenzor(0, 2);
	tenzor(2, 1) = tenzor(1, 2);
	tenzor(2, 2) = c*c;

	i_tenzor = tenzor.inverse();

	return true;
}

double Crystal::interplanarSpacing(double hkl[3])const{
	double d_hkl = 0.0;
	Matrix hkl_row = Matrix(1, 3);
	Matrix hkl_column = Matrix(3, 1);

	for(int i=0; i<3; i++){
		hkl_row(0, i) = hkl[i];
		hkl_column(i, 0) = hkl[i];
	}

	Matrix temp = Matrix(3, 3);
	temp = hkl_row * i_tenzor;

	return d_hkl;
}

void Crystal::printCrystalInfo(void)const{
	cout<<"-----Crystal params.-----\n";
	cout<<"a: "<<a<<", b: "<<b<<", c: "<<c<<"\n";
	cout<<"alfa: "<<a<<", beta: "<<b<<", gamma: "<<c<<"\n";
	cout<<"-----Tenzor.-----\n";
	tenzor.printMatrix();
	cout<<"-----Inverse tenzor.-----\n";
	i_tenzor.printMatrix();
}

int main(){
	Crystal crystal = Crystal(3.0, 3.0, 3.0);
	crystal.printCrystalInfo();
	double hkl[3] = {1.0, 1.0, 0.0};
	crystal.interplanarSpacing(hkl);
	return 0;
}
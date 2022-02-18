/*#pragma once
class Calculations
{
public:
	static bool getMetricTenzor(Crystal crystal, Matrix tenzor)
	{
		double alfaRab = crystal.getAlfa() * M_PI / 180.0;
		double betaRad = crystal.getBeta() * M_PI / 180.0;
		double gammaRad = crystal.getGamma() * M_PI / 180.0;

		//TODO: расчет

		if(!determ(G))
		{
			AfxMessageBox("Ошибка(002)! Определитель равен 0! Дальнейшая работа невозможна!",
				MB_OK|MB_ICONSTOP);
			return FALSE;
		}
		else
			return TRUE;
	}

	static bool basisVector(Matrix a)
	{
		double Ob=fabs(determ(A));
		if(Ob)
		{
			double VP11=A[1][1]*A[2][2]-A[1][2]*A[2][1];
			double VP12=A[1][2]*A[2][0]-A[1][0]*A[2][2];
			double VP13=A[1][0]*A[2][1]-A[1][1]*A[2][0];
			oa[0][0]=VP11/Ob;	oa[0][1]=VP12/Ob;	oa[0][2]=VP13/Ob;
			double VP21=A[2][1]*A[0][2]-A[2][2]*A[0][1];
			double VP22=A[2][2]*A[0][0]-A[2][0]*A[0][2];
			double VP23=A[2][0]*A[0][1]-A[2][1]*A[0][0];
			oa[1][0]=VP21/Ob;	oa[1][1]=VP22/Ob;	oa[1][2]=VP23/Ob;
			double VP31=A[0][1]*A[1][2]-A[0][2]*A[1][1];
			double VP32=A[0][2]*A[1][0]-A[0][0]*A[1][2];
			double VP33=A[0][0]*A[1][1]-A[0][1]*A[1][0];
			oa[2][0]=VP31/Ob;	oa[2][1]=VP32/Ob;	oa[2][2]=VP33/Ob;
			return TRUE;
		}
		else
		{
			AfxMessageBox("Ошибка(004)! Деление на ноль! Дальнейшая работа невозможна!",
				MB_OK|MB_ICONSTOP);
			return FALSE;
		}
	}
};
*/
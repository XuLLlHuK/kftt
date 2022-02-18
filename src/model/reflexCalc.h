int CLaueDlg::reflexCalc(int H, int K, int L)
{
	char buff[80];//
	double RMAX, RMIN, X1, X2, X3, Y1, Y2, Znam, lyamIst, slyam, H2;//?

	//координаты узлов обратной решетки в лаб. с-ме координат
	X1=H*oa[0][0]+K*oa[1][0]+L*oa[2][0];
	X2=H*oa[0][1]+K*oa[1][1]+L*oa[2][1];
	X3=H*oa[0][2]+K*oa[1][2]+L*oa[2][2];
	//

	//Условие попадания между сферами эвальда
	RMAX=X1*X1+X2*X2+(X3+1/Lmin)*(X3+1/Lmin);
	RMIN=X1*X1+X2*X2+(X3+1/Lmax)*(X3+1/Lmax);

	if((RMAX<R1)&&(RMIN>R2))
	{
		//Расчет длины волны, соответ. отражению от hkl
		lyamIst=-2*X3/(X1*X1+X2*X2+X3*X3);
		slyam=1/lyamIst;
		H2=X1*X1+X2*X2+X3*X3;
		if(H2!=0)
		{
			double modulH=sqrt(H2);
			double skalyar=slyam*(X3+slyam);
			double cos_Fi=skalyar/(modulH*slyam);
			if(Epigramm==TRUE)
			{
				if(cos_Fi<0)
				{
					Znam=X3*X3-(X2*X2+X1*X1);
					if(Znam!=0)
					{
						Y1=(2*X1*X3*D)/Znam;
						Y2=(2*X2*X3*D)/Znam;
						if((fabs(Y1)<=SS)&&(fabs(Y2)<=SS))
						{
								int x1=(int)(4.35*Y1-2+220);
								int y1=(int)(4.35*Y2-2+220);
								int x2=(int)(4.35*Y1+2+220);
								int y2=(int)(4.35*Y2+2+220);
								dcMemory.Ellipse(x1, y1, x2, y2);

								sprintf_s(buff, "(%i %i %i),  длина волны=%.4f", H, K, L, lyamIst);
								m_pReflexTips->AddTool(this, buff, 
									CRect(x1-2, y1-2, x2+2, y2+2), reflexID++);

								//fprintf(logs, "\n%d\t %d\t %d\t %f\n", H, K, L, lyamIst);
						}
					}
				}
			}
			else
			{
				if(cos_Fi>0)
				{
					Znam=X3*X3-(X2*X2+X1*X1);
					if(Znam!=0)
					{
						Y1=(2*X1*X3*D)/Znam;
						Y2=(2*X2*X3*D)/Znam;
						if((fabs(Y1)<=SS)&&(fabs(Y2)<=SS))
						{
								int x1=(int)(4.35*Y1-2+220);
								int y1=(int)(4.35*Y2-2+220);
								int x2=(int)(4.35*Y1+2+220);
								int y2=(int)(4.35*Y2+2+220);
								dcMemory.Ellipse(x1, y1, x2, y2);

								sprintf_s(buff, "(%i %i %i),  длина волны=%.4f", H, K, L, lyamIst);
								m_pReflexTips->AddTool(this, buff, 
									CRect(x1-2, y1-2, x2+2, y2+2), reflexID++);

								//fprintf(logs, "\n%d\t %d\t %d\t %f\n", H, K, L, lyamIst);
						}
					}
				}
			}
		}
	}
	return 0;
}


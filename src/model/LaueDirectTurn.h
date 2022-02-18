void CLaueDlg::LaueDirectTurn()
{
	UpdateData();//

	//удаление устройства ToolTip рефлексов
	int id = reflexID;
	while(id > 1)
	{
		m_pReflexTips->DelTool(this, id);
		id--;
	}
	//

	double tetaP=teta*M_PI/180;

	double a_ij_turned[3][3]={{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};

	//для вывода на экран области отображения лауэграммы
	dcMemory.Rectangle(0, 0, 440, 440);//
	dcMemory.MoveTo(220, 210); dcMemory.LineTo(220, 230);//
	dcMemory.MoveTo(210, 220); dcMemory.LineTo(230, 220);//
	dcMemory.MoveTo(220, 10); dcMemory.LineTo(220, 30);//
	dcMemory.MoveTo(430, 220); dcMemory.LineTo(410, 220);//

	//Вычисляем к-ты в-ра P в лаб. с-ме к-т
	double P1E=Hn*a_ij[0][0]+Kn*a_ij[1][0]+Ln*a_ij[2][0];
	double P2E=Hn*a_ij[0][1]+Kn*a_ij[1][1]+Ln*a_ij[2][1];
	double P3E=Hn*a_ij[0][2]+Kn*a_ij[1][2]+Ln*a_ij[2][2];
	
	//Вычисляем направляющие косинус углов между в-ром и осями лаб. с-мы к-т
	double modulP=sqrt(P1E*P1E+P2E*P2E+P3E*P3E);

	//умножаем оператор поворота на матрицу OA_matrix
	if(modulP)//проверяем на равенство 0
	{
		double alfaP=P1E/modulP;	double betaP=P2E/modulP;	double gammaP=P3E/modulP;
		
		double turnMatrix[3][3] = {
			{cos(tetaP)+(1-cos(tetaP))*alfaP*alfaP, 
			(1-cos(tetaP))*alfaP*betaP + sin(tetaP)*gammaP,
			(1-cos(tetaP))*alfaP*gammaP - sin(tetaP)*betaP},
		{(1-cos(tetaP))*alfaP*betaP - sin(tetaP)*gammaP,
			cos(tetaP)+(1-cos(tetaP))*betaP*betaP,
			(1-cos(tetaP))*betaP*gammaP + sin(tetaP)*alfaP},
		{(1-cos(tetaP))*gammaP*alfaP + sin(tetaP)*betaP,
			(1-cos(tetaP))*gammaP*betaP - sin(tetaP)*alfaP,
			cos(tetaP) + (1-cos(tetaP))*gammaP*gammaP}};

		multMatrix(a_ij, turnMatrix, a_ij_turned);
	}
	else
		return;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			a_ij[i][j]=0.0;
			a_ij[i][j]=a_ij_turned[i][j];
		}
	}

	BOOL check=baseVect(a_ij);
	if(!check)
		return;

	//начинаем цикл от -Knots до +Knots
	for(int h=-Knots; h<=Knots; h++)
	{
		for(int k=-Knots; k<=Knots; k++)
		{
			for(int l=-Knots; l<=Knots; l++)
			{
				//int Hsum=h*h+k*k+l*l;//
				//if(Hsum<=52)//
				{
					if(StructFactor==1)//структурный фактор
					{
						int H=h*h+k*k+l*l;//сумма квадратов индексов узлов обратной решетки
						if(H%2==0)//условие на ОЦК решетку
						{
							reflexCalc(h, k, l);//функция расчета рефлексов
						}
					}
					//структурный фактор
					if(StructFactor!=1&&StructFactor!=0)//условие на ПРИМИТВНУЮ решетку
					{
						reflexCalc(h, k, l);//функция расчета рефлексов
					}
					if(StructFactor==0)//структурный фактор
					{
						//условие на ГЦК решетку
						int ch1=abs(h%2), ch2=abs(k%2), ch3=abs(l%2);
						if((ch1==ch2)&&(ch1==ch3)&&
							(ch2==ch1)&&(ch2==ch3)&&
							(ch3==ch1)&&(ch3==ch2))
						{
							reflexCalc(h, k, l);//функция расчета рефлексов
						}
					}
				}
			}
		}
	}
	//
	Invalidate(NULL);//обновляем область рисования
	//
	return;
}


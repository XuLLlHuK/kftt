void CLaueDlg::LaueAngleTurn()
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

	//Углы из градусов переводятся в радианы
	double alf=alfa*M_PI/180;
	double bet=beta*M_PI/180;
	double gam=gamma*M_PI/180;
	//

	//для вывода на экран области отображения лауэграммы
	dcMemory.Rectangle(0, 0, 440, 440);//
	dcMemory.MoveTo(220, 210); dcMemory.LineTo(220, 230);//
	dcMemory.MoveTo(210, 220); dcMemory.LineTo(230, 220);//
	dcMemory.MoveTo(220, 10); dcMemory.LineTo(220, 30);//
	dcMemory.MoveTo(430, 220); dcMemory.LineTo(410, 220);//
	//
	double Turn[3][3], temp_oa[3][3];

	for(int i = 0; i<3; i++)
	{
		for(int j = 0; j<3; j++)
		{
			Turn[i][j] = 0.0F;
			temp_oa[i][j] = 0.0F;
		}
	}

	Turn[0][0]=(cos(gam)*cos(alf)+sin(alf)*sin(bet)*sin(gam));
	Turn[0][1]=(sin(alf)*cos(gam)-sin(bet)*cos(alf)*sin(gam));
	Turn[0][2]=(sin(gam)*cos(bet));
	Turn[1][0]=(-1*cos(bet)*sin(alf));
	Turn[1][1]=(cos(bet)*cos(alf));
	Turn[1][2]=(sin(bet));
	Turn[2][0]=(-1*sin(gam)*cos(alf)+cos(gam)*sin(alf)*sin(bet));
	Turn[2][1]=(-1*(sin(gam)*sin(alf)+sin(bet)*cos(alf)*cos(gam)));
	Turn[2][2]=(cos(gam)*cos(bet));

	if(!determ(Turn))
		AfxMessageBox("Ошибка(101)! Определитель матрицы поворота нулевой! Дальнейшая работа невозможна!",
			MB_OK|MB_ICONSTOP);

    //умножение матрицы базисных векторов обратной решетки на матрицу 
	multMatrix(oa, Turn, temp_oa);
	//
	
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			oa[i][j]=temp_oa[i][j];
		}
	}
	//

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


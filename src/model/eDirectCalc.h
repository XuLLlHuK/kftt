BOOL CLaueDlg::eDirectCalc(double E[3][3], double G[3][3])
{
	double OG[3][3]={{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};//обр. метр. тензор
	BOOL check=TRUE;
	double DET;//определитель

	//задаем плоскость и находим ее индексы
	double H=0, K=0, L=0;

	H = E[2][0]*G[0][0]+E[2][1]*G[1][0]+E[2][2]*G[2][0];
	K = E[2][0]*G[0][1]+E[2][1]*G[1][1]+E[2][2]*G[2][1];
	L = E[2][0]*G[0][2]+E[2][1]*G[1][2]+E[2][2]*G[2][2];
	//

	if(!H&&!K&&!L)
	{
		AfxMessageBox("Ошибка(009)!Результат расчета индексов плоскости: H=0, K=0, L=0! Дальнейшая работа невозможна!",
			MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	double h=0, k=0, l=0;//индексы направления по-вертикали

	//((!H&&!K&&L)||(!H&&K&&!L)||(H&&!K&&!L))
	if(!H&&!K&&L)//0*h + 0*k + L*l = 0;
	{
		h = RAND_MAX / rand();
		k = RAND_MAX / rand();
		l = 0.0;
	}

	if(!H&&K&&!L)//0*h + K*k + 0*l = 0;
	{
		h = RAND_MAX / rand();
		k = 0.0;
		l = RAND_MAX / rand();
	}

	if(H&&!K&&!L)//H*h + 0*k + 0*l = 0;
	{
		h = 0.0;
		k = RAND_MAX / rand();
		l = RAND_MAX / rand();
	}
	//

	//(!H&&(K>0)&&(L>0))||((H>0)&&!K&&(L>0))||((H>0)&&(K>0)&&!L)
	//(!H&&(K<0)&&(L<0))||((H<0)&&!K&&(L<0))||((H<0)&&(K<0)&&!L)
	if( (!H&&(K>0)&&(L>0)) || (!H&&(K<0)&&(L<0)) )//0*h + K*k + L*l = 0; 0*h - K*k - L*l = 0;
	{
		h = RAND_MAX / rand();
		k = -L;
		l = K;
	}

	if( ((H>0)&&!K&&(L>0)) || ((H<0)&&!K&&(L<0)) )//H*h + 0*k + L*l = 0; -H*h + 0*k - L*l = 0;
	{
		h = -L;
		k = RAND_MAX / rand();
		l = H;
	}

	if( ((H>0)&&(K>0)&&!L) || ((H<0)&&(K<0)&&!L) )//H*h + K*k + 0*l = 0; -H*h - K*k + 0*l = 0;
	{
		h = -K;
		k = H;
		l = RAND_MAX / rand();
	}
	//

	//(!H&&(K>0||K<0)&&(L>0||L<0))||((H>0||H<0)&&!K&&(L>0||L<0))||((H>0||H<0)&&(K>0||K<0)&&!L)
	if( (!H&&(K>0)&&(L<0)) || (!H&&(K<0)&&(L>0)) )//0*h + K*k - L*l = 0; 0*h - K*k + L*l = 0;
	{
		h = RAND_MAX / rand();
		k = fabs(L);
		l = fabs(K);
	}

	if( ((H>0)&&!K&&(L<0)) || ((H<0)&&!K&&(L>0)) )//H*h + 0*k + L*l = 0; -H*h + 0*k - L*l = 0;
	{
		h = fabs(L);
		k = RAND_MAX / rand();
		l = fabs(H);
	}

	if( ((H>0)&&(K<0)&&!L) || ((H<0)&&(K>0)&&!L) )//H*h - K*k + 0*l = 0; -H*h + K*k + 0*l = 0;
	{
		h = fabs(K);
		k = fabs(H);
		l = RAND_MAX / rand();
	}
	//

	//(H&&K&&L)
	if(H&&K&&L)
	{
		if( (K>0)&&(L<0) || (K<0)&&(L>0) )//H*h + K*k - L*l = 0; H*h - K*k + L*l = 0;
		{
			h =0.0;
			k = fabs(L);
			l = fabs(K);
		}

		if( (K>0)&&(L>0) || (K<0)&&(L<0) )//H*h + K*k + L*l = 0; H*h - K*k - L*l = 0;
		{
			h =0.0;
			k = L;
			l = -K;
		}
	}
	//

	E[1][0] = h; E[1][1] = k; E[1][2] = l;//вектор по-вертикали

	//ДЛЯ ПРОВЕРКИ ПРАВОЙ ИЛИ ЛЕВОЙ ТРОЙКИ ВЕКТОРОВ
	double pH=0, pK=0, pL=0;

	//произведение соответствует левой тройке векторов
	pH = E[2][2]*E[1][1] - E[2][1]*E[1][2];
	pK = E[2][0]*E[1][2] - E[2][2]*E[1][0];
	pL = E[2][1]*E[1][0] - E[2][0]*E[1][1];

	check = invMatrix(G, OG);
	if(!check)
		return FALSE;

	E[0][0] = pH*OG[0][0]+pK*OG[1][0]+pL*OG[2][0];
	E[0][1] = pH*OG[0][1]+pK*OG[1][1]+pL*OG[2][1];
	E[0][2] = pH*OG[0][2]+pK*OG[1][2]+pL*OG[2][2];
	//

	DET=determ(E);
	if(!DET)
	{
		AfxMessageBox("Ошибка(003)!Проверка правой-левой тройки: определитель равен 0! Дальнейшая работа невозможна!",
			MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	if(DET<0)
	{
		E[0][0] = 0.0; E[0][1] = 0.0; E[0][2] = 0.0;

		//произведение соответствует правой тройке векторов
		pH = E[2][1]*E[1][2] - E[2][2]*E[1][1];
		pK = E[2][2]*E[1][0] - E[2][0]*E[1][2];
		pL = E[2][0]*E[1][1] - E[2][1]*E[1][0];

		E[0][0] = pH*OG[0][0]+pK*OG[1][0]+pL*OG[2][0];
		E[0][1] = pH*OG[0][1]+pK*OG[1][1]+pL*OG[2][1];
		E[0][2] = pH*OG[0][2]+pK*OG[1][2]+pL*OG[2][2];
	}

	return TRUE;
}

BOOL CLaueDlg::eDirectCalcOld(double E[3][3], double G[3][3])
{
	double OG[3][3]={{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};//обр. метр. тензор
	BOOL check=TRUE;

	double P11=E[1][1]*E[2][2]-E[1][2]*E[2][1];
	double P12=E[1][2]*E[2][0]-E[1][0]*E[2][2];
	double P13=E[1][0]*E[2][1]-E[1][1]*E[2][0];

	check = invMatrix(G, OG);
	if(!check)
		return FALSE;

	E[0][0]=P11*OG[0][0]+P12*OG[1][0]+P13*OG[2][0];
	E[0][1]=P11*OG[0][1]+P12*OG[1][1]+P13*OG[2][1];
	E[0][2]=P11*OG[0][2]+P12*OG[1][2]+P13*OG[2][2];

	double DET=determ(E);
	if(!DET)
	{
		AfxMessageBox("Ошибка(003)!Вектора ориентировки. Определитель равен 0! Дальнейшая работа невозможна!",
			MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	else
	return TRUE;
}
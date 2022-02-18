void CLaueDlg::LaueAngleTurn()
{
	UpdateData();//

	//�������� ���������� ToolTip ���������
	int id = reflexID;
	while(id > 1)
	{
		m_pReflexTips->DelTool(this, id);
		id--;
	}
	//

	//���� �� �������� ����������� � �������
	double alf=alfa*M_PI/180;
	double bet=beta*M_PI/180;
	double gam=gamma*M_PI/180;
	//

	//��� ������ �� ����� ������� ����������� ����������
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
		AfxMessageBox("������(101)! ������������ ������� �������� �������! ���������� ������ ����������!",
			MB_OK|MB_ICONSTOP);

    //��������� ������� �������� �������� �������� ������� �� ������� 
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

	//�������� ���� �� -Knots �� +Knots
	for(int h=-Knots; h<=Knots; h++)
	{
		for(int k=-Knots; k<=Knots; k++)
		{
			for(int l=-Knots; l<=Knots; l++)
			{
				//int Hsum=h*h+k*k+l*l;//
				//if(Hsum<=52)//
				{
					if(StructFactor==1)//����������� ������
					{
						int H=h*h+k*k+l*l;//����� ��������� �������� ����� �������� �������
						if(H%2==0)//������� �� ��� �������
						{
							reflexCalc(h, k, l);//������� ������� ���������
						}
					}
					//����������� ������
					if(StructFactor!=1&&StructFactor!=0)//������� �� ���������� �������
					{
						reflexCalc(h, k, l);//������� ������� ���������
					}
					if(StructFactor==0)//����������� ������
					{
						//������� �� ��� �������
						int ch1=abs(h%2), ch2=abs(k%2), ch3=abs(l%2);
						if((ch1==ch2)&&(ch1==ch3)&&
							(ch2==ch1)&&(ch2==ch3)&&
							(ch3==ch1)&&(ch3==ch2))
						{
							reflexCalc(h, k, l);//������� ������� ���������
						}
					}
				}
			}
		}
	}
	//
	Invalidate(NULL);//��������� ������� ���������
	//
	return;
}


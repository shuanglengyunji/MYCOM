#pragma once
#include "mycomdlg.h"

class MYCOMMAND
{
public:
	MYCOMMAND(void)
	{
		Head1 = Head2 = Functionword = Len = Command_Data1 = Command_Data2 = Command_Data3 = Command_Data4 = SUM = 0;
	}

	~MYCOMMAND(void)
	{

	}
	
	BYTE Head1;				//֡ͷ1
	BYTE Head2;				//֡ͷ2
	BYTE Functionword;		//������
	BYTE Len;				//����
	BYTE Command_Data1;		//�ڲ�ָ������1
	BYTE Command_Data2;		//�ڲ�ָ������2
	BYTE Command_Data3;		//�ڲ�ָ������3
	BYTE Command_Data4;		//�ڲ�ָ������4
	BYTE SUM;				//�ܺ�У��

	void Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1);
	void Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1,BYTE t_Data2);
	void Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1,BYTE t_Data2,BYTE t_Data3);
	void Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1,BYTE t_Data2,BYTE t_Data3,BYTE t_Data4);
	
	void Send_To_InputComm();	//��ɿط���ָ��
	void Send_To_OutputComm();	//�����վ����ָ��
};


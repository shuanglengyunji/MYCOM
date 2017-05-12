#pragma once
#include "mycomdlg.h"

class MYCOMMAND :
	public CMYCOMDlg
{
public:
	MYCOMMAND(void);
	MYCOMMAND(
		BYTE t_Head1,				//֡ͷ1
		BYTE t_Head2,				//֡ͷ2
		BYTE t_Functionword,		//������
		BYTE t_Len,				//����
		BYTE t_Command_Number,	//�ڲ�ָ���
		BYTE t_Command_Data		//�ڲ�ָ������
		);	//��ɿط���ָ��
	~MYCOMMAND(void);
	
	BYTE Head1;				//֡ͷ1
	BYTE Head2;				//֡ͷ2
	BYTE Functionword;		//������
	BYTE Len;				//����
	BYTE Command_Number;	//�ڲ�ָ���
	BYTE Command_Data;		//�ڲ�ָ������
	BYTE SUM;				//�ܺ�У��

	void Updata(	
		BYTE t_Head1,				//֡ͷ1
		BYTE t_Head2,				//֡ͷ2
		BYTE t_Functionword,		//������
		BYTE t_Len,				//����
		BYTE t_Command_Number,	//�ڲ�ָ���
		BYTE t_Command_Data		//�ڲ�ָ������
	);
	
	void Send_To_InputComm();	//��ɿط���ָ��
	void Send_To_OutputComm();	//�����վ����ָ��
};


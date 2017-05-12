#include "StdAfx.h"
#include "MYCOMMAND.h"
#include "CMSComm.h"

//�๹�캯��
MYCOMMAND::MYCOMMAND(void)
{
	Head1 = 0;				//֡ͷ1
	Head2 = 0;				//֡ͷ2
	Functionword = 0;		//������
	Len = 0;				//����
	Command_Number = 0;		//�ڲ�ָ���
	Command_Data = 0;		//�ڲ�ָ������
	SUM = 0;				//�ܺ�У��
}

//�๹�캯��
MYCOMMAND::MYCOMMAND(
		BYTE t_Head1,				//֡ͷ1
		BYTE t_Head2,				//֡ͷ2
		BYTE t_Functionword,		//������
		BYTE t_Len,					//����
		BYTE t_Command_Number,		//�ڲ�ָ���
		BYTE t_Command_Data			//�ڲ�ָ������
		)
{
	Head1 = t_Head1;				//֡ͷ1
	Head2 = t_Head2;				//֡ͷ2
	Functionword = t_Functionword;		//������
	Len = t_Len;						//����
	Command_Number = t_Command_Number;	//�ڲ�ָ���
	Command_Data = t_Command_Data;		//�ڲ�ָ������

	SUM = Head1+Head2+Functionword+Len+Command_Number+Command_Data;	//�ܺ�У��
}

//������
MYCOMMAND::~MYCOMMAND(void)
{
}

void MYCOMMAND::Updata(
		BYTE t_Head1,				//֡ͷ1
		BYTE t_Head2,				//֡ͷ2
		BYTE t_Functionword,		//������
		BYTE t_Len,				//����
		BYTE t_Command_Number,	//�ڲ�ָ���
		BYTE t_Command_Data		//�ڲ�ָ������
		)	//��ɿط���ָ��
{
	Head1 = t_Head1;				//֡ͷ1
	Head2 = t_Head2;				//֡ͷ2
	Functionword = t_Functionword;		//������
	Len = t_Len;						//����
	Command_Number = t_Command_Number;	//�ڲ�ָ���
	Command_Data = t_Command_Data;		//�ڲ�ָ������

	SUM = Head1+Head2+Functionword+Len+Command_Number+Command_Data;	//�ܺ�У��
}

//�����վ����ָ��
void MYCOMMAND::Send_To_InputComm()	
{
	CByteArray SendArray;
	SendArray.RemoveAll();
	SendArray.SetSize(7);		//�ܳ���7�ֽڣ�֡ͷ��2�� + �����֣�1�� + ���ȣ�1��+ ָ�2��+ �ܺ�У�飨1��
	SendArray.SetAt(0,Head1);	//֡ͷ
	SendArray.SetAt(1,Head2);	//֡ͷ
	SendArray.SetAt(2,Functionword);	//������
	SendArray.SetAt(3,Len);	//���ȣ�ָ���2�ֽڣ�
	SendArray.SetAt(4,Command_Number);	//ָ���ڲ����
	SendArray.SetAt(5,Command_Data);	//ָ����������
	SendArray.SetAt(6,SUM);

	InputComm.put_Output(COleVariant(SendArray));	//���͵�Input�ڣ��ɿؿڣ�
}

//�����վ����ָ��
void MYCOMMAND::Send_To_OutputComm()	
{
	CByteArray SendArray;
	SendArray.RemoveAll();
	SendArray.SetSize(7);		//�ܳ���7�ֽڣ�֡ͷ��2�� + �����֣�1�� + ���ȣ�1��+ ָ�2��+ �ܺ�У�飨1��
	SendArray.SetAt(0,Head1);	//֡ͷ
	SendArray.SetAt(1,Head2);	//֡ͷ
	SendArray.SetAt(2,Functionword);	//������
	SendArray.SetAt(3,Len);	//���ȣ�ָ���2�ֽڣ�
	SendArray.SetAt(4,Command_Number);	//ָ���ڲ����
	SendArray.SetAt(5,Command_Data);	//ָ����������
	SendArray.SetAt(6,SUM);
	OutputComm.put_Output(COleVariant(SendArray));	//���͵�Input�ڣ��ɿؿڣ�
}


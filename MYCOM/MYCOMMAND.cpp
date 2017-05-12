#include "StdAfx.h"
#include "MYCOMMAND.h"
#include "CMSComm.h"

extern CMYCOMDlg* mydlg;

void MYCOMMAND::Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1)
{
	Head1 = t_Head1;				//֡ͷ1
	Head2 = t_Head2;				//֡ͷ2
	Functionword = t_Functionword;		//������
	Len = 1;
	Command_Data1 = t_Data1;
	SUM = Head1+Head2+Functionword+Len+Command_Data1;
}

void MYCOMMAND::Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1,BYTE t_Data2)
{
	Head1 = t_Head1;				//֡ͷ1
	Head2 = t_Head2;				//֡ͷ2
	Functionword = t_Functionword;		//������
	Len = 2;
	Command_Data1 = t_Data1;
	Command_Data2 = t_Data2;
	SUM = Head1+Head2+Functionword+Len+Command_Data1+Command_Data2;
}

void MYCOMMAND::Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1,BYTE t_Data2,BYTE t_Data3)
{
	Head1 = t_Head1;				//֡ͷ1
	Head2 = t_Head2;				//֡ͷ2
	Functionword = t_Functionword;		//������
	Len = 3;
	Command_Data1 = t_Data1;
	Command_Data2 = t_Data2;
	Command_Data3 = t_Data3;
	SUM = Head1+Head2+Functionword+Len+Command_Data1+Command_Data2+Command_Data3;
}

void MYCOMMAND::Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1,BYTE t_Data2,BYTE t_Data3,BYTE t_Data4)
{
	Head1 = t_Head1;				//֡ͷ1
	Head2 = t_Head2;				//֡ͷ2
	Functionword = t_Functionword;		//������
	Len = 4;
	Command_Data1 = t_Data1;
	Command_Data2 = t_Data2;
	Command_Data3 = t_Data3;
	Command_Data4 = t_Data4;
	SUM = Head1+Head2+Functionword+Len+Command_Data1+Command_Data2+Command_Data3+Command_Data4;
}

//�����վ����ָ��
void MYCOMMAND::Send_To_InputComm()	
{
	CByteArray SendArray;
	SendArray.RemoveAll();
	SendArray.SetSize(Len+5);		//�ܳ���7�ֽڣ�֡ͷ��2�� + �����֣�1�� + ���ȣ�1��+ ָ�2��+ �ܺ�У�飨1��
	SendArray.SetAt(0,Head1);	//֡ͷ
	SendArray.SetAt(1,Head2);	//֡ͷ
	SendArray.SetAt(2,Functionword);	//������
	SendArray.SetAt(3,Len);	//���ȣ�ָ���2�ֽڣ�
	SendArray.SetAt(3+Len+1,SUM);	//���ȣ�ָ���2�ֽڣ�
	int i = 0;
	switch(Len)
	{
	case 4:
		SendArray.SetAt(3+Len-i,Command_Data4);
		i++;
	case 3:
		SendArray.SetAt(3+Len-i,Command_Data3);
		i++;
	case 2:
		SendArray.SetAt(3+Len-i,Command_Data2);
		i++;
	case 1:
		SendArray.SetAt(3+Len-i,Command_Data1);
		break;
	default:
		printf("ָ���������\n");
	}

	mydlg->InputComm.put_Output(COleVariant(SendArray));	//���͵�Input�ڣ��ɿؿڣ�
}

//�����վ����ָ��
void MYCOMMAND::Send_To_OutputComm()	
{
	CByteArray SendArray;
	SendArray.RemoveAll();
	SendArray.SetSize(Len+5);		//�ܳ���7�ֽڣ�֡ͷ��2�� + �����֣�1�� + ���ȣ�1��+ ָ�2��+ �ܺ�У�飨1��
	SendArray.SetAt(0,Head1);	//֡ͷ
	SendArray.SetAt(1,Head2);	//֡ͷ
	SendArray.SetAt(2,Functionword);	//������
	SendArray.SetAt(3,Len);	//���ȣ�ָ���2�ֽڣ�
	SendArray.SetAt(3+Len+1,SUM);	//���ȣ�ָ���2�ֽڣ�
	int i = 0;
	switch(Len)
	{
	case 4:
		SendArray.SetAt(3+Len-i,Command_Data4);
		i++;
	case 3:
		SendArray.SetAt(3+Len-i,Command_Data3);
		i++;
	case 2:
		SendArray.SetAt(3+Len-i,Command_Data2);
		i++;
	case 1:
		SendArray.SetAt(3+Len-i,Command_Data1);
		break;
	default:
		printf("ָ���������\n");
	}
	mydlg->OutputComm.put_Output(COleVariant(SendArray));	//���͵�Input�ڣ��ɿؿڣ�
}


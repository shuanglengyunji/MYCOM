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
	
	BYTE Head1;				//帧头1
	BYTE Head2;				//帧头2
	BYTE Functionword;		//功能字
	BYTE Len;				//长度
	BYTE Command_Data1;		//内部指令内容1
	BYTE Command_Data2;		//内部指令内容2
	BYTE Command_Data3;		//内部指令内容3
	BYTE Command_Data4;		//内部指令内容4
	BYTE SUM;				//总和校验

	void Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1);
	void Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1,BYTE t_Data2);
	void Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1,BYTE t_Data2,BYTE t_Data3);
	void Updata(BYTE t_Head1,BYTE t_Head2,BYTE t_Functionword,BYTE t_Data1,BYTE t_Data2,BYTE t_Data3,BYTE t_Data4);
	
	void Send_To_InputComm();	//向飞控发送指令
	void Send_To_OutputComm();	//向地面站发送指令
};


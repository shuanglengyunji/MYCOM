#pragma once
#include "mycomdlg.h"

class MYCOMMAND :
	public CMYCOMDlg
{
public:
	MYCOMMAND(void);
	MYCOMMAND(
		BYTE t_Head1,				//帧头1
		BYTE t_Head2,				//帧头2
		BYTE t_Functionword,		//功能字
		BYTE t_Len,				//长度
		BYTE t_Command_Number,	//内部指令号
		BYTE t_Command_Data		//内部指令内容
		);	//向飞控发送指令
	~MYCOMMAND(void);
	
	BYTE Head1;				//帧头1
	BYTE Head2;				//帧头2
	BYTE Functionword;		//功能字
	BYTE Len;				//长度
	BYTE Command_Number;	//内部指令号
	BYTE Command_Data;		//内部指令内容
	BYTE SUM;				//总和校验

	void Updata(	
		BYTE t_Head1,				//帧头1
		BYTE t_Head2,				//帧头2
		BYTE t_Functionword,		//功能字
		BYTE t_Len,				//长度
		BYTE t_Command_Number,	//内部指令号
		BYTE t_Command_Data		//内部指令内容
	);
	
	void Send_To_InputComm();	//向飞控发送指令
	void Send_To_OutputComm();	//向地面站发送指令
};


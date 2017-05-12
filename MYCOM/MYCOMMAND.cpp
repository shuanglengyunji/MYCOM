#include "StdAfx.h"
#include "MYCOMMAND.h"
#include "CMSComm.h"

//类构造函数
MYCOMMAND::MYCOMMAND(void)
{
	Head1 = 0;				//帧头1
	Head2 = 0;				//帧头2
	Functionword = 0;		//功能字
	Len = 0;				//长度
	Command_Number = 0;		//内部指令号
	Command_Data = 0;		//内部指令内容
	SUM = 0;				//总和校验
}

//类构造函数
MYCOMMAND::MYCOMMAND(
		BYTE t_Head1,				//帧头1
		BYTE t_Head2,				//帧头2
		BYTE t_Functionword,		//功能字
		BYTE t_Len,					//长度
		BYTE t_Command_Number,		//内部指令号
		BYTE t_Command_Data			//内部指令内容
		)
{
	Head1 = t_Head1;				//帧头1
	Head2 = t_Head2;				//帧头2
	Functionword = t_Functionword;		//功能字
	Len = t_Len;						//长度
	Command_Number = t_Command_Number;	//内部指令号
	Command_Data = t_Command_Data;		//内部指令内容

	SUM = Head1+Head2+Functionword+Len+Command_Number+Command_Data;	//总和校验
}

//类销毁
MYCOMMAND::~MYCOMMAND(void)
{
}

void MYCOMMAND::Updata(
		BYTE t_Head1,				//帧头1
		BYTE t_Head2,				//帧头2
		BYTE t_Functionword,		//功能字
		BYTE t_Len,				//长度
		BYTE t_Command_Number,	//内部指令号
		BYTE t_Command_Data		//内部指令内容
		)	//向飞控发送指令
{
	Head1 = t_Head1;				//帧头1
	Head2 = t_Head2;				//帧头2
	Functionword = t_Functionword;		//功能字
	Len = t_Len;						//长度
	Command_Number = t_Command_Number;	//内部指令号
	Command_Data = t_Command_Data;		//内部指令内容

	SUM = Head1+Head2+Functionword+Len+Command_Number+Command_Data;	//总和校验
}

//向地面站发送指令
void MYCOMMAND::Send_To_InputComm()	
{
	CByteArray SendArray;
	SendArray.RemoveAll();
	SendArray.SetSize(7);		//总长度7字节：帧头（2） + 功能字（1） + 长度（1）+ 指令（2）+ 总和校验（1）
	SendArray.SetAt(0,Head1);	//帧头
	SendArray.SetAt(1,Head2);	//帧头
	SendArray.SetAt(2,Functionword);	//功能字
	SendArray.SetAt(3,Len);	//长度（指令长度2字节）
	SendArray.SetAt(4,Command_Number);	//指令内部编号
	SendArray.SetAt(5,Command_Data);	//指令内容数据
	SendArray.SetAt(6,SUM);

	InputComm.put_Output(COleVariant(SendArray));	//发送到Input口（飞控口）
}

//向地面站发送指令
void MYCOMMAND::Send_To_OutputComm()	
{
	CByteArray SendArray;
	SendArray.RemoveAll();
	SendArray.SetSize(7);		//总长度7字节：帧头（2） + 功能字（1） + 长度（1）+ 指令（2）+ 总和校验（1）
	SendArray.SetAt(0,Head1);	//帧头
	SendArray.SetAt(1,Head2);	//帧头
	SendArray.SetAt(2,Functionword);	//功能字
	SendArray.SetAt(3,Len);	//长度（指令长度2字节）
	SendArray.SetAt(4,Command_Number);	//指令内部编号
	SendArray.SetAt(5,Command_Data);	//指令内容数据
	SendArray.SetAt(6,SUM);
	OutputComm.put_Output(COleVariant(SendArray));	//发送到Input口（飞控口）
}


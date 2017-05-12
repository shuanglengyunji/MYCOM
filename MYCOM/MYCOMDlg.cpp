
// MYCOMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MYCOM.h"
#include "MYCOMDlg.h"
#include "afxdialogex.h"
#include "MYCOMMAND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMYCOMDlg 对话框




CMYCOMDlg::CMYCOMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMYCOMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMYCOMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMYCOMDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_COMOPEN, &CMYCOMDlg::OnBnClickedComopen)
	ON_CBN_SELCHANGE(IDC_BAUDRATE, &CMYCOMDlg::OnCbnSelchangeBaudrate)
	ON_CBN_SELCHANGE(IDC_PORTNUM, &CMYCOMDlg::OnCbnSelchangePortnum)
	ON_CBN_SELCHANGE(IDC_PORTNUM_OUT, &CMYCOMDlg::OnCbnSelchangePortnumOut)
	ON_BN_CLICKED(IDC_MESSAGE1, &CMYCOMDlg::OnBnClickedMessage1)
END_MESSAGE_MAP()


// CMYCOMDlg 消息处理程序

BOOL CMYCOMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//打开控制台
	AllocConsole();
	freopen( "CONOUT$","w",stdout);
	printf("打开控制台\n");

	//初始化界面组件
	InitComboBox();	//下拉列表初始化

	//初始化输入串口控件
	if(InputCommInit() == -1)
	{
		AfxMessageBox("创建InputComm对象失败！");
		return -1;
	}

	if(OutputCommInit() == -1)
	{
		AfxMessageBox("创建OutputComm对象失败！");
		return -1;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMYCOMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMYCOMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//*********************************************************************
//控件相关函数

//下拉列表初始化
void CMYCOMDlg::InitComboBox()
{
	CComboBox * comboBox1 = (CComboBox *)GetDlgItem(IDC_BAUDRATE);
	comboBox1->ResetContent();
	comboBox1->AddString("57600");
	comboBox1->AddString("115200");
	comboBox1->AddString("256000");
	comboBox1->AddString("500000");

	comboBox1 = (CComboBox *)GetDlgItem(IDC_PORTNUM);
	comboBox1->ResetContent();
	comboBox1->AddString("COM1");
	comboBox1->AddString("COM2");
	comboBox1->AddString("COM3");
	comboBox1->AddString("COM4");
	comboBox1->AddString("COM5");
	comboBox1->AddString("COM6");
	comboBox1->AddString("COM7");
	comboBox1->AddString("COM8");
	comboBox1->AddString("COM9");
	comboBox1->AddString("COM10");
	comboBox1->AddString("COM11");
	comboBox1->AddString("COM12");
	comboBox1->AddString("COM13");
	comboBox1->AddString("COM14");
	comboBox1->AddString("COM15");
	comboBox1->AddString("COM16");

	comboBox1 = (CComboBox *)GetDlgItem(IDC_PORTNUM_OUT);
	comboBox1->ResetContent();
	comboBox1->AddString("COM1");
	comboBox1->AddString("COM2");
	comboBox1->AddString("COM3");
	comboBox1->AddString("COM4");
	comboBox1->AddString("COM5");
	comboBox1->AddString("COM6");
	comboBox1->AddString("COM7");
	comboBox1->AddString("COM8");
	comboBox1->AddString("COM9");
	comboBox1->AddString("COM10");
	comboBox1->AddString("COM11");
	comboBox1->AddString("COM12");
	comboBox1->AddString("COM13");
	comboBox1->AddString("COM14");
	comboBox1->AddString("COM15");
	comboBox1->AddString("COM16");
}

//***************************************************************************
//串口相关函数

//对飞控串口初始化
int CMYCOMDlg::InputCommInit()
{
	//配置并初始化MSCOMM对象
	DWORD style = WS_VISIBLE|WS_CHILD;
	if(!InputComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM))	//Creat函数中要输入控件ID（IDC_MSCOMM），将变量与控件关联
	{
		return -1;	//异常
	}
	
	inputCommstatus = 0;	//串口状态为0（未打开）
	myBuadRate = 0;	//默认串口波特率归零，直接打开串口会报错
	inputPortNum = 0;

	//接收配置
	InputComm.put_InBufferSize(1024);	//设置接受缓冲区大小
	InputComm.put_InBufferCount(0);		//清空接收缓冲区
	InputComm.put_InputMode(1);			//以二进制方式接收
	InputComm.put_InputLen(0);			//设置每次读取的长度

	//发送配置
	InputComm.put_OutBufferSize(1024);	//设置发送缓冲区大小
	InputComm.put_OutBufferCount(0);	//清空发送缓冲区

	//配置OnComm事件
	InputComm.put_RThreshold(1);		//收到20个字符时会产生OnComm事件

	return 0;	//正常
}

//对地面站串口初始化
int CMYCOMDlg::OutputCommInit()
{
	//配置并初始化MSCOMM对象
	DWORD style = WS_VISIBLE|WS_CHILD;
	if(!OutputComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM_OUT))
	{
		return -1;	//异常
	}
	
	//初始化相关变量
	outputCommstatus = 0;	//串口状态为0（未打开）
	myBuadRate = 0;	//默认串口波特率归零，直接打开串口会报错
	outputPortNum = 0;

	//接收配置
	OutputComm.put_InBufferSize(1024);	//设置接受缓冲区大小
	OutputComm.put_InBufferCount(0);		//清空接收缓冲区
	OutputComm.put_InputMode(1);			//以二进制方式接收
	OutputComm.put_InputLen(0);			//设置每次读取的长度

	//发送配置
	OutputComm.put_OutBufferSize(1024);	//设置发送缓冲区大小
	OutputComm.put_OutBufferCount(0);	//清空发送缓冲区

	//配置OnComm事件
	OutputComm.put_RThreshold(1);		//收到20个字符时会产生OnComm事件

	return 0;	//正常
}

//对飞控端口号选择下拉菜单
void CMYCOMDlg::OnCbnSelchangePortnum()
{
	// TODO: 在此添加控件通知处理程序代码

	CComboBox * box = (CComboBox *)GetDlgItem(IDC_PORTNUM);

	//获取下拉列表内容序号及内容
	CString strWeb;
    int nSel;   
    // 获取组合框控件的列表框中选中项的索引
    nSel = (*box).GetCurSel();
    // 根据选中项索引获取该项字符串
    (*box).GetLBText(nSel, strWeb);
	printf("%d,%s\n",nSel,(LPCTSTR)strWeb);

	//设置串口号
	inputPortNum = nSel + 1;
}

//对地面站端口号选择下拉菜单
void CMYCOMDlg::OnCbnSelchangePortnumOut()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox * box = (CComboBox *)GetDlgItem(IDC_PORTNUM_OUT);

	//获取下拉列表内容序号及内容
	CString strWeb;
    int nSel;   
    // 获取组合框控件的列表框中选中项的索引
    nSel = (*box).GetCurSel();
    // 根据选中项索引获取该项字符串
    (*box).GetLBText(nSel, strWeb);
	printf("%d,%s\n",nSel,(LPCTSTR)strWeb);

	//设置串口号
	outputPortNum = nSel + 1;
}

//全局波特率选择下拉菜单
void CMYCOMDlg::OnCbnSelchangeBaudrate()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox * box = (CComboBox *)GetDlgItem(IDC_BAUDRATE);

	//获取下拉列表内容序号及内容
	CString strWeb;
    int nSel;   
    // 获取组合框控件的列表框中选中项的索引
    nSel = (*box).GetCurSel();
    // 根据选中项索引获取该项字符串
    (*box).GetLBText(nSel, strWeb);
	printf("%d,%s\n",nSel,(LPCTSTR)strWeb);

	//设置波特率参数
	switch(nSel)
	{
	case 0:
		myBuadRate = 57600;
		break;
	case 1:
		myBuadRate = 115200;
		break;
	case 2:
		myBuadRate = 256000;
		break;
	case 3:
		myBuadRate = 500000;
		break;
	default:
		myBuadRate = 0;
	}
}

//打开串口/关闭按钮
void CMYCOMDlg::OnBnClickedComopen()
{
	// TODO: 在此添加控件通知处理程序代码
	if(inputCommstatus == 1 || outputCommstatus == 1)	//串口已经打开
	{
		//关闭串口
		if(inputCommstatus == 1)
		{
			InputComm.put_PortOpen(0);	//此函数没有返回值
			printf("对飞控COM%d已关闭\n",inputPortNum);
			inputCommstatus = 0;
		}

		if(outputCommstatus == 1)
		{
			OutputComm.put_PortOpen(0);
			printf("对地面站COM%d已关闭\n",outputPortNum);
			outputCommstatus = 0;
		}

		if(inputCommstatus == 0 && outputCommstatus == 0)
			GetDlgItem(ID_COMOPEN)->SetWindowText("打开串口");

		return;
	}

	//设置串口号
	InputComm.put_CommPort(inputPortNum);	//设置对飞控串口号
	OutputComm.put_CommPort(outputPortNum);	//设置对地面站串口号

	//设置串口模式
	switch(myBuadRate)
	{
	case 57600:
		InputComm.put_Settings(_T("57600,n,8,1"));
		OutputComm.put_Settings(_T("57600,n,8,1"));
		break;
	case 115200:
		InputComm.put_Settings(_T("115200,n,8,1"));
		OutputComm.put_Settings(_T("115200,n,8,1"));
		break;
	case 256000:
		InputComm.put_Settings(_T("256000,n,8,1"));
		OutputComm.put_Settings(_T("256000,n,8,1"));
		break;
	case 500000:
		InputComm.put_Settings(_T("500000,n,8,1"));
		OutputComm.put_Settings(_T("500000,n,8,1"));
		break;
	default:
		InputComm.put_Settings(_T("0,n,8,1"));
		OutputComm.put_Settings(_T("0,n,8,1"));
	}

	//打开串口
	InputComm.put_PortOpen(1);	//此函数没有返回值
	printf("对飞控COM%d已打开,波特率%d\n",inputPortNum,myBuadRate);
	inputCommstatus = 1;
	GetDlgItem(ID_COMOPEN)->SetWindowText("关闭串口");

	OutputComm.put_PortOpen(1);	//此函数没有返回值
	printf("对地面站COM%d已打开,波特率%d\n",outputPortNum,myBuadRate);
	outputCommstatus = 1;
	GetDlgItem(ID_COMOPEN)->SetWindowText("关闭串口");
}

void CMYCOMDlg::InputReceiveHandle(BYTE data)
{
	printf("飞控：%x\n",data);

}

void CMYCOMDlg::OutputReceiveHandle(BYTE data)
{
	printf("地面站：%x\n",data);
}

BEGIN_EVENTSINK_MAP(CMYCOMDlg, CDialogEx)
	ON_EVENT(CMYCOMDlg, IDC_MSCOMM_OUT, 1, CMYCOMDlg::OnCommMscommOut, VTS_NONE)
	ON_EVENT(CMYCOMDlg, IDC_MSCOMM, 1, CMYCOMDlg::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()


void CMYCOMDlg::OnCommMscomm()
{
	// TODO: 在此处添加消息处理程序代码

	VARIANT input;
	COleSafeArray safeinput;
	long len;
	BYTE rxdata[2048];

	//获取OnComm事件编号
	short num;
	num = InputComm.get_CommEvent();

	CByteArray SendArray;	//发送数据用的结构体变量
	SendArray.RemoveAll();

	switch(num)
	{
	case 2:
		input = InputComm.get_Input();
		safeinput = input;
		len = safeinput.GetOneDimSize();	//获取长度
		for(long k=0;k<len;k++)				//将输入数据存入数组rxdata
			safeinput.GetElement(&k,rxdata+k);
		
		//转发
		SendArray.SetSize(len);
		for(int k=0;k<len;k++)
		{
			SendArray.SetAt(k,*(rxdata+k));
		}
		OutputComm.put_Output(COleVariant(SendArray));	//转发到output口

		//数据处理
		for(int k=0;k<len;k++)
		{
			InputReceiveHandle(*(rxdata+k));
		}

		break;
	default:
		printf("InputComm Event,NO.%d\n",num);
	}
}


void CMYCOMDlg::OnCommMscommOut()
{
	// TODO: 在此处添加消息处理程序代码
	VARIANT input;
	COleSafeArray safeinput;
	long len;
	BYTE rxdata[2048];

	//获取OnComm事件编号
	short num;
	num = OutputComm.get_CommEvent();

	CByteArray SendArray;	//发送数据用的结构体变量
	SendArray.RemoveAll();

	switch(num)
	{
	case 2:
		input = OutputComm.get_Input();
		safeinput = input;
		len = safeinput.GetOneDimSize();	//获取长度
		for(long k=0;k<len;k++)				//将输入数据存入数组rxdata
			safeinput.GetElement(&k,rxdata+k);

		//数据转发
		SendArray.SetSize(len);
		for(int k=0;k<len;k++)
		{
			SendArray.SetAt(k,*(rxdata+k));
		}
		InputComm.put_Output(COleVariant(SendArray));	//转发到input口

		//数据处理
		for(int k=0;k<len;k++)
		{
			OutputReceiveHandle(*(rxdata+k));
		}

		break;
	default:
		printf("OutputComm Event,NO.%d\n",num);
	}
}

void CMYCOMDlg::OnBnClickedMessage1()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE Head1 = 0xAA;				//帧头1
	BYTE Head2 = 0xAF;				//帧头2
	BYTE Functionword = 0x01;		//功能字
	BYTE Len = 0x01;				//长度
	BYTE Command_Number = 0x02;	//内部指令号
	BYTE SUM = Head1+Head2+Functionword+Len+Command_Number;

	CByteArray SendArray;
	SendArray.RemoveAll();
	SendArray.SetSize(6);		//总长度7字节：帧头（2） + 功能字（1） + 长度（1）+ 指令（2）+ 总和校验（1）
	SendArray.SetAt(0,Head1);	//帧头
	SendArray.SetAt(1,Head2);	//帧头
	SendArray.SetAt(2,Functionword);	//功能字
	SendArray.SetAt(3,Len);	//长度（指令长度2字节）
	SendArray.SetAt(4,Command_Number);	//指令内部编号
	SendArray.SetAt(5,SUM);

	OutputComm.put_Output(COleVariant(SendArray));	//发送到Input口（飞控口）
}

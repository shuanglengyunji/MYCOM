
// MYCOMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MYCOM.h"
#include "MYCOMDlg.h"
#include "afxdialogex.h"
#include "MYCOMMAND.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMYCOMDlg �Ի���




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


// CMYCOMDlg ��Ϣ�������

BOOL CMYCOMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//�򿪿���̨
	AllocConsole();
	freopen( "CONOUT$","w",stdout);
	printf("�򿪿���̨\n");

	//��ʼ���������
	InitComboBox();	//�����б��ʼ��

	//��ʼ�����봮�ڿؼ�
	if(InputCommInit() == -1)
	{
		AfxMessageBox("����InputComm����ʧ�ܣ�");
		return -1;
	}

	if(OutputCommInit() == -1)
	{
		AfxMessageBox("����OutputComm����ʧ�ܣ�");
		return -1;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMYCOMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMYCOMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//*********************************************************************
//�ؼ���غ���

//�����б��ʼ��
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
//������غ���

//�Էɿش��ڳ�ʼ��
int CMYCOMDlg::InputCommInit()
{
	//���ò���ʼ��MSCOMM����
	DWORD style = WS_VISIBLE|WS_CHILD;
	if(!InputComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM))	//Creat������Ҫ����ؼ�ID��IDC_MSCOMM������������ؼ�����
	{
		return -1;	//�쳣
	}
	
	inputCommstatus = 0;	//����״̬Ϊ0��δ�򿪣�
	myBuadRate = 0;	//Ĭ�ϴ��ڲ����ʹ��㣬ֱ�Ӵ򿪴��ڻᱨ��
	inputPortNum = 0;

	//��������
	InputComm.put_InBufferSize(1024);	//���ý��ܻ�������С
	InputComm.put_InBufferCount(0);		//��ս��ջ�����
	InputComm.put_InputMode(1);			//�Զ����Ʒ�ʽ����
	InputComm.put_InputLen(0);			//����ÿ�ζ�ȡ�ĳ���

	//��������
	InputComm.put_OutBufferSize(1024);	//���÷��ͻ�������С
	InputComm.put_OutBufferCount(0);	//��շ��ͻ�����

	//����OnComm�¼�
	InputComm.put_RThreshold(1);		//�յ�20���ַ�ʱ�����OnComm�¼�

	return 0;	//����
}

//�Ե���վ���ڳ�ʼ��
int CMYCOMDlg::OutputCommInit()
{
	//���ò���ʼ��MSCOMM����
	DWORD style = WS_VISIBLE|WS_CHILD;
	if(!OutputComm.Create(NULL,style,CRect(0,0,0,0),this,IDC_MSCOMM_OUT))
	{
		return -1;	//�쳣
	}
	
	//��ʼ����ر���
	outputCommstatus = 0;	//����״̬Ϊ0��δ�򿪣�
	myBuadRate = 0;	//Ĭ�ϴ��ڲ����ʹ��㣬ֱ�Ӵ򿪴��ڻᱨ��
	outputPortNum = 0;

	//��������
	OutputComm.put_InBufferSize(1024);	//���ý��ܻ�������С
	OutputComm.put_InBufferCount(0);		//��ս��ջ�����
	OutputComm.put_InputMode(1);			//�Զ����Ʒ�ʽ����
	OutputComm.put_InputLen(0);			//����ÿ�ζ�ȡ�ĳ���

	//��������
	OutputComm.put_OutBufferSize(1024);	//���÷��ͻ�������С
	OutputComm.put_OutBufferCount(0);	//��շ��ͻ�����

	//����OnComm�¼�
	OutputComm.put_RThreshold(1);		//�յ�20���ַ�ʱ�����OnComm�¼�

	return 0;	//����
}

//�Էɿض˿ں�ѡ�������˵�
void CMYCOMDlg::OnCbnSelchangePortnum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CComboBox * box = (CComboBox *)GetDlgItem(IDC_PORTNUM);

	//��ȡ�����б�������ż�����
	CString strWeb;
    int nSel;   
    // ��ȡ��Ͽ�ؼ����б����ѡ���������
    nSel = (*box).GetCurSel();
    // ����ѡ����������ȡ�����ַ���
    (*box).GetLBText(nSel, strWeb);
	printf("%d,%s\n",nSel,(LPCTSTR)strWeb);

	//���ô��ں�
	inputPortNum = nSel + 1;
}

//�Ե���վ�˿ں�ѡ�������˵�
void CMYCOMDlg::OnCbnSelchangePortnumOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComboBox * box = (CComboBox *)GetDlgItem(IDC_PORTNUM_OUT);

	//��ȡ�����б�������ż�����
	CString strWeb;
    int nSel;   
    // ��ȡ��Ͽ�ؼ����б����ѡ���������
    nSel = (*box).GetCurSel();
    // ����ѡ����������ȡ�����ַ���
    (*box).GetLBText(nSel, strWeb);
	printf("%d,%s\n",nSel,(LPCTSTR)strWeb);

	//���ô��ں�
	outputPortNum = nSel + 1;
}

//ȫ�ֲ�����ѡ�������˵�
void CMYCOMDlg::OnCbnSelchangeBaudrate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComboBox * box = (CComboBox *)GetDlgItem(IDC_BAUDRATE);

	//��ȡ�����б�������ż�����
	CString strWeb;
    int nSel;   
    // ��ȡ��Ͽ�ؼ����б����ѡ���������
    nSel = (*box).GetCurSel();
    // ����ѡ����������ȡ�����ַ���
    (*box).GetLBText(nSel, strWeb);
	printf("%d,%s\n",nSel,(LPCTSTR)strWeb);

	//���ò����ʲ���
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

//�򿪴���/�رհ�ť
void CMYCOMDlg::OnBnClickedComopen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(inputCommstatus == 1 || outputCommstatus == 1)	//�����Ѿ���
	{
		//�رմ���
		if(inputCommstatus == 1)
		{
			InputComm.put_PortOpen(0);	//�˺���û�з���ֵ
			printf("�Էɿ�COM%d�ѹر�\n",inputPortNum);
			inputCommstatus = 0;
		}

		if(outputCommstatus == 1)
		{
			OutputComm.put_PortOpen(0);
			printf("�Ե���վCOM%d�ѹر�\n",outputPortNum);
			outputCommstatus = 0;
		}

		if(inputCommstatus == 0 && outputCommstatus == 0)
			GetDlgItem(ID_COMOPEN)->SetWindowText("�򿪴���");

		return;
	}

	//���ô��ں�
	InputComm.put_CommPort(inputPortNum);	//���öԷɿش��ں�
	OutputComm.put_CommPort(outputPortNum);	//���öԵ���վ���ں�

	//���ô���ģʽ
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

	//�򿪴���
	InputComm.put_PortOpen(1);	//�˺���û�з���ֵ
	printf("�Էɿ�COM%d�Ѵ�,������%d\n",inputPortNum,myBuadRate);
	inputCommstatus = 1;
	GetDlgItem(ID_COMOPEN)->SetWindowText("�رմ���");

	OutputComm.put_PortOpen(1);	//�˺���û�з���ֵ
	printf("�Ե���վCOM%d�Ѵ�,������%d\n",outputPortNum,myBuadRate);
	outputCommstatus = 1;
	GetDlgItem(ID_COMOPEN)->SetWindowText("�رմ���");
}

void CMYCOMDlg::InputReceiveHandle(BYTE data)
{
	printf("�ɿأ�%x\n",data);

}

void CMYCOMDlg::OutputReceiveHandle(BYTE data)
{
	printf("����վ��%x\n",data);
}

BEGIN_EVENTSINK_MAP(CMYCOMDlg, CDialogEx)
	ON_EVENT(CMYCOMDlg, IDC_MSCOMM_OUT, 1, CMYCOMDlg::OnCommMscommOut, VTS_NONE)
	ON_EVENT(CMYCOMDlg, IDC_MSCOMM, 1, CMYCOMDlg::OnCommMscomm, VTS_NONE)
END_EVENTSINK_MAP()


void CMYCOMDlg::OnCommMscomm()
{
	// TODO: �ڴ˴������Ϣ����������

	VARIANT input;
	COleSafeArray safeinput;
	long len;
	BYTE rxdata[2048];

	//��ȡOnComm�¼����
	short num;
	num = InputComm.get_CommEvent();

	CByteArray SendArray;	//���������õĽṹ�����
	SendArray.RemoveAll();

	switch(num)
	{
	case 2:
		input = InputComm.get_Input();
		safeinput = input;
		len = safeinput.GetOneDimSize();	//��ȡ����
		for(long k=0;k<len;k++)				//���������ݴ�������rxdata
			safeinput.GetElement(&k,rxdata+k);
		
		//ת��
		SendArray.SetSize(len);
		for(int k=0;k<len;k++)
		{
			SendArray.SetAt(k,*(rxdata+k));
		}
		OutputComm.put_Output(COleVariant(SendArray));	//ת����output��

		//���ݴ���
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
	// TODO: �ڴ˴������Ϣ����������
	VARIANT input;
	COleSafeArray safeinput;
	long len;
	BYTE rxdata[2048];

	//��ȡOnComm�¼����
	short num;
	num = OutputComm.get_CommEvent();

	CByteArray SendArray;	//���������õĽṹ�����
	SendArray.RemoveAll();

	switch(num)
	{
	case 2:
		input = OutputComm.get_Input();
		safeinput = input;
		len = safeinput.GetOneDimSize();	//��ȡ����
		for(long k=0;k<len;k++)				//���������ݴ�������rxdata
			safeinput.GetElement(&k,rxdata+k);

		//����ת��
		SendArray.SetSize(len);
		for(int k=0;k<len;k++)
		{
			SendArray.SetAt(k,*(rxdata+k));
		}
		InputComm.put_Output(COleVariant(SendArray));	//ת����input��

		//���ݴ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BYTE Head1 = 0xAA;				//֡ͷ1
	BYTE Head2 = 0xAF;				//֡ͷ2
	BYTE Functionword = 0x01;		//������
	BYTE Len = 0x01;				//����
	BYTE Command_Number = 0x02;	//�ڲ�ָ���
	BYTE SUM = Head1+Head2+Functionword+Len+Command_Number;

	CByteArray SendArray;
	SendArray.RemoveAll();
	SendArray.SetSize(6);		//�ܳ���7�ֽڣ�֡ͷ��2�� + �����֣�1�� + ���ȣ�1��+ ָ�2��+ �ܺ�У�飨1��
	SendArray.SetAt(0,Head1);	//֡ͷ
	SendArray.SetAt(1,Head2);	//֡ͷ
	SendArray.SetAt(2,Functionword);	//������
	SendArray.SetAt(3,Len);	//���ȣ�ָ���2�ֽڣ�
	SendArray.SetAt(4,Command_Number);	//ָ���ڲ����
	SendArray.SetAt(5,SUM);

	OutputComm.put_Output(COleVariant(SendArray));	//���͵�Input�ڣ��ɿؿڣ�
}

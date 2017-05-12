
// MYCOMDlg.h : 头文件
//

#include "math.h"
#include "CMSComm.h"
#include "Resource.h"

#pragma once

// CMYCOMDlg 对话框
class CMYCOMDlg : public CDialogEx
{
// 构造
public:
	CMYCOMDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYCOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	void InitComboBox(void);
	
	//输入输出端口使用相同波特率
	int myBuadRate;

	//数据输入串口（对飞控）
	CMSComm InputComm;
	int InputCommInit(void);
	void InputReceiveHandle(BYTE data);
	int inputCommstatus;
	int inputPortNum;
	
	//对地面站输出串口
	CMSComm OutputComm;
	int OutputCommInit(void);
	void OutputReceiveHandle(BYTE data);
	int outputCommstatus;
	int outputPortNum;

	afx_msg void OnBnClickedComopen();
	afx_msg void OnCbnSelchangeBaudrate();
	afx_msg void OnCbnSelchangePortnum();
	afx_msg void OnCbnSelchangePortnumOut();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscommOut();
	void OnCommMscomm();
	afx_msg void OnBnClickedMessage1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedMessaage2();
};

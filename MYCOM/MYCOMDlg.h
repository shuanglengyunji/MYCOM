
// MYCOMDlg.h : ͷ�ļ�
//

#include "math.h"
#include "CMSComm.h"

#pragma once

// CMYCOMDlg �Ի���
class CMYCOMDlg : public CDialogEx
{
// ����
public:
	CMYCOMDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYCOM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	void InitComboBox(void);
	
	//��������˿�ʹ����ͬ������
	int myBuadRate;

	//�������봮�ڣ��Էɿأ�
	CMSComm InputComm;
	int InputCommInit(void);
	int inputCommstatus;
	int inputPortNum;
	
	//�Ե���վ�������
	CMSComm OutputComm;
	int OutputCommInit(void);
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
};

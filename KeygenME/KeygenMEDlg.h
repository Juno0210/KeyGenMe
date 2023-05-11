
// KeygenMEDlg.h : header file
//

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define WIN32_LEAN_AND_MEAN

#define _sizeof(array) (sizeof(array)/sizeof(array[0]))

#pragma once

// CKeygenMEDlg dialog
class CKeygenMEDlg : public CDialogEx
{
// Construction
public:
	CKeygenMEDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KEYGENME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
//	afx_msg void OnIddKeygenmeDialog();
	afx_msg void OnBnClickedBtnExit();
//	afx_msg void OnEnSetfocusEditName();
//	afx_msg void OnChangeEditName();
	afx_msg void OnBnClickedBtnCheck();
	CEdit m_ctrlSerial;
	CEdit m_ctrlName;
	CString m_strName;
	CString m_strSerial;
};

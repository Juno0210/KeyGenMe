
// KeygenMEDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "KeygenME.h"
#include "KeygenMEDlg.h"
#include "afxdialogex.h"
#include <winsock.h>
#include <iphlpapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//HWND Hwnd;
//HWND TextboxUser;
//HWND TextboxSerial;


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CKeygenMEDlg dialog



CKeygenMEDlg::CKeygenMEDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KEYGENME_DIALOG, pParent)
	, m_strName(_T(""))
	, m_strSerial(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeygenMEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SERIAL, m_ctrlSerial);
	DDX_Control(pDX, IDC_EDIT_NAME, m_ctrlName);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_SERIAL, m_strSerial);
}

BEGIN_MESSAGE_MAP(CKeygenMEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_COMMAND(IDD_KEYGENME_DIALOG, &CKeygenMEDlg::OnIddKeygenmeDialog)
	ON_BN_CLICKED(IDB_BTN_EXIT, &CKeygenMEDlg::OnBnClickedBtnExit)
//	ON_EN_SETFOCUS(IDC_EDIT_NAME, &CKeygenMEDlg::OnEnSetfocusEditName)
//ON_EN_CHANGE(IDC_EDIT_NAME, &CKeygenMEDlg::OnChangeEditName)
ON_BN_CLICKED(IDB_BTN_CHECK, &CKeygenMEDlg::OnBnClickedBtnCheck)
END_MESSAGE_MAP()


// CKeygenMEDlg message handlers

BOOL CKeygenMEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeygenMEDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeygenMEDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeygenMEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKeygenMEDlg::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here

	ExitProcess(0);
}

// Function to get the MAC address
int GetMacAddress(CString& szMacAddress)
{
	int nResult = 0;
	ULONG ulSize = 0;
	PIP_ADAPTER_INFO pAdapterInfo = NULL;

	// Get the size of the adapter info structure
	if (GetAdaptersInfo(NULL, &ulSize) != ERROR_BUFFER_OVERFLOW)
		return nResult;

	// Allocate memory for the adapter info structure
	pAdapterInfo = (PIP_ADAPTER_INFO) new BYTE[ulSize];

	// Get the adapter info
	if (GetAdaptersInfo(pAdapterInfo, &ulSize) == ERROR_SUCCESS)
	{
		// Get the MAC address
		szMacAddress.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),
			pAdapterInfo->Address[0],
			pAdapterInfo->Address[1],
			pAdapterInfo->Address[2],
			pAdapterInfo->Address[3],
			pAdapterInfo->Address[4],
			pAdapterInfo->Address[5]);
		nResult = 1;
	}

	// Free the memory
	delete[] pAdapterInfo;

	return nResult;
}

// Function to generate the serial key
UINT  GenerateSerialKey(CString inputValue)
{
	// Generate UUID
	GUID uuid;
	CoCreateGuid(&uuid);
	char szUUID[64];
	sprintf_s(szUUID, sizeof(szUUID), "%08lX-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
		uuid.Data1, uuid.Data2, uuid.Data3,
		uuid.Data4[0], uuid.Data4[1], uuid.Data4[2], uuid.Data4[3],
		uuid.Data4[4], uuid.Data4[5], uuid.Data4[6], uuid.Data4[7]);

	CString szMacAddress;

	// Get the MAC address
	GetMacAddress(szMacAddress);

	// Combine input value with MAC address and UUID
	CString strCombined = inputValue + szMacAddress + szUUID;


	UINT hashed = 0;
	int iStringLength = inputValue.GetLength();

	for (int i = 0; i < iStringLength; i++)
	{
		hashed += (UINT)(strCombined[i] * (i + 1) * 13 * 37 * 71);
	}

	return hashed;

}

void CKeygenMEDlg::OnBnClickedBtnCheck()
{
	// TODO: Add your control notification handler code here

	CString s_Name = _T("");
	CString s_Serial = _T("");
	
	m_ctrlName.GetWindowTextW(s_Name);
	m_ctrlSerial.GetWindowTextW(s_Serial);

	int len_name = m_ctrlName.GetWindowTextLengthW();
	int len_serial = m_ctrlSerial.GetWindowTextLengthW();
	
	if (s_Name.IsEmpty()) {
		MessageBoxW(L"Input UserName...");
		m_ctrlName.SetWindowTextW(_T(""));
		m_ctrlSerial.SetWindowTextW(_T(""));
	}
	else if (len_name < 4)
	{
		MessageBoxW(L"Username must be at least 4 characters long...");
		m_ctrlName.SetWindowTextW(_T(""));
		m_ctrlSerial.SetWindowTextW(_T(""));
	}
	else
	{
		m_strName = s_Name;
		if (s_Serial.IsEmpty())
			MessageBoxW(L"Input serial...");
		else
		{
			m_strSerial = s_Serial;
			UINT uiKey = GenerateSerialKey(m_strName);

			CString strResult;
			strResult.Format(_T("%08X"), uiKey);

			int result = m_strSerial.Compare(strResult);

			if (result == 0)
				AfxMessageBox(_T("Success!"));
			else
				AfxMessageBox(_T("Invalid serial key!"));

		}

	}
	
	
	UpdateData(FALSE);
}

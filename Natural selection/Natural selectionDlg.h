
// Natural selectionDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CNaturalselectionDlg
class CNaturalselectionDlg : public CDialogEx
{
// Создание
public:
	CNaturalselectionDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NATURALSELECTION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void Show_First_Screen();
	void Show_Second_Screen();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT ID);
	CEdit _Edit_Peacfull;
	CEdit _Edit_Angree;
	afx_msg void OnBnClickedButtonGetAmounts();
	CButton _Button_Start;
	afx_msg void OnBnClickedButtonStart();
	CButton _Button_Stop;
	afx_msg void OnBnClickedButtonStop();
	CEdit _Edit_Food;
	CSliderCtrl _Slider_Timer;
	CButton _Text_Amount_Peaceful;
	CButton _Button_New_Simulation;
	CButton _Button_Continue_Simulation;
	CButton _Button_License_Agreement;
	CButton _Button_Exit;
	afx_msg void OnBnClickedButtonnewSimulation();
	afx_msg void OnBnClickedButtoncontinuesimulation();
	afx_msg void OnBnClickedButtonlicenseagrement();
	afx_msg void OnBnClickedButtonexit();
	CButton _Button_Go_To_Menu;
	afx_msg void OnBnClickedButtonGoToMenu();
	CButton _Button_Delete_All_Saves;
	afx_msg void OnBnClickedButtondeletesaves();
	CEdit _Edit_Nomer_of_save;
	CButton _Button_Nomer_ofSave;
	afx_msg void OnBnClickedButtonnomerok();
	CEdit _Edit_Caption_Time;
	CEdit _Edit_Counter_of_mins;
};


// Natural selectionDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Natural selection.h"
#include "Natural selectionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

//RECT rt; GetWindowRect(&rt);
//
//int x = rt.right - rt.left;
//int y = rt.bottom - rt.top;
//
//x -= 30;
//y -= 80;
//
//Creation::window.X = x;
//Creation::window.Y = y;

RECT rt;



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CNaturalselectionDlg



CNaturalselectionDlg::CNaturalselectionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NATURALSELECTION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNaturalselectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_Peacfull, _Edit_Peacfull);
	DDX_Control(pDX, IDC_EDIT_Angree, _Edit_Angree);
	DDX_Control(pDX, IDC_BUTTON_Start, _Button_Start);
	DDX_Control(pDX, IDC_BUTTON_Stop, _Button_Stop);
	DDX_Control(pDX, IDC_EDIT_Food, _Edit_Food);
	DDX_Control(pDX, IDC_SLIDER_Slider_for_Timer, _Slider_Timer);
	DDX_Control(pDX, IDC_BUTTON_Get_Amounts, _Text_Amount_Peaceful);
	DDX_Control(pDX, IDC_BUTTON_new_Simulation, _Button_New_Simulation);
	DDX_Control(pDX, IDC_BUTTON_cONTINUE_sIMULATION, _Button_Continue_Simulation);
	DDX_Control(pDX, IDC_BUTTON_license_agrement, _Button_License_Agreement);
	DDX_Control(pDX, IDC_BUTTON_exit, _Button_Exit);
	DDX_Control(pDX, IDC_BUTTON_Go_To_Menu, _Button_Go_To_Menu);
	DDX_Control(pDX, IDC_BUTTON_delete_saves, _Button_Delete_All_Saves);
	DDX_Control(pDX, IDC_EDIT_nomerofsave, _Edit_Nomer_of_save);
	DDX_Control(pDX, IDC_BUTTON_nomer_ok, _Button_Nomer_ofSave);
	DDX_Control(pDX, IDC_EDIT_Caption_Time, _Edit_Caption_Time);
	DDX_Control(pDX, IDC_EDIT_counter_of_mins, _Edit_Counter_of_mins);
}

BEGIN_MESSAGE_MAP(CNaturalselectionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Get_Amounts, &CNaturalselectionDlg::OnBnClickedButtonGetAmounts)
	ON_BN_CLICKED(IDC_BUTTON_Start, &CNaturalselectionDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_Stop, &CNaturalselectionDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_new_Simulation, &CNaturalselectionDlg::OnBnClickedButtonnewSimulation)
	ON_BN_CLICKED(IDC_BUTTON_cONTINUE_sIMULATION, &CNaturalselectionDlg::OnBnClickedButtoncontinuesimulation)
	ON_BN_CLICKED(IDC_BUTTON_license_agrement, &CNaturalselectionDlg::OnBnClickedButtonlicenseagrement)
	ON_BN_CLICKED(IDC_BUTTON_exit, &CNaturalselectionDlg::OnBnClickedButtonexit)
	ON_BN_CLICKED(IDC_BUTTON_Go_To_Menu, &CNaturalselectionDlg::OnBnClickedButtonGoToMenu)
	ON_BN_CLICKED(IDC_BUTTON_delete_saves, &CNaturalselectionDlg::OnBnClickedButtondeletesaves)
	ON_BN_CLICKED(IDC_BUTTON_nomer_ok, &CNaturalselectionDlg::OnBnClickedButtonnomerok)
END_MESSAGE_MAP()




// Обработчики сообщений CNaturalselectionDlg

BOOL CNaturalselectionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	_Edit_Caption_Time.SetWindowTextW(L"Time in mins:");
	_Edit_Counter_of_mins.SetWindowTextW(L"0");

	Show_First_Screen();

	_Slider_Timer.SetRange(1, 300);
	_Slider_Timer.SetPos(38);


	rt.left = 0;
	rt.bottom = 625;
	rt.top = 0;
	rt.right = 1240;

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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CNaturalselectionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CNaturalselectionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CPaintDC dc(this);

		life.Draw(dc);

		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CNaturalselectionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNaturalselectionDlg::Show_First_Screen()
{
	_Edit_Peacfull.ShowWindow(0);
	_Edit_Angree.ShowWindow(0);
	_Edit_Food.ShowWindow(0);

	_Slider_Timer.ShowWindow(0);

	_Text_Amount_Peaceful.ShowWindow(0);

	_Button_Go_To_Menu.ShowWindow(0);

	_Button_Start.ShowWindow(0);
	_Button_Stop.ShowWindow(0);

	_Edit_Caption_Time.ShowWindow(0);
	_Edit_Counter_of_mins.ShowWindow(0);

	_Edit_Nomer_of_save.ShowWindow(0);//Два елементи, які визначають номер збереження, їх завжти провсяк випадок потрібно приховувати
	_Button_Nomer_ofSave.ShowWindow(0);

	_Button_New_Simulation.ShowWindow(1);
	_Button_Continue_Simulation.ShowWindow(1);
	_Button_Delete_All_Saves.ShowWindow(1);
	_Button_License_Agreement.ShowWindow(1);
	_Button_Exit.ShowWindow(1);
}

void CNaturalselectionDlg::Show_Second_Screen()
{
	_Edit_Peacfull.ShowWindow(1);
	_Edit_Angree.ShowWindow(1);
	_Edit_Food.ShowWindow(1);

	_Slider_Timer.ShowWindow(1);

	_Text_Amount_Peaceful.ShowWindow(1);

	_Button_Go_To_Menu.ShowWindow(1);

	_Button_Start.ShowWindow(1);
	_Button_Stop.ShowWindow(1);

	_Edit_Caption_Time.ShowWindow(1);
	_Edit_Counter_of_mins.ShowWindow(1);

	_Edit_Nomer_of_save.ShowWindow(0);//Два елементи, які визначають номер збереження, їх завжти провсяк випадок потрібно приховувати
	_Button_Nomer_ofSave.ShowWindow(0);

	_Button_New_Simulation.ShowWindow(0);
	_Button_Continue_Simulation.ShowWindow(0);
	_Button_Delete_All_Saves.ShowWindow(0);
	_Button_License_Agreement.ShowWindow(0);
	_Button_Exit.ShowWindow(0);

}

void CNaturalselectionDlg::OnTimer(UINT ID)
{
	CString str;

	switch (ID)
	{
	case 1:
		life.Do();
		
		//InvalidateRect(&rt, 1);
		RedrawWindow(&rt, NULL, RDW_INVALIDATE | RDW_ERASE);
		break;
	case 2:
		str.Format(L"%d", Peacefull::counter_Of_Peacefull);
		_Edit_Peacfull.SetWindowTextW(str);
		str.Format(L"%d", Angree::counter_Of_Angree);
		_Edit_Angree.SetWindowTextW(str);
		break;
	case 3:
		str.Format(L"%d", ++Life::timer_Amount_of_mins);
		_Edit_Counter_of_mins.SetWindowTextW(str);
		break;
	

	}
}


void CNaturalselectionDlg::OnBnClickedButtonGetAmounts()
{
	// TODO: добавьте свой код обработчика уведомлений

	CString amount_Of_Peacefull;
	CString amount_Of_Angree;
	CString amount_Of_Food;

	_Edit_Peacfull.GetWindowTextW(amount_Of_Peacefull);
	_Edit_Angree.GetWindowTextW(amount_Of_Angree);
	_Edit_Food.GetWindowTextW(amount_Of_Food);

	/*int n = _ttoi(s);*/
	Peacefull::counter_Of_Peacefull = (_ttoi(amount_Of_Peacefull));
	Angree::counter_Of_Angree = (_ttoi(amount_Of_Angree));
	Food::amount_of_Food = _ttoi(amount_Of_Food);

	life.Init();

	_Button_Start.EnableWindow(1);
	
	
}


void CNaturalselectionDlg::OnBnClickedButtonStart()
{
	// TODO: добавьте свой код обработчика уведомлений
	_Button_Start.EnableWindow(0);
	_Button_Stop.EnableWindow(1);
	

	SetTimer(1, _Slider_Timer.GetPos(), 0);
	SetTimer(2, 300, 0);
	SetTimer(3, 60000, 0);
	
	_Button_Go_To_Menu.EnableWindow(1);


}


void CNaturalselectionDlg::OnBnClickedButtonStop()
{
	// TODO: добавьте свой код обработчика уведомлений
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);

	_Button_Stop.EnableWindow(0);
	_Button_Start.EnableWindow(1);
	
}


void CNaturalselectionDlg::OnBnClickedButtonnewSimulation()
{
	Life::timer_Amount_of_mins = 0;

	int ressave;
	if (life.Get_Amount_of_Saves() >= 9)
	{
		CString str5;
		str5 = L"У вас уже 9 збережених симуляцій,\n наступна симуляція не буде збережена.\nВидилати усі симуляції?";
		ressave = AfxMessageBox(str5, MB_YESNO);
		if (ressave == IDYES)
			life.Delete_All_Saves();

	}
		_Text_Amount_Peaceful.EnableWindow(1);
		// TODO: добавьте свой код обработчика уведомлений
		Show_Second_Screen();

		CString str;
		str.Format(L"%d", Life::timer_Amount_of_mins);
		_Edit_Counter_of_mins.SetWindowTextW(str);

}

void CNaturalselectionDlg::OnBnClickedButtoncontinuesimulation()
{
	// TODO: добавьте свой код обработчика уведомлений

	Creation::amount_Of_Creation = 0;
	Food::amount_of_Food = 0;
	
	CString str, amountof_saves;
	if (life.Get_Amount_of_Saves() > 0)
	{
		amountof_saves.Format(L"%d", life.Get_Amount_of_Saves());

		str = L"You have " + amountof_saves + L" save(s)\n Enter which one you want to continue";
		int res = AfxMessageBox(str, MB_OKCANCEL);
		if (res == IDOK)
		{
			_Edit_Nomer_of_save.ShowWindow(1);
			_Button_Nomer_ofSave.ShowWindow(1);
		}
	}
	else
	{	
		str = L"You have no saves!";
		AfxMessageBox(str, MB_OK);
	}
}

void CNaturalselectionDlg::OnBnClickedButtonlicenseagrement()
{
	// TODO: добавьте свой код обработчика уведомлений
	int res = _spawnlp(_P_WAIT, "C:\\Windows\\notepad.exe", "notepad.exe", "License Agreement.txt", NULL);
}

void CNaturalselectionDlg::OnBnClickedButtonexit()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	str = L"          E X I T?";
	int res = AfxMessageBox(str, MB_YESNO);
	if(res == IDYES)
		CDialogEx::OnCancel();
}

void CNaturalselectionDlg::OnBnClickedButtonGoToMenu()
{
	// TODO: добавьте свой код обработчика уведомлений

	KillTimer(1);
	KillTimer(2);
	KillTimer(3);

	if (life.Get_Amount_of_Saves() < 9)
	{
		CString str;
		str = L"Save the following simulation?";

		int res = AfxMessageBox(str, MB_YESNOCANCEL);
		if (res == IDNO)
		{
			str = L"Have you even read License Agreement?\n So do it right now!";
			AfxMessageBox(str, MB_OK);
			int res = _spawnlp(_P_WAIT, "C:\\Windows\\notepad.exe", "notepad.exe", "License Agreement.txt", NULL);
			str = L"Save the following simulation?";
			res = AfxMessageBox(str, MB_YESNO);
			if (res == IDYES)
				life.Save();
			Show_First_Screen();
			Peacefull::counter_Of_Peacefull = 0;
			Angree::counter_Of_Angree = 0;
			Creation::amount_Of_Creation = 0;
			Food::amount_of_Food = 0;
			Invalidate();

		}
		else if (res == IDYES)
		{
			life.Save();
			Show_First_Screen();
			Peacefull::counter_Of_Peacefull = 0;
			Angree::counter_Of_Angree = 0;
			Creation::amount_Of_Creation = 0;
			Food::amount_of_Food = 0;
			Invalidate();
		}		
	}
}

void CNaturalselectionDlg::OnBnClickedButtondeletesaves()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	str = L"Delete all saves?";
	int res = AfxMessageBox(str, MB_YESNO);
	if (res == IDYES)
		life.Delete_All_Saves();
}

void CNaturalselectionDlg::OnBnClickedButtonnomerok()
{
	// TODO: добавьте свой код обработчика уведомлений

	CString nomer_of_save;
	_Edit_Nomer_of_save.GetWindowTextW(nomer_of_save);

	int length_of_str_with_nomer_of_save = _Edit_Nomer_of_save.GetWindowTextLengthW();

	int nomer;
	nomer = _ttoi(nomer_of_save);

	CString str;

	if (length_of_str_with_nomer_of_save == 0 || nomer < 1 || nomer > 9)
	{
		str = L"Тут мала б вилетіти точка останови, але Стасюк Євгеній попередив це!";
		AfxMessageBox(str, MB_OK);
	}
	else
	{
		if (nomer > life.Get_Amount_of_Saves())
		{
			MessageBox(L"You don`t have so many saves!");
		}
		else
		{
			_Button_Go_To_Menu.EnableWindow(1);

			Show_Second_Screen();

			_Edit_Nomer_of_save.ShowWindow(0);
			_Button_Nomer_ofSave.ShowWindow(0);

			_Text_Amount_Peaceful.EnableWindow(0);

			_Button_Start.EnableWindow(1);

			life.Init_Save(nomer);

			
			str.Format(L"%d", Life::timer_Amount_of_mins);
			_Edit_Counter_of_mins.SetWindowTextW(str);
		}
	}
}
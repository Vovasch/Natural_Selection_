
// Natural selection.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "Natural selection.h"
#include "Natural selectionDlg.h"
#include <ctime>
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Max_X 1240
#define Max_Y 625


#define Radius 200
#define Energy 2400
#define Strength 1
#define Life_Duration_Peacefull 1300
#define Life_Duration_Angree 900

#define Energy_For_Bundling_Peacefull 3500
#define Energy_For_Bundling_Angree 4000

#define Grass_Energy 400

#define Max_Recovered_Food_Per_Moment 1

// CNaturalselectionApp

BEGIN_MESSAGE_MAP(CNaturalselectionApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Создание CNaturalselectionApp

CNaturalselectionApp::CNaturalselectionApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CNaturalselectionApp

CNaturalselectionApp theApp;


// Инициализация CNaturalselectionApp

BOOL CNaturalselectionApp::InitInstance()
{
	// InitCommonControlsEx() требуется для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;

	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));

	CNaturalselectionDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "ОК"
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "Отмена"
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Предупреждение. Не удалось создать диалоговое окно, поэтому работа приложения неожиданно завершена.\n");
		TRACE(traceAppMsg, 0, "Предупреждение. При использовании элементов управления MFC для диалогового окна невозможно #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}

Creation::Creation(COORD position, COORD where_To_Go, int age, int speed, int radius_Feeling_Of_Object, int energy, int minimal_Guaranted_Life_Duruation, int strength)
{
	this->position = position;
	this->target_Food = where_To_Go;
	this->age = age;
	this->speed = speed;
	this->radius_Feeling_Of_Object = radius_Feeling_Of_Object;
	this->energy = energy;
	this->minimal_Guaranted_Life_Duruation = minimal_Guaranted_Life_Duruation;
	this->strength = strength;

	this->what_to_do_where_to_go = 0;
	this->nomer_of_target_food = 0;
}

void Creation::Go_to()
{
	if (target_Food.X < position.X - 5)
		position.X -= speed;
	else if (target_Food.X > position.X + 5)
		position.X += speed;
	else if (target_Food.Y < position.Y - 5)
		position.Y -= speed;
	else if (target_Food.Y > position.Y + 5)
		position.Y += speed;
}

void Creation::Move(Food** food, Creation** creation, int range_of_Food_start, int rane_of_Food_end)
{

	if (this->what_to_do_where_to_go == 2)
	{
		// where to go = 2

		int x_c = this->position.X;
		int y_c = this->position.Y;
		if (food[this->nomer_of_target_food] != nullptr)
		{
			COORD temp = this->target_Food;

			int x_f = this->target_Food.X;
			int y_f = this->target_Food.Y;

			if (x_f >= x_c - 5 && x_f <= x_c + 5 && y_f >= y_c - 5 && y_f <= y_c + 5)
			{
				//ate

				this->what_to_do_where_to_go = 0;

				this->energy += food[this->nomer_of_target_food]->Get_Energy();

				delete food[this->nomer_of_target_food];

				food[this->nomer_of_target_food] = nullptr;
			}
		}
		else
			this->what_to_do_where_to_go = 0;

	}

	if (this->what_to_do_where_to_go < 2)
	{
		int x_c = this->position.X;
		int y_c = this->position.Y;

		int r = this->radius_Feeling_Of_Object;

		double theNearestLength = 9999999999999;

		for (int e = range_of_Food_start; e < rane_of_Food_end; e++)
		{
			if (food[e] != nullptr)
			{
				COORD temp = food[e]->Get_Pos();

				int x_f = temp.X;
				int y_f = temp.Y;

				double tempLength;

				if (x_f >= x_c - r && x_f <= x_c + r && y_f >= y_c - r && y_f <= y_c + r)
				{
					tempLength = sqrt(pow((x_c - x_f), 2) + pow((y_c - y_f), 2));
					if (tempLength < theNearestLength)
					{
						this->what_to_do_where_to_go = 2;
						theNearestLength = tempLength;
						this->nomer_of_target_food = e;
						this->target_Food = temp;
					}
				}
			}
		}

		if (this->what_to_do_where_to_go == 0)
		{
			COORD pos;

			pos.X = rand() % 1195;
			pos.Y = rand() % 570;

			pos.X += 5;
			pos.Y += 5;

			this->target_Food = pos;
			this->what_to_do_where_to_go = 1;

		}
		else if (this->what_to_do_where_to_go == 1)
		{

			int x_c = this->position.X;
			int y_c = this->position.Y;

			int x_f = this->target_Food.X;
			int y_f = this->target_Food.Y;

			if (x_f >= x_c - 6 && x_f <= x_c + 6 && y_f >= y_c - 6 && y_f <= y_c + 6)
				this->what_to_do_where_to_go = 0;
		}
	}
	

	Go_to();

}

void Creation::Draw(CPaintDC &dc)
{
	dc.Rectangle(this->position.X - 5, position.Y - 5, position.X + 5, position.Y + 5);
}

bool Creation::Become_Older_and_Chek_Dead()
{
	
	this->age++;

	if (this->age >= this->minimal_Guaranted_Life_Duruation || this->energy <= 0)
		return 1;
	return 0;

	
}

void Creation::Not_Being_On_Each_Other(int nomerofcreation, int range_start, int range_end, Creation** creation)
{
	int x1 = creation[nomerofcreation]->Get_Pos().X;
	int y1 = creation[nomerofcreation]->Get_Pos().Y;

	for (int i = range_start; i < range_end; i++)
	{
		if (i == nomerofcreation)
			continue;

		COORD temp2 = creation[i]->position;
		int x2 = creation[i]->position.X;
		int y2 = creation[i]->position.Y;

		//Вони ніби відпихують один одного
		if ((x2 >= x1 - 5) && (x2 <= x1 + 5) && (y2 >= y1 - 5) && (y2 <= y1 + 5))
		{
			int randd = rand() % 3;

			switch (randd)
			{
			case 0:
				creation[i]->position.X += 5;
				break;
			case 1:
				creation[i]->position.X -= 5;
				break;
			case 2:
				creation[i]->position.Y += 5;
				break;
			case 3:
				creation[i]->position.Y -= 5;
				break;

			}
		}
	}
}

void Peacefull::Draw(CPaintDC& dc)
{
	CPen pen(PS_SOLID, 2, RGB(this->R, this->G, this->B));
	dc.SelectObject(&pen);
	Creation::Draw(dc);
}

void Peacefull::Bundling(Creation** creation)
{

	if (this->energy > Energy_For_Bundling_Peacefull)
	{
		for (int e = Creation::amount_Of_Creation; e > Peacefull::counter_Of_Peacefull; e--)
			creation[e] = creation[e - 1];

		this->energy /= 2;

		int plevok;

		if (position.X + 600 >= 1300)
			plevok = -10;
		else if (position.X - 600 <= 0)
			plevok = 10;
		else
			plevok = -10;


		//вибираємо яку характеристику прокачати
		// такий великий range, щоб не кожного разу прокачувати
		int nomer = rand() % 7;

		COORD newPos = this->position;
		COORD newWhere_To_G0;
		int x = rand() % 1200;
		int y = rand() % 550;

		x += 5;
		y += 5;

		newWhere_To_G0.X = x;
		newWhere_To_G0.Y = y;

		newPos.X += plevok;

		int newDuration = this->minimal_Guaranted_Life_Duruation;

		int newSpeed = this->speed;

		int newRadius = this->radius_Feeling_Of_Object;

		switch (nomer)
		{
		case 0:
			if (speed >= 4)
				break;
			newSpeed++;
			break;
		case 3:
			newDuration += 4;
			break;
		case 6:
			newRadius++;
			break;
		default:
			break;
		}

		creation[Peacefull::counter_Of_Peacefull] = new Peacefull(newPos, newWhere_To_G0, 0, newSpeed, newRadius, this->energy, newDuration, 0);

		Creation::amount_Of_Creation++;
		Peacefull::counter_Of_Peacefull++;
	}
}
void Peacefull::Move_Blat_I_Dont_Know_How_To_Do_It_correct(Food** food, Creation** creation)
{
	Move(food, creation, 0, Grass::counter_Of_Grass);

}

void Angree::Recive_Energy_from_Peacefull(Creation* creation)
{
	int damage;

	switch (this->strength)
	{
	case 1:
		damage = 400;
		break;
	case 2:
		damage = 450;
		break;
	case 3:
		damage = 500;
		break;
	default:
		damage = 500;
		break;
	}
	
	
	this->energy += damage;
	creation->Lose_Energy(damage);
}

void Angree::Draw(CPaintDC& dc)
{
	CPen pen(PS_SOLID, 2, RGB(this->R, this->G, this->B));
	dc.SelectObject(&pen);
	Creation::Draw(dc);
}

void Angree::Bundling(Creation** creation)
{

	if (this->energy >= Energy_For_Bundling_Angree)
	{
		this->energy /= 2;

		int plevok;

		if (position.X + 600 >= 1300)
			plevok = -10;
		else if (position.X - 600 <= 0)
			plevok = 10;
		else
			plevok = -10;

		//вибираємо яку характеристику прокачати
		// такий великий range, щоб не кожного разу прокачувати
		int nomer = rand() % 10;

		COORD newPos = this->position;

		COORD newWhere_To_G0;
		int x = rand() % 1200;
		int y = rand() % 550;

		x += 5;
		y += 5;

		newWhere_To_G0.X = x;
		newWhere_To_G0.Y = y;

		newPos.X += plevok;

		int newDuration = this->minimal_Guaranted_Life_Duruation;

		int newSpeed = this->speed;

		int newRadius = this->radius_Feeling_Of_Object;

		int newStrength = this->strength;

		switch (nomer)
		{
		case 0:
			if (speed >= 4)
				break;
			newSpeed++;
			break;
		case 3:
			newDuration += 5;
			break;
		case 6:
			newRadius++;
			break;
		case 9:
			if (strength >= 3)
				break;
			newStrength++;
			break;
		default:
			break;
		}

		creation[Creation::amount_Of_Creation] = new Angree(newPos, newWhere_To_G0, 0, newSpeed, newRadius, this->energy, newDuration, newStrength, -1);

		Creation::amount_Of_Creation++;
		Angree::counter_Of_Angree++;
	}
}

void Angree::Move_Blat_I_Dont_Know_How_To_Do_It_correct(Food** food, Creation** creation)
{
	Move(food, creation, Grass::counter_Of_Grass, Food::amount_of_Food);

	if (this->what_to_do_where_to_go < 2)
	{
		int x_c = this->position.X;
		int y_c = this->position.Y;

		int r = this->radius_Feeling_Of_Object;

		double theNearestLength = 9999999999999;

		for (int e = 0; e < Peacefull::counter_Of_Peacefull; e++)
		{
			if (this->just_Hitten_Creation == e) // Не трогаємо того, кого тільки що вкусили
				continue;
			int x_f = creation[e]->Get_Pos().X;
			int y_f = creation[e]->Get_Pos().Y;

			double tempLength;

			if (x_f >= x_c - r && x_f <= x_c + r && y_f >= y_c - r && y_f <= y_c + r)
			{
				tempLength = sqrt(pow((x_c - x_f), 2) + pow((y_c - y_f), 2));
				if (tempLength < theNearestLength)
				{
					this->what_to_do_where_to_go = 3;
					theNearestLength = tempLength;
					this->nomer_of_target_food = e;
					this->target_Food = creation[e]->Get_Pos();
				}
			}
		}
	}

	if (this->what_to_do_where_to_go == 3)
	{
		if (Peacefull::counter_Of_Peacefull == 0 || this->nomer_of_target_food >= Peacefull::counter_Of_Peacefull)
		{
			this->what_to_do_where_to_go = 0;
		}
		else
		{

			int x_c = this->position.X;
			int y_c = this->position.Y;

			COORD temp = creation[this->nomer_of_target_food]->Get_Pos();

			int x_f = temp.X;
			int y_f = temp.Y;

			if (x_f <= x_c - this->radius_Feeling_Of_Object && x_f >= x_c + this->radius_Feeling_Of_Object && y_f <= y_c - this->radius_Feeling_Of_Object && y_f >= y_c + this->radius_Feeling_Of_Object)
			{
				this->what_to_do_where_to_go = 0;
			}

			if (x_f >= x_c - 5 && x_f <= x_c + 5 && y_f >= y_c - 5 && y_f <= y_c + 5)
			{
				//ate
				this->what_to_do_where_to_go = 0;
				
				Recive_Energy_from_Peacefull(creation[this->nomer_of_target_food]);

				this->just_Hitten_Creation = this->nomer_of_target_food; // Записали номер того якого заграз не трогаємо
			}
			if (creation[this->nomer_of_target_food]->Get_amount_Energy() <= 0)
				this->what_to_do_where_to_go = 0;
			else
				this->target_Food = creation[this->nomer_of_target_food]->Get_Pos();
		}
	}
}

COORD Creation::window;
int Creation::amount_Of_Creation = 0;
int Food::amount_of_Food;

int Peacefull::counter_Of_Peacefull = 0;
int Angree::counter_Of_Angree = 0;

int Meat::counter_Of_Meat = 0;
int Grass::counter_Of_Grass = 0;

int Life::timer_Amount_of_mins = 0;

void Life::If_your_food_was_eaten_look_for_new()
{
	for (int i = 0; i < Creation::amount_Of_Creation; i++)
	{
		if (food[creation[i]->nomer_of_target_food] == nullptr && creation[i]->what_to_do_where_to_go == 2)
			creation[i]->what_to_do_where_to_go = 0;
	}
}
void Life::Draw(CPaintDC& dc)
{
	for (int i = 0; i < Creation::amount_Of_Creation; i++)
		creation[i]->Draw(dc);

	for (int i = 0; i < Food::amount_of_Food; i++)
	{
		if (food[i] == nullptr)
			continue;
		food[i]->Draw(dc);
	}
}

void Life::Init()
{
	this->nomer_Of_Save = 0;

	srand(time(NULL));
	Creation::amount_Of_Creation = Angree::counter_Of_Angree + Peacefull::counter_Of_Peacefull;
	//створюємо вільне місце під м'ясо
	Grass::counter_Of_Grass = Food::amount_of_Food;
	Meat::counter_Of_Meat = Food::amount_of_Food;
	Food::amount_of_Food = Grass::counter_Of_Grass + Meat::counter_Of_Meat;

	if (Angree::counter_Of_Angree == 0)
	{
		Food::amount_of_Food -= Meat::counter_Of_Meat;
		
	}
	food = new Food * [Food::amount_of_Food];

	creation = new Creation * [1000];

	for (int i = 0; i < Peacefull::counter_Of_Peacefull; i++)
	{
		COORD pos;
		COORD target;
		pos.X = rand() % 1195;
		pos.Y = rand() % 570;
		
		target.X = rand() % 1195;
		target.Y = rand() % 570;

		pos.X += 5;
		pos.Y += 5;

		target.X += 5;
		target.Y += 5;
		
		creation[i] = new Peacefull(pos,target,0, 1, Radius, Energy, Life_Duration_Peacefull, 0);
	}

	for (int i = Peacefull::counter_Of_Peacefull; i < Creation::amount_Of_Creation; i++)
	{
		COORD pos;
		COORD target;
		pos.X = rand() % 1195;
		pos.Y = rand() % 570;

		target.X = rand() % 1195;
		target.Y = rand() % 570;

		pos.X += 5;
		pos.Y += 5;

		target.X += 5;
		target.Y += 5;
		
		creation[i] = new Angree(pos, target, 0, 1, Radius, Energy, Life_Duration_Angree, Strength, -1);
	}

	for (int i = 0; i < Grass::counter_Of_Grass; i++)
	{
		COORD pos;
		pos.X = rand() % 1195;
		pos.Y = rand() % 570;

		pos.X += 5;
		pos.Y += 5;

		food[i] = new Grass(pos, Grass_Energy);
	}

	for (int i = Grass::counter_Of_Grass; i < Food::amount_of_Food; i++)
		food[i] = nullptr;
}

void Life::Init_Save(int nomer_of_save)
{
	this->nomer_Of_Save = nomer_of_save;

	int real_amount_of_grass;
	int real_amount_of_meat;

	COORD pos;
	COORD target_food;
	int age, speed, radius, energy, duruation, strength;

	int just_hitten;

	int x, y, x1, y1;

	FILE* save;
	char b[10];
	char str[100];
	
	b[0] = 'S';
	b[1] = 'a';
	b[2] = 'v';
	b[3] = 'e';
	(_itoa_s(nomer_of_save, &b[4], 2, 10));
	b[5] = '.';
	b[6] = 't';
	b[7] = 'x';
	b[8] = 't';
	b[9] = '\0';

	errno_t err1 = fopen_s(&save, b, "r");

	fscanf_s(save, "%d", &Life::timer_Amount_of_mins);

	fscanf_s(save, "%d", &Peacefull::counter_Of_Peacefull);
	fscanf_s(save, "%d", &Angree::counter_Of_Angree);

	Creation::amount_Of_Creation = Peacefull::counter_Of_Peacefull;
	Creation::amount_Of_Creation += Angree::counter_Of_Angree;

	fscanf_s(save, "%d", &Grass::counter_Of_Grass);
	fscanf_s(save, "%d", &Meat::counter_Of_Meat);

	Food::amount_of_Food = Grass::counter_Of_Grass;
	Food::amount_of_Food += Meat::counter_Of_Meat;

	fscanf_s(save, "%d", &real_amount_of_grass);
	fscanf_s(save, "%d", &real_amount_of_meat);

	if (Angree::counter_Of_Angree == 0)
	{
		Food::amount_of_Food -= Meat::counter_Of_Meat;
	}

	food = new Food * [Food::amount_of_Food];

	for (int i = 0; i < Food::amount_of_Food; i++)
	{
		food[i] = nullptr;
	}

	creation = new Creation * [1000];

	for (int i = 0; i < Peacefull::counter_Of_Peacefull; i++)
	{
		fscanf_s(save, "%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s\n", &x, str, _countof(str), &y, str, _countof(str), &x1, str, _countof(str), &y1, str, _countof(str), &age, str, _countof(str), &speed, str, _countof(str), &radius, str, _countof(str), &energy, str, _countof(str), &duruation, str, _countof(str), &strength, str, _countof(str));
		pos.X = x;
		pos.Y = y;
		target_food.X = x1;
		target_food.Y = y1;
		creation[i] = new Peacefull(pos, target_food, age,speed, radius, energy, duruation, strength);
	}
	for (int i = Peacefull::counter_Of_Peacefull; i < Creation::amount_Of_Creation; i++)
	{
		fscanf_s(save, "%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s\n", &x, str, _countof(str), &y, str, _countof(str), &x1, str, _countof(str), &y1, str, _countof(str), &age, str, _countof(str), &speed, str, _countof(str), &radius, str, _countof(str), &energy, str, _countof(str), &duruation, str, _countof(str), &strength, str, _countof(str), &just_hitten, str, _countof(str));
		
		pos.X = x;
		pos.Y = y;
		target_food.X = x1;
		target_food.Y = y1;
		creation[i] = new Angree(pos, target_food, age, speed, radius, energy, duruation, strength, just_hitten);
	}
	for (int i = 0; i < real_amount_of_grass; i++)
	{
		fscanf_s(save, "%d%s%d%s%d%s", &x, str, _countof(str), &y, str, _countof(str), &energy, str, _countof(str));
		pos.X = x;
		pos.Y = y;
		food[i] = new Grass(pos, energy);
	}
	for (int i = Grass::counter_Of_Grass; i < Grass::counter_Of_Grass + real_amount_of_meat; i++)
	{
		fscanf_s(save, "%d%s%d%s%d%s", &x, str, _countof(str), &y, str, _countof(str), &energy, str, _countof(str));
		pos.X = x;
		pos.Y = y;
		food[i] = new Meat(pos, energy);
	}
	fclose(save);
}
void Life::Do()
{
	for (int i = 0; i < Creation::amount_Of_Creation; i++)
	{
		creation[i]->Move_Blat_I_Dont_Know_How_To_Do_It_correct(food, creation);

		creation[i]->energy -= creation[i]->speed; // витрачення енергії

		creation[i]->Not_OnEach_Other(i, this->creation);// Щоб не були один на одному. Потрібно перевіряти тільки зелених з зеленими та червоних з червоними,
														 // бо червоні по цій же формулі їдять зелених
		
		creation[i]->Bundling(creation);//розмноження мирні роздвигають масив створіннь та нове створіння стає остнаннім мирним
										//  на перед першим агресивним а агресивні просто стають в кінець
	}

	for (int i = 0; i < Creation::amount_Of_Creation; i++)
	{	
		if (creation[i]->Become_Older_and_Chek_Dead()) //перевірка на смерть та створення м'яса
		{

			for (int e = Angree::counter_Of_Angree; e < Creation::amount_Of_Creation; e++)
			{
				if (creation[e]->nomer_of_target_food == i && creation[e]->what_to_do_where_to_go == 3)
					creation[e]->what_to_do_where_to_go = 0;
				if (creation[e]->nomer_of_target_food > i && creation[e]->what_to_do_where_to_go == 3)
					creation[e]->nomer_of_target_food--;
			}
			for (int e = Grass::counter_Of_Grass; e < Food::amount_of_Food; e++)
			{
				if (food[e] == nullptr)
				{
					food[e] = new Meat(creation[i]->Get_Pos(), Grass_Energy);
					break;
				}
			}

			delete creation[i];

			for (int e = i; e < Creation::amount_Of_Creation - 1; e++)
			{
				creation[e] = creation[e + 1];
			}

			creation[Creation::amount_Of_Creation - 1] = nullptr;

			Creation::amount_Of_Creation--;

			if (i < Peacefull::counter_Of_Peacefull)
				Peacefull::counter_Of_Peacefull--;
			else
				Angree::counter_Of_Angree--;
		}
	}
	
	If_your_food_was_eaten_look_for_new(); //Перевірка чи не з'їдена їжа, якщо її хтось з'їв, то потрібно шукати нову

	int counter_of_max_recovered_food = 0;

	for (int i = 0; i < Grass::counter_Of_Grass; i++) 	// їжа нова з'являється
	{
		if (counter_of_max_recovered_food >= Max_Recovered_Food_Per_Moment)
			break;
		if (food[i] == nullptr)
		{
			counter_of_max_recovered_food++;

			COORD pos;
			pos.X = rand() % 1195;
			pos.Y = rand() % 570;
			pos.X += 5;
			pos.Y += 5;
			food[i] = new Grass(pos, Grass_Energy);	
		}
	}
}

void Life::Save()
{
	int Amount_Of_Saves;

	FILE* f1, * save;

	errno_t err1;

	if (this->nomer_Of_Save == 0)
	{
		Amount_Of_Saves = Get_Amount_of_Saves();

		
		err1 = fopen_s(&f1, "AmountOfSaves.txt", "w");
		fclose(f1);

		err1 = fopen_s(&f1, "AmountOfSaves.txt", "r+");

		Amount_Of_Saves++;

		fprintf_s(f1, "%d", Amount_Of_Saves);

		fclose(f1);
	}
	else
		Amount_Of_Saves = this->nomer_Of_Save;

	char b[10];
	
	char str[3];
	b[0] = 'S';
	b[1] = 'a';
	b[2] = 'v';
	b[3] = 'e';
	(_itoa_s(Amount_Of_Saves, &b[4],_countof(str), 10));
	b[5] = '.';
	b[6] = 't';
	b[7] = 'x';
	b[8] = 't';
	b[9] = '\0';
	
	err1 = fopen_s(&save, b, "w");

	fclose(save);

	err1 = fopen_s(&save, b, "r+");

	fprintf_s(save, "%d\n", Life::timer_Amount_of_mins);

	fprintf_s(save, "%d\n", Peacefull::counter_Of_Peacefull);
	fprintf_s(save, "%d\n", Angree::counter_Of_Angree);
	fprintf_s(save, "%d\n", Grass::counter_Of_Grass);
	fprintf_s(save, "%d\n", Meat::counter_Of_Meat);

	int realamount_of_grass = 0, realamount_of_meat = 0;

	//Бо є пусті вказівники на їжу
	for (int i = 0; i < Grass::counter_Of_Grass; i++)
	{
		if (food[i] != nullptr)
		{
			realamount_of_grass++;
		}
	}
	for (int i = Grass::counter_Of_Grass; i < Food::amount_of_Food; i++)
	{
		if (food[i] != nullptr)
		{
			realamount_of_meat++;
		}
	}
	fprintf_s(save, "%d\n",realamount_of_grass);
	fprintf_s(save, "%d\n", realamount_of_meat);

	for (int i = 0; i < Peacefull::counter_Of_Peacefull; i++)
	{
		fprintf_s(save, "%d; %d; %d; %d; %d; %d; %d; %d; %d; %d;\n", creation[i]->Get_Pos().X, creation[i]->Get_Pos().Y, creation[i]->target_Food.X, creation[i]->target_Food.Y, creation[i]->age, creation[i]->speed, creation[i]->radius_Feeling_Of_Object, creation[i]->energy, creation[i]->minimal_Guaranted_Life_Duruation, creation[i]->strength);
	}
	for (int i = Peacefull::counter_Of_Peacefull; i < Creation::amount_Of_Creation; i++)
	{
		//Angree* angree = dynamic_cast<Angree*> (creation[i]); angree->Get_nomer_of_just_hitten()
		fprintf_s(save, "%d; %d; %d; %d; %d; %d; %d; %d; %d; %d; %d;\n", creation[i]->Get_Pos().X, creation[i]->Get_Pos().Y, creation[i]->target_Food.X, creation[i]->target_Food.Y, creation[i]->age, creation[i]->speed, creation[i]->radius_Feeling_Of_Object, creation[i]->energy, creation[i]->minimal_Guaranted_Life_Duruation, creation[i]->strength, dynamic_cast<Angree*> (creation[i])->Get_nomer_of_just_hitten());
	}
	for (int i = 0; i < Food::amount_of_Food; i++)
	{
		if (food[i] == nullptr)
			continue;
		fprintf_s(save, "%d; %d; %d;\n", food[i]->position.X, food[i]->position.Y, food[i]->energy);
	}
	fclose(save);

	for (int i = 0; i < 1000; i++)
	{
		/*creation[i] = nullptr;*/
	}
	for (int i = 0; i < Food::amount_of_Food; i++)
	{
		if(food[i] != nullptr)
			delete food[i];
		food[i] = nullptr;
	}
}

void Life::Delete_All_Saves()
{
	FILE* f1;
	errno_t err1 = fopen_s(&f1, "AmountOfSaves.txt", "w");
	fclose(f1);

	err1 = fopen_s(&f1, "AmountOfSaves.txt", "r+");

	int Amount_Of_Saves = 0;

	fprintf_s(f1, "%d", Amount_Of_Saves);

	fclose(f1);


}

int Life::Get_Amount_of_Saves()
{
	FILE* f1;
	errno_t err1 = fopen_s(&f1, "AmountOfSaves.txt", "r");
	int Amount_Of_Saves;

	fscanf_s(f1, "%d", &Amount_Of_Saves);
	
	fclose(f1);
	return Amount_Of_Saves;
}

void Meat::Draw(CPaintDC &dc)
{
	CPen pen(PS_SOLID, 2, RGB(this->R, this->G, this->B));
	dc.SelectObject(&pen);
	dc.Rectangle(position.X - 2, position.Y - 2, position.X + 2, position.Y + 2);
}

void Grass::Draw(CPaintDC &dc)
{
	CPen pen(PS_SOLID, 2, RGB(this->R, this->G, this->B));
	dc.SelectObject(&pen);
	dc.Rectangle(position.X - 2, position.Y - 2, position.X + 2, position.Y + 2);
}

Life life;
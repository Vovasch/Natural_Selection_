
// Natural selection.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CNaturalselectionApp:
// Сведения о реализации этого класса: Natural selection.cpp
//

class CNaturalselectionApp : public CWinApp
{
public:
	CNaturalselectionApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CNaturalselectionApp theApp;

class Life;

class Food
{
protected:
	friend class Life;
	COORD position;
	int energy;

public:
	Food(COORD position, int energy) {this->position = position, this->energy = energy; }
	inline COORD Get_Pos() { return this->position; }
	virtual void Draw(CPaintDC& dc) = 0;
	inline int Get_Energy(void) { return energy; }
	static int amount_of_Food;
};

class Meat : public Food
{
	int R = 255, G = 0, B = 0;
public:
	Meat(COORD position, int energy) :Food(position, energy) {};
	virtual void Draw(CPaintDC &dc);

	static int counter_Of_Meat;
};

class Grass : public Food
{
	int R = 0, G = 255, B = 0;
public:
	Grass(COORD position, int energy) :Food(position, energy) {};
	virtual void Draw(CPaintDC& dc);

	static int counter_Of_Grass;
};

class Creation
{
protected:
	
	friend class Life;

	COORD position;
	int age ;
	int speed;
	int radius_Feeling_Of_Object;
	int energy;
	int minimal_Guaranted_Life_Duruation;
	int strength;

	COORD target_Food;
	int what_to_do_where_to_go;
	int nomer_of_target_food;

	virtual void Not_Being_On_Each_Other(int nomerofcreation, int range_start, int range_end, Creation** creation);
	virtual void Move(Food** food, Creation** creation, int range_of_Food_start, int rane_of_Food_end);
	void Go_to();
	
public:
	
	Creation(COORD positon,COORD where_To_Go, int age, int speed, int radius_Feeling_Of_Object, int energy, int minimal_Guaranted_Life_Duruation, int strength );

	virtual void Move_Blat_I_Dont_Know_How_To_Do_It_correct(Food** food, Creation** creation) = 0;
	virtual void Draw(CPaintDC& dc);
	
	bool Become_Older_and_Chek_Dead();
	
	virtual void Bundling(Creation** creation) = 0;
	virtual void Not_OnEach_Other(int nomerofcreation, Creation** creation) = 0;
	
	inline int Get_Radius() { return this->radius_Feeling_Of_Object; }
	inline int Get_amount_Energy() { return this->energy; }
	inline COORD Get_Pos() { return this->position; }
	inline void Lose_Energy(int energy) { this->energy -= energy; }

	static int amount_Of_Creation;
	static COORD window;
};

class Peacefull : public Creation
{
	const int R = 0, G = 255, B = 0;
	
public:
	
	Peacefull(COORD positon, COORD where_To_Go, int age, int speed, int radius_Feeling_Of_Object, int energy, int minimal_Guaranted_Life_Duruation, int strength) :Creation(positon,where_To_Go, age, speed, radius_Feeling_Of_Object, energy, minimal_Guaranted_Life_Duruation, strength) {}

	void Draw(CPaintDC& dc)override;
	void Bundling(Creation** creation)override;
	void Not_OnEach_Other(int nomerofcreation, Creation** creation)override { Not_Being_On_Each_Other(nomerofcreation, 0, Peacefull::counter_Of_Peacefull, creation); }
	
	void Move_Blat_I_Dont_Know_How_To_Do_It_correct(Food** food, Creation** creation)override;
	
	static int counter_Of_Peacefull;
};

class Angree : public Creation
{
	const int R = 255, G = 0, B = 0;

	int just_Hitten_Creation;

	void Recive_Energy_from_Peacefull(Creation* creation);

public:
	
	Angree(COORD positon, COORD where_To_Go, int age, int speed, int radius_Feeling_Of_Object, int energy, int minimal_Guaranted_Life_Duruation, int strength, int just_hitten) :Creation(positon, where_To_Go, age, speed, radius_Feeling_Of_Object, energy, minimal_Guaranted_Life_Duruation, strength) { this->just_Hitten_Creation = just_hitten; }
		
	void Draw(CPaintDC& dc)override;
	void Bundling (Creation** creation)override;
	void Not_OnEach_Other(int nomerofcreation, Creation** creation)override{ Not_Being_On_Each_Other(nomerofcreation, Peacefull::counter_Of_Peacefull, Creation::amount_Of_Creation, creation); }
	
	void Move_Blat_I_Dont_Know_How_To_Do_It_correct(Food** food, Creation** creation)override;
	
	int Get_nomer_of_just_hitten() { return this->just_Hitten_Creation; }

	static int counter_Of_Angree;
};

class Life
{
	Creation** creation;
	Food** food;

	int nomer_Of_Save;
	void If_your_food_was_eaten_look_for_new();

public:

	void Draw(CPaintDC &dc);
	void Init();
	void Init_Save(int nomer_of_save);
	void Do();
	void Save();
	void Delete_All_Saves();

	int Get_Amount_of_Saves();

	inline int Get_Nomer_of_Save() { return this->nomer_Of_Save; }
	inline void Set_Nomer_of_Save(int nomer_Of_Save) { this->nomer_Of_Save = nomer_Of_Save; }
	
	static int timer_Amount_of_mins;
};

extern Life life;
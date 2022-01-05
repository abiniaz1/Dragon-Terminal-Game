#include "Dragon.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>

using namespace std;

Dragon::Dragon(string name, string type, bool isHatched, dragonSize curSize,
	dragonSize maxSize, int rarity)
{
	SetName(name);
	SetType(type);
	m_isHatched = isHatched;
	SetCurSize(curSize);
	SetMaxSize(maxSize);
	SetRarity( rarity);
}

string Dragon::GetName()
{
	
	return m_name;
}

void Dragon::SetName(string name)
{
	m_name = name;
}

string Dragon::GetType()
{
	return m_type;
}

void Dragon::SetType(string type)
{
	m_type = type;
}
bool Dragon::GetIsHatched()
{
	return m_isHatched;
}

void Dragon::HatchDragon()
{
	m_isHatched = true;
}

dragonSize Dragon::GetCurSize()
{
	return m_curSize;
}

void Dragon::SetCurSize(dragonSize curSize)
{
	m_curSize = curSize;
}

dragonSize Dragon::GetMaxSize()
{
	return m_maxSize;
}

void Dragon::SetMaxSize(dragonSize maxSize)
{
	m_maxSize = maxSize;
}
int Dragon::GetRarity()
{
	return m_rarity;
}

void Dragon::SetRarity(int rarity)
{
	m_rarity = rarity;
}

bool Dragon::AttemptGrow()
{
	if (GetCurSize() < GetMaxSize())
	{
		cout << "Your dragon grows..." << endl;
		SetCurSize( static_cast<dragonSize>(GetCurSize()+ small));
		return true;
	}
	else
	{
		return false;
	}
}

bool Dragon::AttackDragon(Dragon& randDRG)
{
	string breath = BreathAttack();
	bool grow; //For storing AttemptGrow() result
	if (breath.compare(GetType()) == 0) //determine if enemy dragon dies
	{
		cout << "Whoah! Your dragon used " << GetType() << " breath!" << endl;
		grow = AttemptGrow();
		return false; //Enemy dragon has died
	}
	else
	{
		if (GetCurSize() > randDRG.GetCurSize())
		{
			cout << "Your dragon has defeated the enemy dragon!" << endl;
			grow = AttemptGrow();
			return false; // Enemy dragon has died
		}
		else if (GetCurSize() == randDRG.GetCurSize())
		{
			cout << "The battle ends with a draw..." << endl;
			grow = AttemptGrow();
			return false; //Even if the battle is a draw

		}
		else
		{
			cout << "Your dragon was defeated!" << endl;
			return true; //User dragon has died
		}
	}
}

string Dragon::BreathAttack()
{
	srand(unsigned(time(0)));
	int ranNum = rand() % 101; //Random number from 0-100
	string fail = "fail"; //String to mark failure
	if (ranNum < 5) // for 5% chance
	{
		return GetType();
	}
	else
	{
		return fail;
	}
}

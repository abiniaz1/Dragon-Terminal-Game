// File: Extras.cpp
// Author: Abid Niaz
// Date: 3-19-18
// Description: Provides extra functions, specifically for printing sprites

#include "stdafx.h"

#include "Dragon.h"
#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>





void printDragon(int level);
void printEgg();

// Pre-Condition: none
// Post-Condition: Specific dragon is printed
void printDragon(int level)
{
	ifstream myFile("LVL_" + (to_string(level)) + "_DRG.txt");
	char c;
	while (myFile) //Prints each character
	{
		myFile.get(c);
		cout << c;
	}
	myFile.close();
}

// Pre-Condition: none
// Post-Condition: egg is printed
void printEgg()
{
	ifstream myFile("EGG_DRG.txt");
	char c;
	while (myFile) //Prints each character
	{
		myFile.get(c);
		cout << c;
	}
	myFile.close();
}

void printMenu()
{
	ifstream myFile("MENU_DRG.txt");
	char c;
	while (myFile) //Prints each character
	{
		myFile.get(c);
		cout << c;
	}
	myFile.close();
}

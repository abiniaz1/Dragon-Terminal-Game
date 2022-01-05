#include "stdafx.h"
#include "Dragon.h"
#include "Game.h"
#include "Extras.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const int NAME = 1; //name flag for LoadDragons()
const int TYPE = 2; //type flag for LoadDragons()
const int SIZE = 3; //size flag for LoadDragons()
const int RARE = 4; //rarity flag for LoadDragons()
const int EXIT = 5; // constant for exit prompt in StartGame()
const int SEARCH = 1; //constant for search flag in Start Game()
const int HATCH = 2; //For hatch flag in StartGame()
const int DISPLAY = 3; //For display flag in StartGame()
const int ATK = 4; //For attack flag in StartGame()

Game::Game()
{
	string userName;
	cout << "Welcome to Dragon Wars!\n\nWhat is your name? ";
	getline(cin, userName);
	cout << endl << "Good luck, " << userName << '!' << endl;
	m_name = userName;
	LoadDragons();
}
void Game::LoadDragons()
{
	ifstream myList("data.txt");
	char c;
	string line;
	string name;
	string type;
	dragonSize size;

	int count = 0;
	while (myList)
	{
		myList.get(c);
		if (c == ',' || c == '\n')
		{
			count++;
			if (count == 1) // sets the name
			{
				name = line; //marker.....................
			}
			else if (count == 2) // sets the type
			{
				type = line; //marker.....................
			}
			else if (count == SIZE) // sets the dragonSize
			{
				if (stoi(line) == 1) //each enumerator value for dragonSize
				{
					size = dragonSize::tiny;
				}
				else if (stoi(line) == 2)
				{
					size = dragonSize::small;
				}
				else if (stoi(line) == 3)
				{
					size = dragonSize::medium;
				}
				else if (stoi(line) == 4)
				{
					size = dragonSize::large;
				}
				else
				{
					size = dragonSize::huge;
				}
			}
			else // sets rarity and resets count and constructs the dragon
			{
				int rarity = stoi(line); //marker................
				count = 0;
				m_dragons.push_back(Dragon(name, type, false, dragonSize::tiny, size, rarity));
			}

			line = ""; // resets line
		}
		else
		{
			line = line + c;
		}
	}
}

void Game::SearchEgg()
{
	int userNum;
	int rarity;
	bool success; //used for determining if egg will be found
	bool found = false; //used to find egg

	cout << "Select a rarity to search for(1-10)\n(1 = Very Common, 10 = \"Hahaha!...good luck\")" << endl;
	cin >> userNum;
	while (userNum > 10 || userNum < 1) // input validation
	{
		cout << "Invalid input\nTry again ";
		cin >> userNum;
	}

	srand(unsigned(time(0))); //Starts the random algorithm
	rarity = 100 - (userNum * 9); // 9 for the rarity percentage formula

	int gamble = rand() % (100 + 1); //out of 100 for easy percentage
	if (gamble > rarity) //Checks to see if gamble is outside of rarity threshold
	{
		success = false;
	}
	else
	{
		success = true;
	}

	if (success == true) //Gets random egg of specific rarity
	{
		while (found != true) //Searches for random egg of user specified rarity
		{
			int ranNum = rand() % (m_dragons.size() - 1);
			int eggRarity = m_dragons[ranNum].GetRarity();
			if (eggRarity == userNum)
			{
				m_myDragons.push_back(m_dragons[ranNum]); //adds dragon egg to users list of dragons
				cout << "You found a " << m_dragons[ranNum].GetName() << " egg!" << endl;
				found = true;
				printEgg();
			}
		}
	}
	else
	{
		cout << "You didn't find a dragon egg of this rarity..." << endl;
	}
}

void Game::HatchEgg()
{
	int userNum;
	bool hatchable = false;
	DisplayMyDragons();
	for (unsigned int i = 0; i != m_myDragons.size(); i++) //Checking to see if there is an egg to hatch
	{
		if (m_myDragons[i].GetIsHatched() == false)
		{
			hatchable = true;
		}
	}
	if (m_myDragons.size() == 0) // Stops if there are no dragons
	{
		cout << "You can't hatch eggs if you don't have any dragons..." << endl;
	}
	else if (hatchable == false) //Stops if there are no eggs
	{
		cout << "You can't hatch eggs if you don't have any eggs..." << endl;
	}
	else
	{
		srand(unsigned(time(0))); //Starts the random algorithm
		cout << endl;
		cout << "Choose an egg to hatch: ";
		cin >> userNum;
		while (userNum < 1 || userNum > unsigned(m_myDragons.size())) //Input validation
		{
			cout << "INVALID INPUT\n\nTry again ";
			cin >> userNum;
		}
		int ranNum = rand() % 101; //Gets a random number from 0-100
		cout << endl;
		while (m_myDragons[userNum - 1].GetIsHatched() == true) //-1 to account for display distortion and vectors
		{
			cout << "Enter a valid dragon: ";
			cin >> userNum;
			while (userNum < 1 || userNum > unsigned(m_myDragons.size())) //Input validation
			{
				cout << "INVALID INPUT\n\nTry again ";
				cin >> userNum;
			}
		}
		if (ranNum < 50) //50 used for 50%
		{
			//Success
			m_myDragons[userNum - 1].HatchDragon();
			printDragon(m_myDragons[userNum - 1].GetRarity());
			cout << "Congratulations!\n\n Your " << m_myDragons[userNum - 1].GetName() << " has hatched!" << endl;
		}
		else
		{
			cout << "Egg has failed to hatch..." << endl;
		}
	}
}

void Game::StartGame()
{
	int userNum;
	do
	{
		userNum = MainMenu();
		if (userNum == SEARCH)
		{
			SearchEgg();
		}
		else if (userNum == HATCH)
		{
			HatchEgg();
		}
		else if (userNum == DISPLAY)
		{
			DisplayMyDragons();
		}
		else if (userNum == ATK)
		{
			Attack();
		}
		else
		{
			cout << "Goodbye!" << userNum << endl;
		}
	} while (userNum != EXIT);
	cout << "Thank you for playing!" << endl;
}

void Game::DisplayMyDragons()
{
	if (m_myDragons.size() == 0)
	{
		cout << "You have no dragons..." << endl;
	}
	else
	{
		cout << "************************************" << endl;
		cout << m_name << "'s Dragons:" << endl;
		cout << endl; //Setw() numbers derived through experimentation
		cout << setw(10) << "Number" << setw(30) << "Name" << setw(10) << "Type" << setw(15) << "Egg / Dragon" << setw(15) << "Current Size" << setw(15) << "Max Size" << endl;
		for (unsigned int i = 0; i != m_myDragons.size(); i++)
		{
			string forEgg;
			if (m_myDragons[i].GetIsHatched() == true)
			{
				forEgg = "Dragon";
			}
			else
			{
				forEgg = "Egg";
			}
			cout << setw(10) << i + 1 << setw(30);
			cout << m_myDragons[i].GetName() << setw(10) << m_myDragons[i].GetType() << setw(15) << forEgg << setw(15) << m_myDragons[i].GetCurSize() + 1 << setw(15) << m_myDragons[i].GetMaxSize() + 1 << endl;
		}
	}
}

int Game::MainMenu()
{
	int userNum;
	printMenu();
	cout << "Enter a command: ";
	cin >> userNum;
	while (userNum < 1 || userNum > 5)
	{
		cout << "INVALID INPUT\nTry again: ";
		cin >> userNum;
	}
	return userNum;
}

void Game::Attack()
{
	bool hatched = false;

	for (unsigned int i = 0; i != m_myDragons.size(); i++) //Checking to see if there is a hatched egg
	{
		if (m_myDragons[i].GetIsHatched() == true)
		{
			hatched = true;
		}
	}
	if (hatched == true)
	{
		bool result;// variable for AttackDragon() result
		//find a random dragon
		srand(unsigned(time(0)));
		int ranNum = rand() % m_dragons.size();               // Gets a number for all dragons loaded
		Dragon randDRG = m_dragons[ranNum];                   // random dragon
		randDRG.HatchDragon();                                // prepares random dragon
		int ranSize = rand() % (randDRG.GetMaxSize() + 1);    // Gets a random size for the dragon
		randDRG.SetCurSize(static_cast<dragonSize>(ranSize)); // Sets the size for the dragon

		// ask user if they want to fight
		cout << endl;
		cout << endl;
		printDragon(randDRG.GetRarity());//Prints the dragon sprite to give the user a hint
		cout << "You found a " << randDRG.GetName() << " to fight!\nWould you like to fight?(y/n)";
		char userChoice;
		cin >> userChoice;
		while (userChoice != 'y' && userChoice != 'n') //input validation
		{
			cout << "INVALID INPUT\nTry again(y/n): ";
			cin >> userChoice;
		}
		if (userChoice == 'y')
			// if yes, compare dragons and calculate breath attack. Else, stop
		{
			int userNum;
			DisplayMyDragons();
			do //Input validation
			{
				cout << "Choose a dragon for battle: ";
				cin >> userNum;
				if (userNum > unsigned(m_myDragons.size()) || userNum < 1) //input validation
				{
					cout << "INVALID INPUT" << endl;
				}
				else if (m_myDragons[userNum - 1].GetIsHatched() == false)
				{
					cout << "That is only an egg. An egg cannot fight, no matter how hard you try..." << endl;
				}
			} while (userNum > unsigned(m_myDragons.size()) || userNum < 1 || m_myDragons[userNum - 1].GetIsHatched() == false);

			//Attacking enemy
			result = m_myDragons[userNum - 1].AttackDragon(randDRG);
			if (result == true) //Enemy wins
			{
				m_myDragons.erase(m_myDragons.begin() + userNum - 1);
			}
		}
		else
		{
			cout << "ole" << endl;
		}
		// if yes, compare dragons and calculate breath attack. Else, stop
		// if player dragon is bigger, player wins and dragon gets bigger. Else, dragon dies and is removed
	}
	else
	{
		cout << "You have no hatched dragons..." << endl;
	}
}

void Game::DisplayAllDragons()
{
	for (unsigned int i = 0; i != m_dragons.size(); i++)
	{
		cout << m_dragons[i].GetName() << ' ' << m_dragons[i].GetType() << ' ' << m_dragons[i].GetIsHatched() << ' ' << m_dragons[i].GetMaxSize() + 1 << ' ' << m_dragons[i].GetRarity() << endl;
	}
}
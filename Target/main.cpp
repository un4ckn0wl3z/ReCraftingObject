#include <cstdio>
#include <cstdint>
#include <iostream>
#include <Windows.h>

class Player
{
public:
	char name[20];  // instance address + 0
	int skinID;     // instance address + sizeof(name)
	float health;	// instance address + sizeof(name) + izeof(skinID)
	float armour;	// instance address + sizeof(name) + izeof(skinID) + izeof(health)

	/*
	assuming instance address is 0x500ACE65
	char name[20];  // 0x500ACE65 + 0
	int skinID;     // 0x500ACE65 + 20
	float health;	// 0x500ACE65 + 24
	float armour;	// 0x500ACE65 + 28
	*/

	Player(char* theName, int theSkinID, float theHealth, float theArmour) {
		std::cout << "[+] Initialize player....." << std::endl;
		std::memcpy(name, theName, sizeof(name));
		skinID = theSkinID;
		health = theHealth;
		armour = theArmour;

		std::cout << "[+] Player info " << std::endl;
		std::cout << "[+] Player Name: " << this->name << std::endl;
		std::cout << "[+] Player SkinID: " << this->skinID << std::endl;
		std::cout << "[+] Player Health: " << this->health << std::endl;
		std::cout << "[+] Player Armour: " << this->armour << std::endl;
		std::cout << "-----------------------------------------\n" << std::endl;


		
	}

};


void GamLogic(Player* player) {
	while (true)
	{

		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {

			player->health -= 0.5f;
			player->armour -= 1.0f;

			std::cout << "\nCurrent player health: " << player->health << std::endl;
			std::cout << "Current player armour: " << player->armour << std::endl;
		}


		if (GetAsyncKeyState(VK_ESCAPE) & 1) {
			break;
		}

		Sleep(100);
	}
}

int main() {

	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "          Simple Game Logic              " << std::endl;
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "[+] Press NUMPAD1 to attack" << std::endl;
	std::cout << "[+] Press ESCAPE to exit" << std::endl;

	Player* ptrPlayer = new Player((char*)"Anuwat", 70789, 100.0f, 100.0f);
	GamLogic(ptrPlayer);

	std::cout << "[+] Game exit" << std::endl;
	delete ptrPlayer;

	system("pause");
	return 0;
}
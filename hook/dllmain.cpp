#include <iostream>
#include "mem.h"
#include "Player.h"

/*
ORIGINAL opcode

Target.exe+12790 - 8B 4D 08              - mov ecx,[ebp+08]
---------------------------------HOOK------------------------------------
Target.exe+12793 - F3 0F11 41 18         - movss [ecx+18],xmm0
Target.exe+12798 - 8B 45 08              - mov eax,[ebp+08]
*/

uintptr_t moduleBase;
BYTE* originAddress;
DWORD* playerPtr;
HMODULE myhModule;


DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(myhModule, 0);
}


void __declspec(naked) ourFunct() {

	__asm {
		mov playerPtr, ecx
		jmp originAddress
	}
}


DWORD WINAPI HackThread(HMODULE hModule)
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout); // output only
	std::cout << "[+] Entrypoint reached" << std::endl;
	ZeroMemory(&playerPtr, sizeof(DWORD));

	std::cout << "[+] playerPtr address : " << &playerPtr << std::endl;
	std::cout << "[+] playerPtr value: " << playerPtr << std::endl;

	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
	DWORD hookAddress = ((DWORD)moduleBase + 0x12793);
	// Hook
	int hookLength = 8;

	originAddress = mem::TrampHook32((BYTE*)hookAddress, (BYTE*)ourFunct, hookLength);

	Player* pPlayer;
	ZeroMemory(&pPlayer, sizeof(Player));

	while (true) {

		if (GetAsyncKeyState(VK_NUMPAD7)) {
			std::cout << "[+] playerPtr value: " << playerPtr << std::endl;
			
			std::uint8_t* playerAdress = reinterpret_cast<std::uint8_t*>(playerPtr);
			char* pName = (char*)(playerAdress);
			int* pSkinID = (int*)(playerAdress + 0x14); // 20 in dec
			float* pHealth = (float*)(playerAdress + 0x18); // 24 in dec
			float* pArmour = (float*)(playerAdress + 0x1C); // 28 in dec

			std::printf("\npName: %s\npSkin ID: %d\npHealth: %.2f\npArmour: %.2f\n\n",
				pName, (*pSkinID), (*pHealth), (*pArmour)
			);

			pPlayer = reinterpret_cast<Player*>(playerPtr);


		};

		if (GetAsyncKeyState(VK_NUMPAD9)) {
			pPlayer->health += 100.0f;
			pPlayer->armour += 100.0f;

			std::cout << "\nCurrent player health: " << pPlayer->health << std::endl;
			std::cout << "Current player armour: " << pPlayer->armour << std::endl;
		};

		Sleep(100);
	}
		/*
	fclose(fp);
	FreeConsole();
	*/

	CreateThread(0, 0, EjectThread, 0, 0, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		myhModule = hModule;
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
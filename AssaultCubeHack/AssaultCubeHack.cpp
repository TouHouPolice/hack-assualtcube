// AssaultCubeHack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "bypass.h"
#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;

uintptr_t playerBaseAddress = 0x509B74;
uintptr_t assualtRifleLoadedAmmoOffset[] = { 0x150,0,0 };
DWORD gameProcessID;

int ammoValue = 666;

uintptr_t FindPointerAddress(int pointerLevel, Bypass* hBypass, uintptr_t baseAddress, uintptr_t offset[]);

int main()
{
	
	cout << "Press any key to start hacking" << endl;
	system("pause");

	Bypass* mBypass = new Bypass();
	LPCSTR windowName = "AssaultCube";
	HWND gameWindow=FindWindowA(NULL, windowName);
	if (gameWindow != NULL) {
		cout << "Game is active, hack start" << endl;
	}
	else {
		cout << "Game not found, last error " << GetLastError() << endl;
	}


	GetWindowThreadProcessId(gameWindow, &gameProcessID);
	cout << "Process ID is : " << gameProcessID << endl;
	
	if (mBypass->Attach(gameProcessID)==false) {
		cout << "game attach failed" << endl;
		cout << "last error: " << GetLastError() << endl;
		system("pause");
	};
	
	
	uintptr_t assualtRifleLoadedAmmoPointer = FindPointerAddress(1, mBypass, playerBaseAddress,assualtRifleLoadedAmmoOffset);
	
	cout << "pointer address: " <<hex<< assualtRifleLoadedAmmoPointer << endl;

	if (!mBypass->Write(assualtRifleLoadedAmmoPointer, &ammoValue, sizeof(ammoValue))) {
		cout << "Hacking failed, last error: " <<GetLastError()<< endl;
		
		system("pause");
	}
	else {
		cout << "Unlimited Ammo Successful!" << endl;
	}
	int currentAmmo = 0;
	if (!mBypass->Read(assualtRifleLoadedAmmoPointer, &currentAmmo, sizeof(int))) {
		cout << "Read process memory failed, last error: " << GetLastError() << endl;
		
		system("pause");
	};
	cout << "current ammo value :" <<dec<< currentAmmo << endl;
	cout << "Press any key to quit" << endl;
	system("pause");
	
	//mBypass->Close();


    return EXIT_SUCCESS;
}

uintptr_t FindPointerAddress(int pointerLevel, Bypass* hBypass, uintptr_t baseAddress, uintptr_t offset[]) {
	uintptr_t pointerAddress=0x0;
	uintptr_t tempAddress =0x0;
	
	for (int i = 0; i < pointerLevel; i++) {
		if (i == 0) {
			if (!hBypass->Read(baseAddress, &tempAddress, sizeof(tempAddress))) {
				cout << "something wrong" << endl;
				cout << "last error: " << GetLastError()<<endl;
				system("pause");
			};
			
		}
		cout << "base address :" << hex << baseAddress << endl;
		cout << "current temp address: " <<hex<< tempAddress << endl;
		pointerAddress = tempAddress + offset[i];
		hBypass->Read(pointerAddress, &tempAddress, sizeof(tempAddress));

	}
	return pointerAddress;
}


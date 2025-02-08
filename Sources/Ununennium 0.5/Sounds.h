namespace Bytebeat {
	void Sound1() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 17000, 17000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[17000 * 15] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t^t*(t>>12))&128);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

	void Sound2() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 17000, 17000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[17000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((t*t>>5|t)-t)/5);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
} // a recompile

	void Sound3() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[17000 * 25] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*(t^8|t^5)/0x1448);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

	void Sound4() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t^(t>>6)-t);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

	void Sound5() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[16000 * 22] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t^(t>>5|t>>8*t))%500);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}

	void Sound6() {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[32000 * 5] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*rand());

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
}
}


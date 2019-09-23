#include "SoundfontTester.h"
#include <cmath>
#include <iostream>

float SoundfontTester::GetVolume(HSOUNDFONT soundfont, int bank, int program, int key, int velocity)
{
	HSTREAM stream = BASS_MIDI_StreamCreate(16, BASS_SAMPLE_FLOAT | BASS_STREAM_DECODE, 0);
	BassAssert();

	BASS_MIDI_FONT font;
	font.font = soundfont;
	font.bank = 0;
	font.preset = -1;
	BASS_MIDI_StreamSetFonts(stream, &font, 1);
	BassAssert();

	int channel = 0;
	if (bank == 128)
	{
		channel = 9;
		bank = 0;
	}
	BASS_MIDI_StreamEvent(stream, channel, MIDI_EVENT_BANK, bank);
	BassAssert();
	BASS_MIDI_StreamEvent(stream, channel, MIDI_EVENT_PROGRAM, program);
	BassAssert();
	BASS_MIDI_StreamEvent(stream, channel, MIDI_EVENT_NOTE, MAKEWORD(key, velocity));
	BassAssert();

	float* fft = new float[32768];
	float maxSum = 0.0F;
	for (int i = 0; i < 5; i++)
	{
		BASS_ChannelGetData(stream, fft,
			BASS_DATA_FFT32768 | BASS_DATA_FFT_NOWINDOW | BASS_DATA_FFT_INDIVIDUAL);
		BassAssert();
		float sum = 0.0F;
		for (int d = 0; d < 32768; d++)
		{
			sum += fft[d];
		}
		if (sum > maxSum)
		{
			maxSum = sum;
		}
	}
	delete[] fft;
	BASS_StreamFree(stream);
	BassAssert();
	return maxSum;
}

void SoundfontTester::BassAssert()
{
	assertCount++;
	int errorCode = BASS_ErrorGetCode();
	if (errorCode != 0)
	{
		cout << "BASS error code: " << errorCode << endl;
		cout << "Assert count: " << assertCount << endl;
		system("PAUSE");
	}
}

SoundfontTester::SoundfontTester(const string& referenceSoundfontPath, const string& testedSoundfontPath)
{
	reference = BASS_MIDI_FontInit(referenceSoundfontPath.c_str(), NULL);
	BassAssert();
	BASS_MIDI_FontSetVolume(reference, 0.1F);
	BassAssert();
	tested = BASS_MIDI_FontInit(testedSoundfontPath.c_str(), NULL);
	BassAssert();
	BASS_MIDI_FontSetVolume(tested, 0.1F);
	BassAssert();
}

SoundfontTester::~SoundfontTester()
{
	BASS_MIDI_FontFree(reference);
	BassAssert();
	BASS_MIDI_FontFree(tested);
	BassAssert();
}

float SoundfontTester::GetAttenuation(int bank, int program, int key, int velocity)
{
	return 15.0F * log2f(GetVolume(tested, bank, program, key, velocity)
		/ GetVolume(reference, bank, program, key, velocity));
}

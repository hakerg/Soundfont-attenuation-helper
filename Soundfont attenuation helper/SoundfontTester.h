#pragma once
#include <string>
#include "bass.h"
#include "bassmidi.h"
using namespace std;

class SoundfontTester
{
private:

	int assertCount = 0;

protected:

	SoundfontTester(const string& testedSoundfontPath);

	void LoadSoundfont(const string& path, HSOUNDFONT& target, float volumeMultiplier = 1.0F);
	void FreeSoundfont(HSOUNDFONT soundfont);

public:

	HSOUNDFONT tested;

	virtual ~SoundfontTester();

	void BassAssert();

	float GetVolume(HSOUNDFONT soundfont, int bank, int program, int key, int velocity);

	virtual float GetAttenuation(int bank, int program, int key, int velocity) = 0;

	float GetAttenuation(int bank, int program, int velocity);
};


#pragma once
#include <string>
#include "bass.h"
#include "bassmidi.h"
using namespace std;

class SoundfontTester
{
private:

	int assertCount = 0;
	float GetVolume(HSOUNDFONT soundfont, int bank, int program, int key, int velocity);

public:

	HSOUNDFONT reference, tested;

	void BassAssert();

	SoundfontTester(const string& referenceSoundfontPath, const string& testedSoundfontPath);
	~SoundfontTester();

	float GetAttenuation(int bank, int program, int key, int velocity);
};


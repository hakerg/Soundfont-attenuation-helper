#pragma once
#include "SoundfontTester.h"
class SoundfontTesterProgram0 :
	public SoundfontTester
{
public:

	float referenceVolume;

	SoundfontTesterProgram0(const string& testedSoundfontPath);

	float GetAttenuation(int bank, int program, int key, int velocity) override;
};


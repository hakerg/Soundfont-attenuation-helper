#include "SoundfontTesterProgram0.h"

SoundfontTesterProgram0::SoundfontTesterProgram0(const string& testedSoundfontPath)
	: SoundfontTester(testedSoundfontPath)
{
	referenceVolume = GetVolume(tested, 0, 0, 60, 127);
}

float SoundfontTesterProgram0::GetAttenuation(int bank, int program, int key, int velocity)
{
	return 15.0F * log2f(GetVolume(tested, bank, program, key, velocity) / referenceVolume);
}

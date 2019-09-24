
#include "SoundfontTesterReference.h"

SoundfontTesterReference::SoundfontTesterReference
	(const string& testedSoundfontPath, const string& referenceSoundfontPath,
		float referenceVolumeMultiplier) :
	SoundfontTester(testedSoundfontPath)
{
	LoadSoundfont(referenceSoundfontPath, reference, referenceVolumeMultiplier);
}

SoundfontTesterReference::~SoundfontTesterReference()
{
	FreeSoundfont(reference);
}

float SoundfontTesterReference::GetAttenuation(int bank, int program, int key, int velocity)
{
	return 15.0F * log2f(GetVolume(tested, bank, program, key, velocity)
		/ GetVolume(reference, bank, program, key, velocity));
}

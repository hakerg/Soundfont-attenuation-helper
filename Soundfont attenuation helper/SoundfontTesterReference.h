
#include "SoundfontTester.h"
class SoundfontTesterReference :
	public SoundfontTester
{
public:

	HSOUNDFONT reference;

	SoundfontTesterReference
		(const string& testedSoundfontPath, const string& referenceSoundfontPath,
			float referenceVolumeMultiplier);
	~SoundfontTesterReference();

	float GetAttenuation(int bank, int program, int key, int velocity) override;
};

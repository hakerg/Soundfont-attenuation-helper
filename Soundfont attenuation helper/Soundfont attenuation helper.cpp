// Soundfont attenuation helper.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "SoundfontTester.h"
using namespace std;

SoundfontTester * tester;

void check(int bank, int program, int key)
{
	const char* name = BASS_MIDI_FontGetPreset(tester->tested, program, bank);
	if (name)
	{
		float attenuation = tester->GetAttenuation(bank, program, key, 127);
		if (isnormal(attenuation))
		{
			int rounded = roundf(attenuation);
			if (rounded != 0)
			{
				cout << "Attenuation to apply to " << bank << ":" << program <<
					" key " << key << ": " << rounded << " dB - " << name << endl;
			}
		}
	}
}

int main(int argc, char** argv)
{
	BASS_Init(-1, 44100, NULL, NULL, NULL);
	string reference = "C:\\Users\\grzeg\\Soundfonty\\Scc1t2.sf2";
	string filename = "C:\\Users\\grzeg\\Soundfonty\\Papelmedia SF2 GM 2007.sf2";
	if (argc > 1)
	{
		filename = argv[1];
	}
	tester = new SoundfontTester(reference, filename);
	for (int b = 0; b < 128; b++)
	{
		for (int p = 0; p < 128; p++)
		{
			check(b, p, 60);
		}
		cout << endl;
	}
	cout << endl;
	for (int p = 0; p < 128; p++)
	{
		for (int k = 0; k < 128; k++)
		{
			check(128, p, k);
		}
		cout << endl;
	}
	cout << endl;
	delete tester;
	system("PAUSE");
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln

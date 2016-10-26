#include "BullCowGame.h"
#include <map>

#define TMap std::map


CBullCowGame::CBullCowGame()
{
	Reset();
}

CBullCowGame::~CBullCowGame()
{
}

int32 CBullCowGame::getMaxEssai()const
{
	TMap<int32, int32> LgMotEssaiMax{ {3,4}, {4,7}, {5,10}, {6, 16}, {7, 20} };
	return LgMotEssaiMax[MotCache.length()];
}

int32 CBullCowGame::getEssaiCourant()const
{
	return this->EssaiCourant;
}

void CBullCowGame::setEssaiCourant(int32 nEssai)
{
	this->EssaiCourant = nEssai;
}

/*void CBullCowGame::setMaxEssai(int32 nEssai)
{
	//this->MaxEssai = nEssai;
}*/

void CBullCowGame::Reset()
{
	this->EssaiCourant = 1;
	//constexpr int32 MAX_ESSAI = 8;
	//this->MaxEssai = MAX_ESSAI;

	const FString MOTCACHE = "avion";
	MotCache = MOTCACHE;

	gagne = false;
}

bool CBullCowGame::Gagne()const
{
	return gagne;
}

EWordStatus CBullCowGame::TestValideMot(FString Mot)const
{
	if (!estIsogram(Mot)){ //si pas isogram
		return EWordStatus::Not_Isogram;
	}
	else if (!estLowerCase(Mot)) { //si pas minuscule

		return EWordStatus::Not_Lowercase;
	}
	else if (Mot.length() != getLongMotCache()) {
		return EWordStatus::Wrong_Length;
	}
	else {
		return EWordStatus::Ok;
	}
}

int32 CBullCowGame::getEWordStatus() const
{
	return (int)status;
}

// receives a VALID guess, incriments turn, and returns count
CBullCowCount CBullCowGame::SubmitGuess(FString Guess)
{
		// incriment the turn number
		EssaiCourant++;
	
		// setup a return variable
		CBullCowCount BullCowCount;
	
		// loop through all letters in the guess
		int32 HiddenWordLength = Guess.length();
		for (int32 i = 0; i < HiddenWordLength; i++) {
			// compare letters against the hidden word
				for (int32 j = 0; j < HiddenWordLength; j++) {
							// if they match then
					if (Guess[i] == MotCache[j]) {
						if (i == j) { // if they're in the same place
							BullCowCount.Bulls++; // incriment bulls
						}
					else {
						BullCowCount.Cows++; // must be a cow
						
					}
					
				}
				
			}
			
		}

		if (BullCowCount.Bulls == getLongMotCache()) {
			gagne = true;
		}
		else {
			gagne = false;
		}
	return BullCowCount;
}

int32 CBullCowGame::getLongMotCache()const {
	return MotCache.length();
}

bool CBullCowGame::estIsogram(FString Mot) const
{
	if (Mot.length() <= 1) { return true; }

	TMap<char, bool>lettreMot;
	for (auto lettre : Mot) {
		lettre = tolower(lettre);
		if (lettreMot[lettre]) {
			return false;
		}
		else {
			lettreMot[lettre] = true;
		}
	}

	return true;
}

bool CBullCowGame::estLowerCase(FString Mot) const {
	if (Mot.length() <= 1) { return true; }

	TMap<char, bool>lettreMot;
	for (auto lettre : Mot) {
		if (islower(lettre) == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	return true;
}
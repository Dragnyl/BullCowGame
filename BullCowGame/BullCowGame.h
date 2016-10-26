#pragma once
#include <string>

using namespace std;

using FString = string;
using int32 = int;

// all values intialised to zero
struct CBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {

	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};

class CBullCowGame
{
private:

	int32 EssaiCourant = 0;
	int32 MaxEssai = 8;
	FString MotCache;
	EWordStatus status;
	bool gagne;

public:
	CBullCowGame();

	~CBullCowGame();
	//get
	int32 getEssaiCourant()const;
	int32 getMaxEssai()const;
	
	//set
	void setEssaiCourant(int32 nEssai);
	//void setMaxEssai(int32 nEssai);

	void Reset();

	bool Gagne()const;

	EWordStatus TestValideMot(FString Mot) const;

	CBullCowCount SubmitGuess(FString);

	int32 getLongMotCache() const;

	int32 getEWordStatus()const;

	bool estIsogram(FString Mot)const;

	bool estLowerCase(FString Mot) const;

};


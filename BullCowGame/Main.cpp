#include <iostream>
#include <string>
#include "BullCowGame.h"

using namespace std;

using FTEXT = string;
using int32 = int;

//Prototypes
void AfficheIntro(CBullCowGame);
FTEXT VotreMot(CBullCowGame);
void Jouer(CBullCowGame);
bool JouerEncore();

int32 main() {
	
	CBullCowGame Joueur;
	do {
		AfficheIntro(Joueur);
		Jouer(Joueur);
	}while(JouerEncore());

	system("pause");

	return 0;

}

void AfficheIntro(CBullCowGame joueur) {

	//Constante locale au main
	constexpr int32 WORLD_LENGTH = 8;
	

	cout << "Bienvenue dans le Bull & Cow Game !!!" << endl;
	cout << "Nombre de lettres du mot cache : " << joueur.getLongMotCache() << endl;
	cout << "Nombre de possibilites : " << joueur.getMaxEssai() << endl;
	cout << joueur.getLongMotCache();

	
}

FTEXT VotreMot(CBullCowGame joueur) {

	EWordStatus status = EWordStatus::Ok;
	do {
		int32 Essaicourant = joueur.getEssaiCourant();
		FTEXT mot = "";

		cout << "Essai courant : " << Essaicourant << endl;

		cout << "Saisir votre mot : " << endl;
		getline(cin, mot);

		status = joueur.TestValideMot(mot);

		switch (status) {
			case EWordStatus::Wrong_Length: cout << "Entrez un mot de max : " << joueur.getLongMotCache() << " lettres." << endl; break;
			case EWordStatus::Not_Isogram: cout << "Entrez un mot sans lettres repetees." << endl; break;
			case EWordStatus::Not_Lowercase: cout << "Entrez un mot en minuscule." << endl; break;
			default: return mot; break;
		}
	} while (status != EWordStatus::Ok);
}

void Jouer(CBullCowGame joueur) {

	int32 MaxEssai = joueur.getMaxEssai();

	while (!joueur.Gagne() && joueur.getEssaiCourant() <= MaxEssai) {

		FTEXT mot = VotreMot(joueur);
		EWordStatus status = joueur.TestValideMot(mot);

		cout << "Votre mot est : " << mot << endl;
		cout << endl;

		// submit valid guess to the game, and receive counts
		CBullCowCount BullCowCount = joueur.SubmitGuess(mot);
		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}
	if (joueur.Gagne()) {
		cout << "Bravo ! Vous avez gagne ! :)" << endl;
	}
	else {
		cout << "Vous avez perdu ! :(" << endl;
	}
}

bool JouerEncore()
{
	cout << "Voulez-vous rejouer ?" << endl;
	FTEXT Reponse = "";
	getline(cin, Reponse);
	return (Reponse[0] == 'o') || (Reponse[0] == 'O');
}

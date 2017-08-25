#include "BullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;	// FString instead of String (UE Coding Standard). FString when dealing with mutable strings.
using int32 = int;				// int32 instead of int (UE Coding Standard).

constexpr int32 MAX_TRIES = 8;
const FString HIDDEN_WORD = "planes";

BullCowGame::BullCowGame() {
	Reset();
}

void BullCowGame::Reset() {

	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
}

int32 BullCowGame::GetMaxTries() const {
	return MyMaxTries;
}

int32 BullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

int32 BullCowGame::GetHiddenWordLength() const {
	return MyHiddenWord.length();
}

bool BullCowGame::IsGameWon() const {
	return bGameIsWon;
}

EGuessStatus BullCowGame::CheckGuessValidity(FString guess) const {
	if (!IsIsogram(guess)) {
		return EGuessStatus::NOT_ISOGRAM;
	} else if (false) {
		return EGuessStatus::INCORRECT_CASE;
	} else if (guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::INCORRECT_LENGTH;
	} else {
		return EGuessStatus::OK;
	}
}

FBullCowCount BullCowGame::SubmitValidGuess(FString guess) {

	// increment the number of tries.
	MyCurrentTry++;

	// setup our return value;
	FBullCowCount BullCowCount;

	int32 wordLength = MyHiddenWord.length();

	for (int32 hiddenWordCharacter = 0; hiddenWordCharacter < wordLength; hiddenWordCharacter++) {
		
		for (int32 guessCharacter = 0; guessCharacter < wordLength; guessCharacter++) {
			
			if (guess[guessCharacter] == MyHiddenWord[hiddenWordCharacter]) {
				if (hiddenWordCharacter == guessCharacter) {
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == wordLength) {
		bGameIsWon = true;
	}

	return BullCowCount;
}

bool BullCowGame::IsIsogram(FString Guess) const {
	
	if (Guess.length() <= 1) return true;

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess) {
		Letter = tolower(Letter);

		if (LetterSeen[Letter]) {
			return false;
		} else {
			LetterSeen[Letter] = true;
			return true;
		}
	}

	return true;
}

#pragma once
#include <string>

using FString = std::string;	// FString instead of String (UE Coding Standard). FString when dealing with mutable strings.
using int32 = int;				// int32 instead of int (UE Coding Standard).

// structs begin with F (UE Coding Standard).
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows  = 0;
};

// enum begins with E (UE Coding Standard).
enum class EGuessStatus {
	INVALID_STATUS,
	OK,
	NOT_ISOGRAM,
	INCORRECT_LENGTH,
	INCORRECT_CASE
};

class BullCowGame {

public:
	BullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	EGuessStatus CheckGuessValidity(FString guess) const;
	bool IsGameWon() const;

	void Reset();

	// TODO: a method for counting bulls and cows, and increasing turn number.
	FBullCowCount SubmitValidGuess(FString guess);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString Guess) const;

};

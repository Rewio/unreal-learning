/* 
This is the console executable, that makes use of the BullCow Class.
This acts as the view in a MVC Pattern, and is responsible for all user interaction.
For game logic, see the FBullCowGame class.
 */

#include <iostream>
#include <string>
#include "BullCowGame.h"

using FText = std::string; // FText instead of String (UE Coding Standard). FText when dealing with input.
using int32 = int;

void PrintIntro();
FText GetGuess();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

BullCowGame BCGame;

int main() {

	// introduce the game.
	PrintIntro();

	do {
		std::cout << std::endl;

		// start playing the game.
		PlayGame();

	} while (AskToPlayAgain() == true);

	return 0;
}

void PrintIntro() {

	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
}

FText GetGuess() {

	FText Guess = "";
	std::cout << "Try " << BCGame.GetCurrentTry() << ": Take a guess: ";
	getline(std::cin, Guess);

	return Guess;
}

void PlayGame() {

	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game and receive counts of bulls and cows.
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows.
		std::cout << "Bulls = " << BullCowCount.Bulls << " - ";
		std::cout << "Cows = " << BullCowCount.Cows << "." << std::endl;
		std::cout << std::endl;
	}

	PrintGameSummary();
}

FText GetValidGuess() {

	EGuessStatus status = EGuessStatus::INVALID_STATUS;
	FText guess = "";

	do {
		int32 currentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << currentTry << ". Enter Your Guess: ";
		guess = "";
		getline(std::cin, guess);

		status = BCGame.CheckGuessValidity(guess);
		switch (status) {
			case EGuessStatus::OK:
				return guess;
			case EGuessStatus::NOT_ISOGRAM:
				std::cout << "Please enter a word without repeating letters." << std::endl;
				break;
			case EGuessStatus::INCORRECT_LENGTH:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
				break;
			case EGuessStatus::INCORRECT_CASE:
				std::cout << "Please enter a word with all lowercase letters." << std::endl;
				break;
			default:
				return guess;
		}
	} while (status != EGuessStatus::OK);
	return guess;
}

bool AskToPlayAgain() {
	std::cout << "Would you like to play again with the same word? (y/n)? ";

	FText Response;
	getline(std::cin, Response);

	return tolower(Response[0] == 'y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well done, you won!" << std::endl;
	} else {
		std::cout << "Better luck next time!" << std::endl;
	}
}

/*This acts as a console executable, that makes use of the FBullCowGame class.
This acts as the view in a MVC pattern, and is responsible of all
user interaction. For game logic see the FBullCowGame class.
*/
//importing extra files and classes only once
#pragma once
//including extra nessesary files and classes
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//creating substitutes for methods(Making the methods Unreal friendly)
using FText = std::string;
using int32 = int;

//creating prototype methods as outside a class
void PrintGameSummary();
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame;//make an instance of the game, which we re-use across plays

//the entry for our application
int main() {
	do {
		//introduce the game
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain() == true );
	
	std::cout << std::endl;
	return 0;//exit the application
}
//Main game method
void PlayGame() {
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while the game is NOT won
	//and there are still tries remaining
	while ( ! BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();		

		//submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ". \n\n";
	}
	PrintGameSummary();
	return;
}
// introduce the game function
void PrintIntro() {
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "||||^||||||^||||||||||||||^||||||^||||" << std::endl;
	std::cout << "|||||||||||||||||||||||||||||||||||||||" << std::endl;
	//introduce the rules of the game
	std::cout << "Rules:\n" << "-You must guess the isogram with a limited amount of tries\n" << "-You must input with all lowercase letters\n";
	std::cout << "-After each guess, the computer will output Bull and Cows:\n" << "	-Bulls: the right letter in the right place\n" << "	-Cows: the right letter in the wrong place\n";
	//Choose your Difficulty
	std::cout << "Choose your difficulty [D1/D2/D3/D4/D5]";
	FText Difficulty = "";
	std::getline(std::cin, Difficulty);
	BCGame.Reset(Difficulty);
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}
// summarize the game
void PrintGameSummary() {
	if (BCGame.isGameWon()) {
		std::cout << "WELL DONE, YOU HAVE GUESSED THE ISOGRAM - YOU WIN!\n";
	}
	else {
		std::cout << "BETTER LUCK NEXT TIME!\n";
	}
}

//loop continually until user gives valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() <<". Enter Your Guess: ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		//send error messages

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram(a word without repeating letters).\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase letter word.\n\n";
			break;
		default:
			//assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);//keep looping until we get valid input
	return Guess;
}
//ask the user if they wish to play again
bool AskToPlayAgain() {
	std::cout << "Do You Want to Play Again? [Y/N]";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


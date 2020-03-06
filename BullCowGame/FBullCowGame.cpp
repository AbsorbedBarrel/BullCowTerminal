/*This is the file that defines the methods of the FBullCowGame class
in the FBullCowGame header file.
*/
//importing extra files and classes only once
#pragma once
//including extra nessesary files and classes
#include "FBullCowGame.h"
#include <map>
//defining TMap method(making method Unreal friendly)
#define TMap std::map


FBullCowGame::FBullCowGame() {
} // default constructor
//resets the game
void FBullCowGame::Reset(FString Difficulty) 
{	
	MyCurrentTries = 1;
	bisGameWon = false;

	const FString HIDDEN_WORD = ChooseDifficulty(Difficulty);//this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	return;
}

//Checks Guess Validity
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (! IsIsogram(Guess)) {//if guess isn't an isogram,
		return EGuessStatus::Not_Isogram;
	}
	else if ( ! IsLowercase(Guess)) {//if guess isn't all lowercase, TODO write a function
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {//if guess length is wrong,
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

//Getter Methods
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTries; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bisGameWon; }
int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthtoMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 14}, {7, 18} };
	return WordLengthtoMaxTries[MyHiddenWord.length()];
}

//Chooses Difficulty Level
FString FBullCowGame::ChooseDifficulty(FString Difficulty) const
{
	FString ChoosenHiddenWord = "";
	if (Difficulty == "D1" || Difficulty == "d1") {
		ChoosenHiddenWord = "sea";
	}
	else if (Difficulty == "D2" || Difficulty == "d2") {
		ChoosenHiddenWord = "find";
	}
	else if (Difficulty == "D3" || Difficulty == "d3") {
		ChoosenHiddenWord = "slope";
	}
	else if (Difficulty == "D4" || Difficulty == "d4") {
		ChoosenHiddenWord = "planet";
	}
	else if (Difficulty == "D5" || Difficulty == "d5") {
		ChoosenHiddenWord = "stumped";
	}
	else {
		ChoosenHiddenWord = "sea";
	}
	return ChoosenHiddenWord;
}

//Submits valid Guess
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//submits a VALID guess, incriments turn, and returns count
	
	MyCurrentTries++;
	FBullCowCount BullCowCount;

	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length();//assuming the same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {
					//incriment bulls if they're in the right place
					BullCowCount.Bulls++;
				}
			//else
				else {
					BullCowCount.Cows++;
					//incriment cows if they're in the wrong place
				}
			}

		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bisGameWon = true;
		
	}
	else {
		bisGameWon = false;
	}
	return BullCowCount;
}

//Checks if the guess is an isogram
bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter word
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;//setup the map
	for (auto Letter : Word) { //for all letters of the guess
		Letter = tolower(Letter);//handle mixed cases
		if (LetterSeen[Letter]) {
			//if one letter appears more than once in the map,
			return false;// we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true;//add the letter to the map as seen
		}
		
	}
	return true;
}

//Checks if the guess is a lowercase letter word
bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if ( ! islower(Letter)) {
			return false;
		}
	}
}


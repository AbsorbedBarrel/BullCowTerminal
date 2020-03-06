/*This is the header file for the FBullCowGame.cpp file and Declares all functions and private variables.
This file creates the FBullCowCount structure and the EGuessStatus enumeration
*/
//importing string class only once
#pragma once
//including string class from C++ library
#include <string>

//creating substites for methods(making methods Unreal friendly)
using FString = std::string;
using int32 = int;

//the FBullCowCount Structure
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

//the EGuessStatus Enumeration
enum class EGuessStatus {
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Invalid_Status
};

//creates the FBullCowGame class
class FBullCowGame {
public:
	//default constuctor
	FBullCowGame();

	//all of the getter methods
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool isGameWon() const;
	FString ChooseDifficulty(FString) const;

	//other methods
	void Reset(FString);
	FBullCowCount SubmitValidGuess(FString);


					/*||^^^^----------------Please focus on the Methods above----------------^^^^||*/

private:
	//private variables
	int32 MyCurrentTries = 1;
	FString MyHiddenWord;
	bool bisGameWon = false;

	//helper methods
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};


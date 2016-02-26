#include "FBullCowgame.h"
#include <iostream>

FBullCowGame::FBullCowGame() { Reset(); }

int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "donkey";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess)  // loop through all the letters in Guess word
	{
		Letter = tolower(Letter); // lowercase each letter
		if (LetterSeen[Letter]) // if the letter is in map
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;   // add the letter to the map
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!tolower(Letter))
		{
			return false;
		}
	}
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// isn't an isogram
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if(!IsLowercase(Guess)) // isn't all lowercase
	{
		
		return EGuessStatus::Not_Lowercase;
	}
	else if(Guess.length() != GetHiddenWordLength()) // Guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// Recieves a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength(); // assuming same length as guess

	//loop through all letters in the guess in hidden words
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		//compare letters against the hidden word
		for (int32 GChar = 0; GChar < WordLength; GChar++)  
		{ 
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar) 
				{
					BullCowCount.Bulls++;
				}
				else 
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}

	return BullCowCount;
}

void FBullCowGame::PrintGameSummary() const
{
	if (IsGameWon()) {
		std::cout << "\nWELL DONE - YOU WIN";
	}
	else {
		std::cout << "\nBetter luck next time!";
	}
}

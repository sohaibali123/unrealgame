/* This is the console executible, that makes use of the BullCow Class 
this acts as the view in MVC pattern, and is responsible for all 
user interaction. For game logic see BullCow Class.
*/

#pragma once

#include "stdio.h"
#include "FBullCowGame.h"
#include <iostream>	
#include <string>

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void GetValidGuess(FText &Guess);
void PrintBack(const FText Guess);
bool AskToPlayAgain();

FBullCowGame BCGame;	//Instantiate a new game

int32 main()
{
	bool PlayAgain;
	
	do {
		PrintIntro();
		PlayGame();
		PlayAgain = AskToPlayAgain();
	} while (PlayAgain);

	return 0;
}

void PrintIntro() 
{
	// intro Game

	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n\n";
	std::cout << "        *                                                       *" << std::endl;
	std::cout << "       ***                                                     ***" << std::endl;
	std::cout << "       ****                                                   ****" << std::endl;
	std::cout << "       *   ******                                       ******   *" << std::endl;
	std::cout << "       *         ***************************************         *" << std::endl;
	std::cout << "        **            *       ______*______       *            **" << std::endl;
	std::cout << "          *****      *        ______*______        *      *****" << std::endl;
	std::cout << "               *******        ______*______        *******" << std::endl;
	std::cout << "            ***       ****          *         ****        ***" << std::endl;
	std::cout << "                ****** *oo*******  ***  *******oo* ******" << std::endl;
	std::cout << "                     *   *o********* *********o*   *" << std::endl;
	std::cout << "                      *   *                   *   *" << std::endl;
	std::cout << "                       *   *   _         _   *   *" << std::endl;
	std::cout << "                        *   *  -_       _-  *   *" << std::endl;
	std::cout << "                         *  *   -_     _-   *  *" << std::endl;
	std::cout << "                          * *     -___-     * *" << std::endl;
	std::cout << "                           *                 *" << std::endl;
	std::cout << "                          *********************" << std::endl;
	std::cout << "                          *      **   **      *" << std::endl;
	std::cout << "                            *    **   **    *" << std::endl;
	std::cout << "                              *  _-----_  *" << std::endl;
	std::cout << "                                *********" << std::endl << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram i'm thinking of?\n";
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";

	// loop asking for guesses while the games is not won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		GetValidGuess(Guess);

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		BCGame.CheckGuessValidity(Guess);
	}

	BCGame.PrintGameSummary();
}

//loop continually until the user gives a valid guess 
void GetValidGuess(FText &Guess)
{
	EGuessStatus Status = EGuessStatus::Invalid;

	do
	{
		//Get Guess
		std::cout << "\nTry " << BCGame.GetCurrentTry() << " of ";
		std::cout << BCGame.GetMaxTries() << ". Enter your guess : ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		default:
			break;
		}

	} while (Status != EGuessStatus::OK);
}

void PrintBack(const FText Guess) 
{
	std::cout << "Your guess was : " << Guess << "\n";
}

bool AskToPlayAgain()
{
	FText response = "";

	std::cout << "\nDo you want to play again with the same hidden word (y/n)? ";
	getline(std::cin, response);

	return response[0] == 'y' || response[0] == 'Y';
}

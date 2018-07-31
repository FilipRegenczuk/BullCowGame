/* This is the console executable, that makes use of the BullBow class.
This acts as the view in a MVC pattern, and is responsible for all user 
interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void print_intro();
void play_game();
FText get_valid_guess();
bool ask_to_play_again();
void print_game_summary();


FBullCowGame BCGame; // instantiate a new game



int main()
{
	bool continue_game;
	do
	{
		print_intro();
		play_game();
		continue_game = ask_to_play_again();

	} while (continue_game);

	return 0;
}




void print_intro()
{
	std::cout << "  ___                        ___                                         " << std::endl;
	std::cout << "    \\\\                      //                                         " << std::endl;
	std::cout << "     \\\\                    //                                          " << std::endl;
	std::cout << "      \\\\______//////______//               \\``\\__''''''__/``/        " << std::endl;
	std::cout << "       \\\_____| >  < |_____/                 \\___/ <  > \\___/         " << std::endl;
	std::cout << "             |      |            BULLS         /        \\               " << std::endl;
	std::cout << "             {  **  }              &           \\   oo   /               " << std::endl;
	std::cout << "              \\____/             COWS           \\______/               " << "\n\n\n";

	std::cout << "Can you guess the " << BCGame.get_hidden_word_length() << " letter isogram I'm thinking of?\n\n";
	return;
}




void play_game()
{
	BCGame.reset();
	int32 max_tries = BCGame.get_max_tries();
	
	
	/* loop asking for guesses while the game
	   is NOT won and there are still tries remaining */
	while (!BCGame.is_game_won() && BCGame.get_current_try() < max_tries)
	{
		FText Guess = get_valid_guess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.submit_valid_guess(Guess);

		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	print_game_summary();

	return;
}



// loop continually until the user gives a valid guess
FText get_valid_guess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		// get a guess from the player
		int32 current_try = BCGame.get_current_try();
		std::cout << "Try " << current_try << " of " << BCGame.get_max_tries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give a feedback
		Status = BCGame.check_guess_validity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.get_hidden_word_length() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
		

	} while (Status != EGuessStatus::OK);	// keep looping until we get no errors
	return Guess;
}



bool ask_to_play_again()
{
	FText Response = "";

	std::cout << "Do you want to play again with the same hidden word (y/n)?\n";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	return (Response[0] == 'y') || (Response[0] == 'Y');
}



void print_game_summary()
{
	if (BCGame.is_game_won())
		std::cout << "YOU WIN. CONGRATULATION.\n";
	else
		std::cout << "YOU LOST. TRY AGAIN.\n";

	return;
}
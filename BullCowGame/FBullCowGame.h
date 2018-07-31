/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on mastermind 
*/

#pragma once

#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};



class FBullCowGame
{
public:
	FBullCowGame();

	int32 get_max_tries() const;
	int32 get_current_try() const;
	int32 get_hidden_word_length() const;
	bool is_game_won() const;
	EGuessStatus check_guess_validity(FString) const;

	void reset();
	FBullCowCount submit_valid_guess(FString); 


private:
	int32 my_current_try;
	FString my_hidden_word;
	bool bgame_is_won;

	bool is_isogram(FString) const;
	bool is_lower_case(FString) const;
};
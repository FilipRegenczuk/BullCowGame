#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map	// to make syntax Unreal friendly

using FString = std::string;
using int32 = int;


FBullCowGame::FBullCowGame() { reset(); }	// default constructor

int32 FBullCowGame::get_current_try() const { return my_current_try; }
int32 FBullCowGame::get_hidden_word_length() const { return my_hidden_word.length(); }
bool FBullCowGame::is_game_won()  const { return bgame_is_won; }


int32 FBullCowGame::get_max_tries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,8}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[my_hidden_word.length()];
}



void FBullCowGame::reset()
{ 
	const FString HIDDEN_WORD = "hotdog";	// this must be an isogram
	my_hidden_word = HIDDEN_WORD;

	my_current_try = 1;
	bgame_is_won = false;
	return;
}



EGuessStatus FBullCowGame::check_guess_validity(FString Guess) const
{
	if (!is_isogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!is_lower_case(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != get_hidden_word_length())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}




// reveives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::submit_valid_guess(FString Guess)
{
	my_current_try++;
	FBullCowCount BullCowCount;
	int32 word_length = my_hidden_word.length();	// assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < word_length; MHWChar++)
	{
		// compare letters against the hidden guess
		for (int32 GChar = 0; GChar < word_length; GChar++)
		{
			if (Guess[GChar] == my_hidden_word[MHWChar])
			{
				if (MHWChar == GChar)
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}

	if (BullCowCount.Bulls == word_length)
		bgame_is_won = true;
	else
		bgame_is_won = false;

	return BullCowCount;
}


// check the word is an isogram
bool FBullCowGame::is_isogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; };

	TMap<char, bool> LetterSeen; 	// setup our map
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);	// handle mixed case
		if (LetterSeen[Letter])		// if the letter is in the map
			return false;	// no isogram
		else
			LetterSeen[Letter] = true;	// add the letter to the map as seen
	}

	return true;
}

bool FBullCowGame::is_lower_case(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}


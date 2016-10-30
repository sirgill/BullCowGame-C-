//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Surinder Singh Gill on 10/28/16.
//  Copyright © 2016 Surinder Singh Gill. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {Reset();}


int32 FBullCowGame::GetCurrentTry() const {return MyCurrentTry;}

int32 FBullCowGame::GetHiddenWordLength() const{return MyHiddenWord.length();}

bool FBullCowGame::IsGameWon() const {return bGameIsWon;}


int32 FBullCowGame::GetMaxTries() const {
    
    TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
    return WordLengthToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset(){
    
    const FString HIDDEN_WORD= "plane";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;

}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    if (!IsIsogram(Guess))//if the guess isnt an isogram
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLoweCase(Guess))//if the guess isnt all lowercase
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength())//if length is wrong
    {
        return EGuessStatus::Wrong_Length;
    }
    else {
        return EGuessStatus::OK;
    }
}
//receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
    
    
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    int32 WordLength = MyHiddenWord.length();  //assuming same length as Guess
    
    for(int32 MHWChar = 0; MHWChar<WordLength; MHWChar++) {
        //compare letters against guess
        for (int32 GChar =0; GChar< WordLength; GChar++) {
        //if they match then
            if (Guess[MHWChar] == MyHiddenWord[MHWChar]) {
        
                if (MHWChar==GChar) {
                    BullCowCount.Bulls++; //increment Bulls
                }
                else {
                    BullCowCount.Cows++; //increment Cows
                }
                
            }
        }
    }
    if (BullCowCount.Bulls == WordLength) {
        bGameIsWon = true;
    } else {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    
    //treat 0 and 1 letter words as isograms
    if(Word.length() <= 1) {
        return true;
    }
    TMap<char,bool> LetterSeen; //setup our map
    for(auto Letter : Word) { // for all letters of the word
        Letter = tolower(Letter); // handle mixed cases
        if(LetterSeen[Letter]) {
            return false;
        } else {
            LetterSeen[Letter] = true;
        }
        
    
    }
    return true;
}
bool FBullCowGame::IsLoweCase(FString Word) const {
    for (auto Letter : Word){
        if(!islower(Letter)) {
            return false;
        }
    }
        return false;
}


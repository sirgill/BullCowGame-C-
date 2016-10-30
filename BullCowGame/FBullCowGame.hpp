//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Surinder Singh Gill on 10/28/16.
//  Copyright © 2016 Surinder Singh Gill. All rights reserved.
//

#pragma once
#define FBullCowGame_hpp

#include <string>



using FString = std::string;
using int32 = int;

struct FBullCowCount {
    
    int32 Bulls=0;
    int32 Cows = 0;
};


enum class EGuessStatus {
    Invaild,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    FBullCowGame(); // constructor
    

    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    FBullCowCount SubmitGuess(FString);

    
private:
    
    //see constructor for init
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsIsogram(FString) const;
    bool IsLoweCase(FString) const;
   
};

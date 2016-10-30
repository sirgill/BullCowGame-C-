/* 
 This is the console executable, that makes use of the BullCow class
 This acts as the view in MVC pattern, and is responsible for all user interaction. 
 For game logic see FBullCowGame Class
 Created by Surinder Singh Gill on 10/27/16.
 Copyright © 2016 Surinder Singh Gill. All rights reserved.
 */

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate new game

//the entry point of the game
int main() {
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while(bPlayAgain);
    
    return 0; //exit the application
}


void PrintIntro() {
    //Introduce the game
    
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the "<< BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    return;
}

void PlayGame() {
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    //LOOP asking for guesses while the game
    //is Not won and there are tries still remaining
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText Guess = GetValidGuess(); //ToDo make loop to check valid
        
        //submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
        //Print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
       
    
    }
    
    PrintGameSummary();
    return;
    
}
//loop continously until c
FText GetValidGuess() {
    FText Guess = "";
    EGuessStatus Status = EGuessStatus::Invaild;
    do {
        int32 CurrentTry = BCGame.GetCurrentTry();
        //get a guess from the user
        std::cout << "Try " << CurrentTry << "of" << BCGame.GetMaxTries();
        std::cout << " .Enter your guess: ";
        std::getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout<< "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters. \n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters.\n\n";
                break;
            default:
                //assuming guess is valid 
                break;
        }
        
    }while (Status != EGuessStatus::OK); { //keep looping till we get no errors
        return Guess;
    }
    
}

bool AskToPlayAgain() {
    std::cout << "Do you want to play agian with the same hidden word?(y/n) ";
    FText Response = "";
    std::getline(std::cin, Response);
    
    return (Response[0] == 'y') || (Response[0] == 'Y');
}
void PrintGameSummary(){
    if (BCGame.IsGameWon()) {
        std::cout << "Well Done - You Win!!";
    } else {
        std::cout << "Better luck next time";
    }
};

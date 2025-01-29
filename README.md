#include <iostream>
#include <string>
#include <cstdlib> // for srand
#include <ctime>   // for time(0)
using namespace std;

const int attmepts = 7;
const int WordCount = 26; // word library
const int players = 5;


const string words[WordCount] = {"unitedstates", "china", "unitedkingdom", "france", "india", "germany", "japan", "russia", "brazil", "italy", "australia", "canada", "southkorea", "mexico", "saudi arabia", "egypt", "spain", "turkey", "argentina", "switzerland", "netherlands", "poland", "sweden", "southafrica", "greece", "newzealand"};

// random word to be chosen
string pickRandomWord() {
    return words[rand() % WordCount];
}

// displaying current state of the word
void displayWord(const string& word, const bool guessed[]) {
    for (int i = 0; i < word.length(); i++) {
        if (guessed[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

//checking if all letters in the woord have been guessed
bool isWordGuessed(const bool guessed[], int length) {
    for (int i = 0; i < length; i++) {
        if (!guessed[i]) return false;
    }
    return true;
}

// the mainly fucntion of the game that handles the word guessing logic
int Hangman() {
    string word = pickRandomWord();
    int wordLength = word.length();
    bool guessed[wordLength] = {false};
    int attemptsLeft = attmepts;
    char guess;
    bool correctGuess;

    cout << "\nGuess the word! You have " << attmepts << " attempts." << endl;
    // game loop until 0 attemptes
    while (attemptsLeft > 0) {
        displayWord(word, guessed);
        cout << "\nEnter a letter: ";
        cin >> guess;

        correctGuess = false;

// check if the guessed letter is in the owrd
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guess && !guessed[i]) {
                guessed[i] = true;
                correctGuess = true;
            }
        }
    // gives feedback and results based on the guess
        if (correctGuess) {
            cout << "\nGood guess!" << endl;
        } else {
            --attemptsLeft;
            cout << "\nWrong guess! Attempts left: " << attemptsLeft << endl;
        }

    //check the whole word is guessed or not
        if (isWordGuessed(guessed, wordLength)) {
            cout << "\nCongratulations! You guessed the word: " << word << endl;
            return 1; // Player wins
        }
    }

    // if out of attempts u lose
    cout << "\nYou lost! The word was: " << word << endl;
    return 0;
}
    // main function of the game
int main() {
    srand(time(0));
    int numPlayers;
    int scores[players] = {0};
    string playerNames[players];

    cout << "Welcome to the hangman game" << endl;
    cout << "Enter the number of players (max " << players << "): ";
    cin >> numPlayers;

    // checking if the number of players are suitable
    if (numPlayers < 1 || numPlayers > players) {
        cout << "Invalid number of players. Exiting..." << endl;
        return 1;
    }


    for (int i = 0; i < numPlayers; i++) {
        cout << "Enter name for player " << i + 1 << ": ";
        cin >> playerNames[i];
    }


    for (int i = 0; i < numPlayers; i++) {
        cout << "\n--- " << playerNames[i] << "'s Turn ---" << endl;
        scores[i] = Hangman();
    }


    cout << "\n--- Final Scores ---" << endl;
    for (int i = 0; i < numPlayers; i++) {
        cout << playerNames[i] << ": " << scores[i] << " points" << endl;
    }

    return 0;
}

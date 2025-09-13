#include <iostream>
#include <string>
#include <cstdlib> // for srand
#include <ctime>   // for time(0)
#include <vector>
#include <cctype>  // for tolower
using namespace std;

const int attempts = 7;
const int WordCount = 26; // word library
const int players = 5;

const string words[WordCount] = {
    "unitedstates", "china", "unitedkingdom", "france", "india", "germany",
    "japan", "russia", "brazil", "italy", "australia", "canada",
    "southkorea", "mexico", "saudi arabia", "egypt", "spain", "turkey",
    "argentina", "switzerland", "netherlands", "poland", "sweden",
    "southafrica", "greece", "newzealand"
};

// random word to be chosen
string pickRandomWord() {
    return words[rand() % WordCount];
}

// displaying current state of the word
void displayWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.length(); i++) {
        if (word[i] == ' ') {
            cout << "  "; // two spaces for visual gap
        }
        else if (guessed[i]) {
            cout << word[i] << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// checking if all letters in the word have been guessed
bool isWordGuessed(const vector<bool>& guessed) {
    for (bool b : guessed) {
        if (!b) return false;
    }
    return true;
}

// the main function of the game that handles the word guessing logic
int Hangman() {
    string word = pickRandomWord();
    int wordLength = static_cast<int>(word.length());
    vector<bool> guessed(wordLength, false);

    // mark spaces as already "guessed"
    for (int i = 0; i < wordLength; ++i) {
        if (word[i] == ' ') guessed[i] = true;
    }

    int attemptsLeft = attempts;
    char guess;
    bool correctGuess;

    cout << "\nGuess the word! You have " << attempts << " attempts." << endl;

    // game loop until 0 attempts
    while (attemptsLeft > 0) {
        displayWord(word, guessed);
        cout << "\nEnter a letter: ";
        cin >> guess;

        // normalize to lowercase
        guess = static_cast<char>(tolower(static_cast<unsigned char>(guess)));

        // validate input: must be alphabetic
        if (!isalpha(static_cast<unsigned char>(guess))) {
            cout << "Please enter a valid letter." << endl;
            continue;
        }

        correctGuess = false;

        // check if the guessed letter is in the word
        for (int i = 0; i < wordLength; i++) {
            if (tolower(static_cast<unsigned char>(word[i])) == guess && !guessed[i]) {
                guessed[i] = true;
                correctGuess = true;
            }
        }

        // gives feedback and results based on the guess
        if (correctGuess) {
            cout << "\nGood guess!" << endl;
        }
        else {
            --attemptsLeft;
            cout << "\nWrong guess! Attempts left: " << attemptsLeft << endl;
        }

        // check the whole word is guessed or not
        if (isWordGuessed(guessed)) {
            cout << "\nCongratulations! You guessed the word: " << word << endl;
            return 1; // Player wins
        }
    }

    // if out of attempts you lose
    cout << "\nYou lost! The word was: " << word << endl;
    return 0;
}

// main function of the game
int main() {
    srand(static_cast<unsigned int>(time(0)));
    int numPlayers;
    int scores[players] = { 0 };
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
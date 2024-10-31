#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int numWords = 100;
const int numChances = 12;

struct WORDS {
    string data;
};

WORDS words[numWords];
WORDS dup[numWords];
int wordCount = 0;

char toLowerCase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

void insertInPlace(WORDS words[], int wordCount) {
    for (int i = 1; i < wordCount; i++) {
        WORDS newword = words[i];
        int j = i - 1;
        while (j >= 0 && words[j].data > newword.data) {
            words[j + 1] = words[j];
            j--;
        }
        words[j + 1] = newword;
    }
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void isDuplicate(WORDS words[], WORDS dup[], int wordCount) {
    cout << "REPEATED WORDS" << endl;
    cout << "================================================================" << endl;

    int x = 0;
    int dupCount = 0; // Counter for the number of duplicates found
    
    for (int i = 0; i < wordCount; i++) {
        bool isDuplicate = false; // Flag to check if a word is a duplicate
        
        // Check if the word has already been marked as a duplicate
        for (int j = 0; j < dupCount; j++) {
            if (words[i].data == dup[j].data) {
                isDuplicate = true;
                break;
            }
        }
        
        // Check for duplicates among the remaining words
        if (!isDuplicate) {
            for (int j = i + 1; j < wordCount; j++) {
                if (words[i].data == words[j].data) {
                    isDuplicate = true;
                    dup[dupCount++].data = words[i].data; // Add the duplicate word to the dup array
                    break;
                }
            }
        }
        
   
        // Print the duplicate word if found

		if (isDuplicate) {
		    cout << words[i].data << " ";
		    x++;
		}
		if ((x%4) == 0 && isDuplicate)
			cout << endl;
	
}
cout << endl << endl;
cout << "Note: Repeated words have a higher chance of being choosen by the system. ";
}

void printWords (WORDS words[], int wordCount){
	cout << "HERE IS A LIST OF POSSIBLE WORDS" << endl;
	cout << "================================================================" << endl;
	cout << endl;
	cout << "DO NOT WRITE THEM DOWN (-_-)";
	for (int w =0; w<wordCount; w++){
		if (w % 4 == 0){
			cout << endl;
		}
		cout << words[w].data << " ";
	}
		
}

void playHangman(string word) {
    int guesses = 0;
    string guessedLetters(word.length(), '*');

//	cout << "===============================================================" << endl;
    while (guesses < numChances) {
   	cout << "===============================================================" << endl;

    	cout << "You have " << numChances - guesses << " guesses remaining." << endl;
        cout << "Guess the word: " << guessedLetters << endl;
        char letter;
        cout << "Enter a letter: ";
        cin >> letter;
        
        letter = toLowerCase(letter);

        if (!isLetter(letter)) {
            cout << "Invalid input. Please enter a letter." << endl;
        }

        bool correctGuess = false;
        for (int i = 0; i < word.length(); i++) {
            if (word[i] == letter) {
                guessedLetters[i] = letter;
                correctGuess = true;
            }
        }
		
		system ("cls");
		
        if (correctGuess) {
            cout << "Correct guess!" << endl;
            if (guessedLetters == word) {
                cout << "Congratulations! You guessed the word: " << word << endl;
                cout << "===============================================================" << endl;
                return;
            }
        } else {
            cout << "Incorrect guess." << endl;
            guesses++;
           // cout << "You have " << numChances - guesses << " guesses remaining." << endl;
        }
    }

    cout << "You exceeded the maximum number of guesses. The word was: " << word << endl;
    cout << "===============================================================" << endl;
}





//void printDup (WORDS dup[], int wordCount){
//	for (int x=0; x<wordCount; x++){
//		cout << dup[x].data;
//	}
//}


 int main() {
	
    ifstream infile;
    infile.open("words.txt");

    if (!infile) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    int j = 0;
    WORDS w;
    infile >> w.data;
    while (w.data != "ENDDATA") {
        words[j].data = w.data;
        wordCount++;
        j++;
        infile >> w.data;
    }

    for (int i = 0; i < wordCount; i++) {
        for (char& c : words[i].data) {
            c = toLowerCase(c);
        }
    }

    insertInPlace(words, wordCount);

//printWords (words, wordCount);
//cout << endl;
//isDuplicate(words, dup, wordCount);
//cout << endl;

int randomIndex;

cout << "================================================================" << endl;
cout << "WELCOME TO THE HANGMAN GAME!!" << "    			ver:1.1.3" << endl;
cout << "================================================================" << endl <<endl;
cout << "Objective: Correctly guess all the letters to win. (^-^)" << endl << endl;

system ("pause");
system("cls");
	printWords (words, wordCount);
		cout << endl << endl;
	isDuplicate(words, dup, wordCount);
		cout << endl << endl;
system ("pause");
system("cls");
cout << "You aren't going to get me hanged right? lol ........ right? (o_o)" <<endl;
system ("pause");
system("cls");

    for (int i = 0; i < wordCount; i++) {
    	srand(time(0));
    	randomIndex = rand() % wordCount;
        playHangman(words[randomIndex].data);
        char choice;
        cout << "Do you want to continue playing? (y/n): ";
        cin >> choice;
        if (choice == 'n' || choice == 'N') {
        	system ("cls");
        	cout << "THANKS FOR PLAYING!! ";
            break;
        }
        system ("cls");
    }

    return 0;
}

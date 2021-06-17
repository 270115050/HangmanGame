//Programmer:       Jay Anino
//Student ID:       270115050
//School:           Yoobee College
//Due Date:         17/05/2021
//Reference:	    CS 103 Lab 1
//Description:	    This program is a Hangman game were the player needs to guessed the hidden words.
//Guarantee:	    Program works to full specifications

#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

const int ARRSIZE = 22;

bool play(char*, string[][ARRSIZE], int, int, int);
bool checkCharMatch(char[], char, string[][ARRSIZE], int, int);
bool printGuessedLetters(char[], string[][ARRSIZE], int, int);
void printTitleScreen(bool);
void line(int);
void drawHangman();
void walk_man();
void invert_hangman();
void printInsultMessage(int);
void printCheerMessage(int);
void printCongratzMessage(int);
void printHearts(int);

int main()
{
    string guessWord[][ARRSIZE] = { {"Boku no Hero Academia", "Horimiya is Shit", "Attack on Titan", "Demon Slayer", "Ace of diamond", "Jujutsu Kaisen",
                           "Bokura wa Minna Kawai sou", "Anohana", "Grand Blue", "Daily lives of highschool boys", "Tokyo Revengers", "Haikyuu", "Barakamon",
                           "Princess Mononoke", "Sprited Away", "Howls moving castle", "Log Horizon", "Your Name", "Weathering with you", "Himouto Umaru chan", "Slam Dunk", "Grave of the Fireflies"},
                            {"Anime series about superheroes.", "A romance anime about two differentpeople who meet and develop a friendship.", "A dark fantasy anime set in a world where humanity\n\t\t\tlives inside cities surrounded by walls.",
                            "An action anime about a boy trying to find\n\t\t\ta cure for her little sister.", "A sports anime about a boy who wants to become the Ace of the team.", "A action anime about sorcerers and curses.", "A romcom anime about a boy who ends up living in a\n\t\t\tboarding house due to his parents working overseas.",
                            "A anime about a tragic tale of five teenagers", "A anime comedy that follows a college student with his eccentric\n\t\t\tnew friends as he strives to realize his ideal college dream.","Anime comedy that follows 3 highschool boys and their various interactions with\n\t\t\tother students of and around their school and their coming of age endeavors.",
                            "A time travel mystery anime about a man\n\t\t\twho is trying to save his ex-girlfriend.", "A sports anime that follows a boy determined to become a\n\t\t\tgreat player despite his small stature.", "An anime about a 23-year-old calligrapher prone to anger\n\t\t\tand misfortune, and his friendship with the villagers\n\t\t\twho continually screw him over through a myriad of hilarious accidents.",
                            "A Ghibli film about a struggle between the gods of a forest\n\t\t\tand the humans who consume its resources.", "A Ghibli film about a 10-year-old girl who while\n\t\t\tmoving to a new neighbourhood, enters the world of Kami.", "A Ghibli film, A love story between an 18-year-old girl,\n\t\t\tcursed by a witch into an old woman's body, and a magician.",
                            "A isekai anime where 30,000 japanese players are trapped\n\t\t\tin a fantasy online game world.","An anime movie about a high school boy in Tokyo and a high school girl\n\t\t\tin the Japanese countryside who suddenly and inexplicably begin to swap bodies.",
                            "A anime fantasy movie about a teenage boy\n\t\t\twho leaves home for Tokyo and meets a girl who was\n\t\t\tthe power to summon sunshine with a prayer.","A anime series about a cute story that follows the daily adventures of\n\t\t\ta highschool girl and her older brother, as they take care of—and put\n\t\t\tup with each other the best they can.",
                            "A sports anime about a freshman who joins the\n\t\t\tbasketball team because of the girl he has a crush on.","A Ghibli film that tells the story of two\n\t\t\tsiblings and their desperate struggle to survive\n\t\t\tduring the final months of the Second World War."
                            } };
    int numGuess = 0, randWord = 18, wordSize, choice, rndScriptLine, prevScriptLine = 0;
    char guessedLetters[100];
    bool isWordComplete, answer, isTrue;

start:
    srand(time(0));
    numGuess = 0;
    randWord = rand() % ARRSIZE;// picks a random anime title in the list
    wordSize = guessWord[0][randWord].length();

    memset(guessedLetters, 0, sizeof(guessedLetters)); //clears the array(If player wants to play again, this makes sure that the guessed letters are deleted)
    printTitleScreen(false);
    system("pause"); // wait for input
    system("cls");   // clear the screen
    printTitleScreen(true);
    cin >> choice;
    system("cls");
    drawHangman();

    do {
        if (!choice)
            cout << "Bollok";
        if (choice == 2)// this will show the hidden words if user press 2
            cout << "\n\t\t\tCheat Mode\n\t\t\tThe hidden words are: " << guessWord[0][randWord] << "\n\n";
        else if (choice != 1 && choice != 2)//exit program
            return 0;

        cout << "\t\t\tHint: " << guessWord[1][randWord] << "\n\n";

        printHearts(numGuess);
        answer = play(guessedLetters, guessWord, wordSize, randWord, numGuess);// returns a boolean to check if guess is right
        isWordComplete = printGuessedLetters(guessedLetters, guessWord, wordSize, randWord);// returns a boolean to check if user guessed all words

        do { // loops until previous message script is not the same
            rndScriptLine = rand() % 10;// used to get random message to be printed
            isTrue = true;
            if (prevScriptLine == rndScriptLine) {
                rndScriptLine = rand() % 10;
                isTrue = false;
            }
        } while (!isTrue);
        prevScriptLine = rndScriptLine;

        if (isWordComplete) { // checks if the hidden words are compeleted
            system("cls");
            walk_man();
            cout << "\n\n\t\t\tYou guessed it: " << guessWord[0][randWord] << "\n\n\t\t\t";
            printCongratzMessage(rndScriptLine);
            break;
        }
        else if (answer) { // checks if user guessed right
            cout << "\n\n\t\t\t";
            printCheerMessage(rndScriptLine);
        }
        else if (!answer) { // check if user guessed wrong
            numGuess++;
            if (numGuess == 3) { //if no more lives print gameover              
                system("cls");
                invert_hangman();
                cout << "\n\n\t\t\tThe hidden words are: " << guessWord[0][randWord] << "\n\n\t\t\tGAME OVER!\n\n\t\t\t";
                printInsultMessage(rndScriptLine);
                break;
            }
            else { //print message to user if guessed wrong
                cout << "\n\n\t\t\t";
                printInsultMessage(rndScriptLine);
            }
        }
        cout << "\n\t\t\t";
        Sleep(800);
        system("cls");
        drawHangman();
    } while (true);

    cout << "\t\t\t";
    system("pause");
    system("cls");
    goto start;
}
// This function prints the hearts which indicate the lives of the user(3 lives)
void printHearts(int numGuess) {
    cout << "\t\t\tPlayer Live(s): ";
    for (int i = 0; i < 3 - numGuess; i++)
        cout << char(3) << " ";
    cout << "\n\n";
}
// This function returns a boolean that checks if user guessed a letter
bool play(char* c, string guessAnswer[][ARRSIZE], int max, int rndWord, int numGuess) {
    char checkChar;
    bool isLetterValid, correctGuess;

    do {
        correctGuess = false;
        isLetterValid = false;

        printGuessedLetters(c, guessAnswer, max, rndWord);

        cout << "\n\t\t\tEnter a letter: ";
        cin >> checkChar;

        for (int i = 0; i < max; i++) { // This loop validates the user input
            if (!isalpha(checkChar)) { // if input is not alphabet
                cout << "\n\t\t\tMy God I said enter a letter, Try again!!..\n\n";
                break;
            }
            else if (tolower(checkChar) == tolower(c[i])) {//if it matches any previous guessed letters
                cout << "\n\t\t\Hey stupid you already picked this letter, Try again...\n\n";
                isLetterValid = false;
                break;
            }
            else { //if it doesn't match any previous guessed letters
                isLetterValid = true;
            }
        }
        if (!isLetterValid)
            system("pause");

        system("cls");
        drawHangman();
        cout << "\t\t\tHint: " << guessAnswer[1][rndWord] << "\n\n";
        printHearts(numGuess);
    } while (!isLetterValid);

    correctGuess = checkCharMatch(c, checkChar, guessAnswer, max, rndWord); // calls function to check if input matches hidden words
    return correctGuess;
}
// This function checks if the user input matches the hidden words and returns a boolean
bool checkCharMatch(char let[], char checkLet, string word[][ARRSIZE], int max, int rWord) {
    bool isTrue = false;

    for (int i = 0; i < max; i++) {
        if (tolower(word[0][rWord][i]) == tolower(checkLet)) {
            let[i] = word[0][rWord][i];
            isTrue = true;
        }
    }
    return isTrue;
}
// This function prints all Guessed letters to the user
bool printGuessedLetters(char let[], string gAnwswer[][ARRSIZE], int max, int rndWord) {
    bool isComplete = true;

    cout << "\t\t\t";
    for (int i = 0; i < max; i++) {
        if (let[i] == gAnwswer[0][rndWord][i])// checks if guessed letters matches the hidden words
            cout << let[i] << " ";
        else if (gAnwswer[0][rndWord][i] == ' ')// check if index is space
            cout << " ";
        else {
            cout << "_ ";
            isComplete = false; // this checks if user has not guess all of the letters
        }
    }
    return isComplete;
}
// This function prints dashes
void line(int dash) {
    cout << "\t\t\t\t";
    for (int i = 0; i < dash; i++) {
        cout << "-";
    }
    cout << "\n\n";
}
// This function prints a  message to user if they guessed wrong
void printInsultMessage(int rndScriptLine) {
    string msg[] = { "Are you stupid or something?!", "You've read the rules right?", "This is it I'm going to die...", "Ohh my its my lucky day...... just kill me", "Did your mom drop you when you were still a baby?!..",
    "Why do I always get the idiots?!", "Come on are you even trying?!", "(Facepalm) I hate my life", "Are you high right now?", "Im going to die and I haven't finished watching haikyuu sob sob.." };
    for (int i = 0; i < msg[rndScriptLine].length(); i++) {
        cout << msg[rndScriptLine][i];
        Sleep(20);
    }
    cout << endl << endl;;
}
// This function prints a message to user if they guessed right
void printCheerMessage(int rndScriptLine) {
    string msg[] = { "OHH YEAH!!!!!", "Not bad... not bad at all!", "You the man or girl.......... I dont really care.", "Lets get the W baby!!!", "Albert Einstein is in the house!!!!!!", "Sweeeet!", "Good job!", "Nice one!!!",
    "Maaah MAN!", "What a legend!" };
    for (int i = 0; i < msg[rndScriptLine].length(); i++) {
        cout << msg[rndScriptLine][i];
        Sleep(20);
    }
    cout << endl << endl;;
}
// This function prints a congratz message to user if they guessed all the hidden words
void printCongratzMessage(int rndScriptLine) {
    string msg[] = { "Ohh Yeah DRINKS ON ME!", "YOU THE GOAT!", "IM FREEEEEEEEEEEE!!!!!!", "Time to watch ANIME!", "ARIGATO GOZAIMASU!!", "MVP of the year!", "Good job champ!", "I guess you are not that stupid",
    "Im going to send you 2 sack of rice", "Party time boiizz!" };
    for (int i = 0; i < msg[rndScriptLine].length(); i++) {
        cout << msg[rndScriptLine][i];
        Sleep(20);
    }
    cout << endl << endl;;
}
// This function prints the title screen
void printTitleScreen(bool showChoice) {
    if (!showChoice) {
        cout << "\n\n\n\t\t\t|================================================================================|" << endl
            << "\t\t\t|                                                                                |" << endl
            << "\t\t\t|    |      |  |======|  |==    |  |=======  |==      ==|  |======|  |==    |    |" << endl
            << "\t\t\t|    |      |  |      |  |  =   |  |         |  =    =  |  |      |  |  =   |    |" << endl
            << "\t\t\t|    |======|  |======|  |   =  |  |  ====|  |   =  =   |  |======|  |   =  |    |" << endl
            << "\t\t\t|    |      |  |      |  |    = |  |      |  |    ==    |  |      |  |    = |    |" << endl
            << "\t\t\t|    |      |  |      |  |     =|  |======|  |          |  |      |  |     =|    |" << endl
            << "\t\t\t|                                                                                |" << endl
            << "\t\t\t|================================================================================|" << endl
            << "\n\t\t\t\tWelcome to play hangman. This game is to check your spelling skill" << endl;
        line(66);
        cout << "\t\t\t==========Rules========== \n\t\t\t1. Guess the hidden words to win the game.\n\t\t\t2. You have 3 lives every wrong guess you will lose 1 heart. \n\t\t\tHave fun :D\n\t\t\t";
    }
    else {
        cout << "\n\n\n\t\t\t|================================================================================|" << endl
            << "\t\t\t|                                                                                |" << endl
            << "\t\t\t|    |      |  |======|  |==    |  |=======  |==      ==|  |======|  |==    |    |" << endl
            << "\t\t\t|    |      |  |      |  |  =   |  |         |  =    =  |  |      |  |  =   |    |" << endl
            << "\t\t\t|    |======|  |======|  |   =  |  |  ====|  |   =  =   |  |======|  |   =  |    |" << endl
            << "\t\t\t|    |      |  |      |  |    = |  |      |  |    ==    |  |      |  |    = |    |" << endl
            << "\t\t\t|    |      |  |      |  |     =|  |======|  |          |  |      |  |     =|    |" << endl
            << "\t\t\t|                                                                                |" << endl
            << "\t\t\t|================================================================================|" << endl
            << "\n\t\t\t\tWelcome to play hangman. This game is to check your spelling skill" << endl;
        line(66);
        cout << "\t\t\tPress 1 to start Hangman game" << endl
            << "\t\t\tPress 2 to start cheat mode (This will show the hidden words)" << endl
            << "\t\t\tPress any key to exit.." << endl
            << "\t\t\t";
    }
}
// Prints hangman
void drawHangman() {
    cout << "\n\t\t\t   -------------" << endl
        << "\t\t\t  |            |" << endl
        << "\t\t\t  |            |" << endl
        << "\t\t\t  |           ---" << endl
        << "\t\t\t  |          -   -" << endl
        << "\t\t\t  |           ---" << endl
        << "\t\t\t  |           _|_ " << endl
        << "\t\t\t  |          / | \\ " << endl
        << "\t\t\t  |         /  |  \\  " << endl
        << "\t\t\t  |           _|_" << endl
        << "\t\t\t  |          |   |" << endl
        << "\t\t\t  |          |   |" << endl
        << "\t\t\t  |          |   |" << endl
        << "\t\t\t  |" << endl
        << "\t\t\t  |" << endl
        << "\t\t\t__|_________________" << endl;
}
// Prints walkman
void walk_man() {
    cout
        << "\n\t\t\t             ---" << endl
        << "\t\t\t          \\ -   - /  " << endl
        << "\t\t\t           \\ --- /  " << endl
        << "\t\t\t            \\_|_/  " << endl
        << "\t\t\t              |  " << endl
        << "\t\t\t              |   " << endl
        << "\t\t\t             _|_" << endl
        << "\t\t\t            |   |" << endl
        << "\t\t\t            |   |" << endl
        << "\t\t\t            |   |" << endl
        << "\t\t\t______________________________" << endl;
}
// Prints inverted hangman
void invert_hangman() {
    cout << "\n\t\t\t   -------------" << endl
        << "\t\t\t  |            |" << endl
        << "\t\t\t  |            |" << endl
        << "\t\t\t  |          |   |" << endl
        << "\t\t\t  |          |   |" << endl
        << "\t\t\t  |          |   |" << endl
        << "\t\t\t  |           -|-" << endl
        << "\t\t\t  |            |" << endl
        << "\t\t\t  |            |" << endl
        << "\t\t\t  |           _|_ " << endl
        << "\t\t\t  |          / | \\ " << endl
        << "\t\t\t  |         /  |  \\ " << endl
        << "\t\t\t  |           ---" << endl
        << "\t\t\t  |          -   -" << endl
        << "\t\t\t  |           ---" << endl
        << "\t\t\t  |" << endl
        << "\t\t\t  |" << endl
        << "\t\t\t__|_________________" << endl;
}
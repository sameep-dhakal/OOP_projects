#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

class WordPool
{
private:
    std::vector<std::string> words;

public:
    WordPool() : words({"programming", "computer", "hangman", "knowledge", "language"}) {}

    std::string getRandomWord()
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        return words[rand() % words.size()];
    }
};

class HangmanGame
{
private:
    std::string word;
    std::string maskedWord;
    int attempts;
    const int MAX_ATTEMPTS = 6;
    std::vector<char> guessedLetters;
    WordPool wordPool;

public:
    HangmanGame()
    {
        word = wordPool.getRandomWord();
        maskedWord = std::string(word.size(), '_');
        attempts = 0;
    }

    void display()
    {
        printHangman();
        std::cout << maskedWord << "\n";
        std::cout << "Guessed letters: ";
        for (char c : guessedLetters)
        {
            std::cout << c << " ";
        }
        std::cout << "\n";
    }

    bool isGameOver()
    {
        return attempts == MAX_ATTEMPTS || isWordGuessed();
    }

    bool isWordGuessed()
    {
        return maskedWord.find('_') == std::string::npos;
    }

    void guess(char letter)
    {
        if (std::find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end())
        {
            std::cout << "You've already guessed that letter!\n";
            return;
        }

        guessedLetters.push_back(letter);

        if (word.find(letter) != std::string::npos)
        {
            for (size_t i = 0; i < word.size(); ++i)
            {
                if (word[i] == letter)
                {
                    maskedWord[i] = letter;
                }
            }
        }
        else
        {
            attempts++;
        }
    }

    void printHangman()
    {
        switch (attempts)
        {
        case 0:
            std::cout << " +---+\n";
            std::cout << " |   |\n";
            std::cout << "     |\n";
            std::cout << "     |\n";
            std::cout << "     |\n";
            std::cout << "     |\n";
            std::cout << "======\n";
            break;
        case 1:
            std::cout << " +---+\n";
            std::cout << " |   |\n";
            std::cout << " O   |\n";
            std::cout << "     |\n";
            std::cout << "     |\n";
            std::cout << "     |\n";
            std::cout << "======\n";
            break;
        case 2:
            std::cout << " +---+\n";
            std::cout << " |   |\n";
            std::cout << " O   |\n";
            std::cout << " |   |\n";
            std::cout << "     |\n";
            std::cout << "     |\n";
            std::cout << "======\n";
            break;
        case 3:
            std::cout << " +---+\n";
            std::cout << " |   |\n";
            std::cout << " O   |\n";
            std::cout << "/|   |\n";
            std::cout << "     |\n";
            std::cout << "     |\n";
            std::cout << "======\n";
            break;
        case 4:
            std::cout << " +---+\n";
            std::cout << " |   |\n";
            std::cout << " O   |\n";
            std::cout << "/|\\  |\n";
            std::cout << "     |\n";
            std::cout << "     |\n";
            std::cout << "======\n";
            break;
        case 5:
            std::cout << " +---+\n";
            std::cout << " |   |\n";
            std::cout << " O   |\n";
            std::cout << "/|\\  |\n";
            std::cout << "/    |\n";
            std::cout << "     |\n";
            std::cout << "======\n";
            break;
        case 6:
            std::cout << " +---+\n";
            std::cout << " |   |\n";
            std::cout << " O   |\n";
            std::cout << "/|\\  |\n";
            std::cout << "/ \\  |\n";
            std::cout << "     |\n";
            std::cout << "======\n";
            break;
        }
    }
};

int main()
{
    HangmanGame game;
    std::cout << "Welcome to Hangman!\n";

    while (!game.isGameOver())
    {
        game.display();
        std::cout << "Guess a letter: ";
        char guess;
        std::cin >> guess;
        game.guess(guess);
    }

    game.display();
    if (game.isWordGuessed())
    {
        std::cout << "Congratulations! You've guessed the word!\n";
    }
    else
    {
        std::cout << "Game Over.\n";
    }

    return 0;
}
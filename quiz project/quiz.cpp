#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Question {
public:
    std::string question;
    std::string options[4];
    std::string correctoption;


    void setData() {
        std::cout << "Enter the question: ";
        std::cin.ignore();
        std::getline(std::cin, question);

        std::cout << "Enter 4 options:\n";
        for (int i = 0; i < 4; ++i) {
            std::cout << "Option " << i + 1 << ": ";
            std::getline(std::cin, options[i]);
        }

        std::cout << "Enter the correct option (1-4): ";
        std::cin >> correctoption;
    }

    void saveToFile(std::ofstream &file) {
        file << question << "\n";
        for (int i = 0; i < 4; ++i) {
            file << options[i] << "\n";
        }
        file << correctoption << "\n";
    }

    void displayQuestion() {
        std::cout << question << "\n";
        for (int i = 0; i < 4; ++i) {
            std::cout << i + 1 << ". " << options[i] << "\n";
        }
    }
    friend void displayQuestionsFromFile();
};

void addQuestionToFile() {
    std::ofstream file("quiz_questions.txt", std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Unable to open file.\n";
        return;
    }

    Question q;
    q.setData();
    q.saveToFile(file);

    file.close();
    std::cout << "Question added successfully.\n";
}
void displayQuestionsfromfile()
{
	std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open file.\n";
    }

    std::vector<Question> objects;
    Question currentObject;

    while (true) {
        std::string line;
        char ans;
        for (int i = 0; i < 6; ++i) {
            if (!std::getline(file, line)) {
                break; // Exit loop when end of file is reached
            }

            switch (i) {
                case 0: currentObject.question = line; break;
                case 1: currentObject.options[0] = line; break;
                case 2: currentObject.options[1] = line; break;
                case 3: currentObject.options[2]= line; break;
                case 4: currentObject.options[3]= line; break;
                case 5: currentObject.correctoption=line; break;
            }
        }

        if (file.eof()) {
            break;
        }
		currentObject.displayQuestion();
        objects.push_back(currentObject);
    }

    file.close();

}


int main() {
    int choice;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Add a question\n";
        std::cout << "2. Display questions\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addQuestionToFile();
                break;
            case 2:
                displayQuestionsFromFile();
                break;
            case 3:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}

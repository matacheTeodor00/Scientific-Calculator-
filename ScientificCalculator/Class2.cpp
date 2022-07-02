#include <iostream>
#include <string.h>
#include <stdexcept>

using namespace std;

template<typename T>


class MultiplicationDivison {
private:
    char *input = nullptr;
    int *operatorPosition = nullptr;
    const string allowedCharacters = "*/";


public:

    //Destructor
    ~MultiplicationDivison() {

        delete[] this->input;
        delete[] this->operatorPosition;
    }

    //Copy Constructor
    MultiplicationDivison(const MultiplicationDivison &object) : allowedCharacters(object.allowedCharacters) {

        this->input = new char[strlen(object.input) + 1];
        strcpy_s(this->input, strlen(object.input) + 1, object.input);

        operatorPosition = new int;
        *operatorPosition = *(object.operatorPosition);

    }

    void operator=(MultiplicationDivison source) {

        this->input = new char[strlen(source.input) + 1];
        strcpy_s(this->input, strlen(source.input) + 1, source.input);

        operatorPosition = new int;
        *operatorPosition = *(source.operatorPosition);

    }

    char *getInput() {
        return this->input;
    }

    int *getOperatorPos() {
        return this->operatorPosition;
    }

    string getAllowedCharacter() {
        return this->allowedCharacters;
    }

    void setInput(char *input) {
        this->input = new char[strlen(input) + 1];
        strcpy(this->input, input);
    }

    void setOperatorPosition(int *operatorPosition) {
        this->operatorPosition = operatorPosition;
    }

    MultiplicationDivison() {

    }

    MultiplicationDivison(char *input) {
        setInput(input);
    }

//    ~PlusMinus() {
//        cout << endl << "CALLING DESTRUCTOR" << endl;
//        delete[] this->input;
//        delete[] this->operatorPosition;
//    }

    static double multiply(T x, T y) {
        return x * y;

    }

    static double divide(T x, T y) {
        if (y == 0) {
            throw std::runtime_error("You can't divide by 0");
        }
        return x / y;
    }

    static string solve(char *input) {
        int posFirstMultiplication = findPos('*', input);
        int posFirstDivision = findPos('/', input);
        int firstNumber, secondNumber, newNumber;
        string newInput;
        if (posFirstMultiplication == -1 && posFirstDivision == -1) {
            return input;
        }
        if (posFirstMultiplication != -1 && posFirstMultiplication < posFirstDivision || posFirstDivision == -1) {
            int mostLeftDigit = findNextNonDecimalCharacter(posFirstMultiplication, input, direction::LEFT);
            int mostRightDigit = findNextNonDecimalCharacter(posFirstMultiplication, input, direction::RIGHT);
            firstNumber = getNumberFromInput(input, mostLeftDigit, posFirstMultiplication - 1);
            secondNumber = getNumberFromInput(input, posFirstMultiplication + 1, mostRightDigit);
            newNumber = multiply(firstNumber, secondNumber);
            string inputString = input;
            if (mostLeftDigit != 0)
                newInput = inputString.substr(0, mostLeftDigit + 1);
            newInput.append(to_string(newNumber));
            newInput.append(inputString.substr(mostRightDigit, string::npos));
        } else if (posFirstMultiplication > posFirstDivision || posFirstMultiplication == -1) {
            int mostLeftDigit = findNextNonDecimalCharacter(posFirstDivision, input, direction::LEFT);
            int mostRightDigit = findNextNonDecimalCharacter(posFirstDivision, input, direction::RIGHT);
            firstNumber = getNumberFromInput(input,
                                             mostLeftDigit,
                                             posFirstDivision - 1);
            secondNumber = getNumberFromInput(input, posFirstDivision + 1, mostRightDigit);
            newNumber = divide(firstNumber, secondNumber);
            string inputString = input;
            if (mostLeftDigit != 0)
                newInput = inputString.substr(0, mostLeftDigit + 1);
            newInput.append(to_string(newNumber));
            newInput.append(inputString.substr(mostRightDigit, string::npos));
        }
        char newInputArray[newInput.length() + 1];
        for (int i = 0; i < newInput.length(); i++) {
            newInputArray[i] = newInput[i];
        }
        newInputArray[newInput.length()] = '\0';
        return solve(newInputArray);
    }

    static int findPos(char character, char *input) {
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == character)
                return i;
        }
        return -1;
    }

    static int getNumberFromInput(char *input, int l, int r) {
        string number = "";
        for (int i = l; i <= r; i++) {
            number += input[i];
        }
        return stoi(number);
    }

    static int findNextNonDecimalCharacter(int pos, char *input, direction direction) {
        if (direction == direction::LEFT) {
            for (int i = pos - 1; i >= 0; i--) {
                if ((input[i] < '0' || input[i] > '9') && input[i] != '.')
                    return i;
            }
            return 0;
        }
        int i;
        for (i = pos + 1; input[i] != '\0'; i++) {
            if (input[i] < '0' || input[i] > '9')
                return i;
        }
        return i;
    }

    //friend void operator<<(ostream& console, PlusMinus& plusMinus);
};

//void operator<<(ostream& console, PlusMinus plusMinus) {
//	//console << endl << "The no of operations is: " << plusMinus.getNoOp() << endl;
//	console << endl << "The allowed characters are: " << plusMinus.getAllowedCharacter() << endl;
//
//	if (plusMinus.getInput() == nullptr) {
//		console << endl << "NO INPUT" << endl;
//	}
//	else {
//		char* input = plusMinus.getInput();
//		for (int i = 0; i < input[i] != '\0'; i++) {
//			console << input[i];
//		}
//		console << endl;
//	}
//
//	//la fel pentru array de inturi
//
//
//}


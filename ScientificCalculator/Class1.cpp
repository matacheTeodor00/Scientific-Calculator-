#include <iostream>
#include <string.h>

using namespace std;

enum direction {
    LEFT = 'l', RIGHT = 'r'
};

template<typename T>


class PlusMinus {
private:
    char *input = nullptr;
    int *operatorPosition = nullptr;
    const string allowedCharacters = "+-";


public:
    //Destructor
    ~PlusMinus() {

        delete[] this->input;
        delete[] this->operatorPosition;
    }

    //Copy Constructor
    PlusMinus(const PlusMinus &object) : allowedCharacters(object.allowedCharacters) {


        this->input = new char[strlen(object.input) + 1];
        strcpy_s(this->input, strlen(object.input) + 1, object.input);

        operatorPosition = new int;
        *operatorPosition = *(object.operatorPosition);

    }

    //equals operator overloading

    void operator=(PlusMinus source) {

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

    PlusMinus() {

    }

    PlusMinus(char *input) {
        setInput(input);
    }


    static double addition(T x, T y) {
        return x + y;

    }

    static double substraction(T x, T y) {
        return x - y;
    }

    static string solve(char *input) {
        int posFirstAddition = findPos('+', input);
        int posFirstSubstraction = findPos('-', input);
        int firstNumber, secondNumber, newNumber;
        string newInput;
        if (posFirstAddition == -1 && posFirstSubstraction == -1) {
            return input;
        }
        if (posFirstAddition != -1 && posFirstAddition < posFirstSubstraction || posFirstSubstraction == -1) {
            int mostLeftDigit = findNextNonDecimalCharacter(posFirstAddition, input, direction::LEFT);
            int mostRightDigit = findNextNonDecimalCharacter(posFirstAddition, input, direction::RIGHT);
            firstNumber = getNumberFromInput(input, mostLeftDigit, posFirstAddition - 1);
            secondNumber = getNumberFromInput(input, posFirstAddition + 1, mostRightDigit);
            newNumber = addition(firstNumber, secondNumber);
            string inputString = input;
            if (mostLeftDigit != 0)
                newInput = inputString.substr(0, mostLeftDigit + 1);
            newInput.append(to_string(newNumber));
            newInput.append(inputString.substr(mostRightDigit, string::npos));
        } else if (posFirstAddition > posFirstSubstraction || posFirstAddition == -1) {
            int mostLeftDigit = findNextNonDecimalCharacter(posFirstSubstraction, input, direction::LEFT);
            int mostRightDigit = findNextNonDecimalCharacter(posFirstSubstraction, input, direction::RIGHT);
            firstNumber = getNumberFromInput(input,
                                             findNextNonDecimalCharacter(posFirstSubstraction, input, direction::LEFT),
                                             posFirstSubstraction - 1);
            secondNumber = getNumberFromInput(input, posFirstSubstraction + 1,
                                              findNextNonDecimalCharacter(posFirstSubstraction, input,
                                                                          direction::RIGHT));
            newNumber = substraction(firstNumber, secondNumber);
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
                if (input[i] < '0' || input[i] > '9')
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


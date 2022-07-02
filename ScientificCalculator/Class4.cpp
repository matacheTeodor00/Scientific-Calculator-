#pragma once
#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

template<typename T>


class Paranthesis {
private:
    char *input = nullptr;
    int *operatorPosition = nullptr;
    const string allowedCharacters = "[]()";


public:

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

    Paranthesis() {

    }

    Paranthesis(char *input) {
        setInput(input);
    }

//    ~PlusMinus() {
//        cout << endl << "CALLING DESTRUCTOR" << endl;
//        delete[] this->input;
//        delete[] this->operatorPosition;
//    }

    static double poww(T x, T y) {
        return pow(x, y);

    }

    static double roott(T x, T y) {
        return pow(x, 1.0 / y);
    }

    static string solve(char *input) {
        string stringInput = input;
        int posFirstClose = findPos(')', stringInput, 1);
        int posFirstOpen = findPos('(', stringInput.substr(0, posFirstClose), 2);
        while (posFirstClose != -1) {
            string substring = stringInput.substr(posFirstOpen + 1, posFirstClose - posFirstOpen - 1);
            PlusMinus<double> plusMinusEngine;
            char *input = &substring[0];
            string result = mainSolve(input);
            string newStringInput = stringInput.substr(0, posFirstOpen);
            newStringInput.append(result);
            newStringInput.append(stringInput.substr(posFirstClose + 1, stringInput.length()));
            stringInput = newStringInput;
            posFirstClose = findPos(')', stringInput, 1);
            posFirstOpen = findPos('(', stringInput.substr(0, posFirstClose), 2);
        }

        posFirstClose = findPos(']', stringInput, 1);
        posFirstOpen = findPos('[', stringInput.substr(0, posFirstClose), 2);
        while (posFirstClose != -1) {
            string substring = stringInput.substr(posFirstOpen + 1, posFirstClose - posFirstOpen - 1);
            PlusMinus<double> plusMinusEngine;
            char *input = &substring[0];
            string result = mainSolve(input);
            string newStringInput = stringInput.substr(0, posFirstOpen);
            newStringInput.append(result);
            newStringInput.append(stringInput.substr(posFirstClose + 1, stringInput.length()));
            stringInput = newStringInput;
            posFirstClose = findPos(']', stringInput, 1);
            posFirstOpen = findPos('[', stringInput.substr(0, posFirstClose), 2);
        }
        stringInput = mainSolve(&stringInput[0]);
        return stringInput;

    }

    static string mainSolve(string input) {
        PlusMinus<double> plusMinusEngine;
        MultiplicationDivison<double> multiplyDivideEngine;
        PowerRoot<double> powerRootEngine;
        input = powerRootEngine.solve(&input[0]);
        input = multiplyDivideEngine.solve(&input[0]);
        input = plusMinusEngine.solve(&input[0]);

        return input;

    }

    static int findPos(char character, string input, int flag) {
        //first position
        if (flag == 1) {
            for (int i = 0; input[i] != '\0'; i++) {
                if (input[i] == character)
                    return i;

            }
            //last position;
        } else {
            for (int i = input.length() - 1; i >= 0; i--) {
                if (input[i] == character) {
                    return i;
                }
            }
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


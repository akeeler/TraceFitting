/*! \file InputHandler.cpp
 *  \brief A class to handle the user input to the program
 *  \author S. V. Paulauskas
 *  \date October 29, 2014
*/
#include <iostream>

#include "InputHandler.hpp"

using namespace std;

InputHandler::InputHandler() {
    doFitAgain_ = false;
    ReadFunctionNumber();
    ReadFittingRange();
}

void InputHandler::ReadFunctionNumber(void) {
    cout << "How about we choose a function to fit with: " << endl
         << "(0) Vandle Function" << endl << "(1) SiPmt Fast Function" << endl
         << "(2) EmCal Function" << endl << "(3) CsI Function" << endl;
    cin >> funcNum_;
}

void InputHandler::ReadFittingRange(void) {
    cout << "Now how about hooking me up with a fitting range." << endl;
    cin >> rangeLow_ >> rangeHigh_;
}

void InputHandler::ReadRepeatFit(void) {
    cout << "Would you like to start the fit over again?" << endl;
    string ans;
    if(ans == "y" || ans == "yes" || ans == "Yes" || ans == "Y")
        doFitAgain_ = true;
    else
        doFitAgain_ = false;
}

/**************************************************************************
 *  Copyright S. V. Paulauskas 2014                                       *
 *                                                                        *
 *  This program is free software: you can redistribute it and/or modify  *
 *  it under the terms of the GNU General Public License as published by  *
 *  the Free Software Foundation, version 3.0 License.                    *
 *                                                                        *
 *  This program is distributed in the hope that it will be useful,       *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *  GNU General Public License for more details.                          *
 *                                                                        *
 *  You should have received a copy of the GNU General Public License     *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *************************************************************************/
/*! \file Tokenizer.cpp
 *  \brief A class to tokenize a string
 *  \author S. V. Paulauskas
 *  \date  14 October 2014
 */
#include <fstream>
#include <iostream>

#include "Tokenizer.hpp"

using namespace std;

Tokenizer::Tokenizer(const std::string &file, const std::string &delim) {
    file_ = file;
    delimiter_ = delim;

    Tokenize();
}

void Tokenizer::Tokenize(void) {
    ifstream infile(file_.c_str());
    if(!infile)
        cerr << "Cannot open input file. Try again, son." << endl;
    else {
        while(infile) {
            if (isdigit(infile.peek())) {
                string s;
                getline(infile, s);
                size_t current;
                size_t next = -1;
                int columnNum = 0;
                do {
                    current = next + 1;
                    next = s.find_first_of(' ', current );
                    double temp =
                        atof(s.substr( current, next - current ).c_str());
                    switch(columnNum) {
                    case(0):
                        xVals_.push_back(temp);
                        break;
                    case(1):
                        yVals_.push_back(temp);
                        break;
                    case(2):
                        yErrVals_.push_back(temp);
                        break;
                    default:
                        break;
                    }
                    columnNum++;
                } while (next != string::npos);
            } else
                infile.ignore(1000,'\n');
        }
    }
}

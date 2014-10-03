/*! \file main.cpp
 * \brief File containing the main function for the ROOT based trace fitting
 * \author S. V. Paulauskas
 * \date 03 October 2014
 */
#include <iostream>
#include <fstream>
#include <vector>

#include <TGraph.h>
#include <TF1.h>

#include "VandleTimingFunction.hpp"

using namespace std;

int main() {
    vector<double> xvals, yvals;
    
    ifstream infile("data/plsr-nscl-revf.dat");
    if(!infile)
        cerr << "Cannot open input file. Try again, son." << endl;
    else {
        while(infile) {
            if (isdigit(infile.peek())) {
                int junk, junk1;
                infile >> junk >> junk1;
                xvals.push_back(junk);
                yvals.push_back(junk1);
            } else
                infile.ignore(1000,'\n');
        }
    }

    
    
}

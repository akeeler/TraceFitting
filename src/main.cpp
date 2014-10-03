/*! \file main.cpp
 * \brief File containing the main function for the ROOT based trace fitting
 * \author S. V. Paulauskas
 * \date 03 October 2014
 */
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

#include <TApplication.h>
#include <TAxis.h>
#include <TGraph.h>
#include <TF1.h>
#include <TFitResult.h>

#include "Trace.hpp"
#include "VandleTimingFunction.hpp"

using namespace std;

int main() {
    TApplication app("app", 0, 0);

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

    Trace trc(yvals);
    int lo = trc.GetMaxPos() - 5;
    int hi = trc.GetMaxPos() + 25;

    VandleTimingFunction *fobj = new VandleTimingFunction();
    TF1 *f = new TF1("f", fobj, 0., 1000., 4, "VandleTimingFunction");
    f->SetLineColor(kRed);
    f->SetParameters(trc.GetMaxPos(), trc.GetQdc(), 1.0, 1.0);

    TGraph *graph =  new TGraph(xvals.size(), &(xvals[0]), &(yvals[0]));
    graph->GetXaxis()->SetRangeUser(lo,hi);
    TFitResultPtr fitResults = graph->Fit(f,"MENRS", "MINUIT2", lo, hi);
    int fitStatus = fitResults;

    cout << "Fit Status : " << fitStatus << endl;

    graph->Draw();
    f->Draw("same");
    app.Run(kTRUE);
}

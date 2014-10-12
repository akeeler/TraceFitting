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
  **************************************************************************
*/

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
#include <TGraphErrors.h>
#include <TF1.h>
#include <TFitResult.h>

#include "Trace.hpp"
#include "VandleTimingFunction.hpp"
#include "EmCalTimingFunction.hpp"

using namespace std;

int main() {
    vector<double> xvals, yvals;

    ifstream infile("data/plsr-1000mV-02ns-num05.dat");
    if(!infile)
        cerr << "Cannot open input file. Try again, son." << endl;
    else {
        while(infile) {
            if (isdigit(infile.peek())) {
                int junk, junk1, junk2;
                infile >> junk >> junk1 >> junk2;
                cout << junk << " " << junk1 << " " << junk2 << endl;
                xvals.push_back(junk);
                yvals.push_back(junk1);
            } else
                infile.ignore(1000,'\n');
        }
    }

    cout << yvals.size() << endl;

    Trace trc(yvals);
    int lo = trc.GetMaxPos() - 5;
    int hi = trc.GetMaxPos() + 40;

    EmCalTimingFunction *fobj = new EmCalTimingFunction();
    fobj->SetBaseline(trc.GetBaseline());

    TF1 *f = new TF1("f", fobj, 0., 1000., 4, "EmCalTimingFunction");
    f->SetLineColor(kRed);
    f->SetParameters(trc.GetMaxPos(), trc.GetQdc()*0.5, 1.0, 1.0);

    TGraphErrors *graph =
        new TGraphErrors(xvals.size(), &(xvals[0]), &(yvals[0]));

    for(unsigned int i = 0; i < xvals.size(); i++)
        graph->SetPointError(i,0.0,trc.GetStandardDeviationBaseline());

    graph->GetXaxis()->SetRangeUser(lo,hi);

    TFitResultPtr fitResults = graph->Fit(f,"MENRS", "", lo, hi);
    int fitStatus = fitResults;

    cout << "Fit Status : " << fitStatus << endl;
    cout << "QDC : " << trc.GetQdc() << endl;

    TApplication app("app", 0, 0);
    graph->Draw();
    f->Draw("same");
    app.Run(kTRUE);
}

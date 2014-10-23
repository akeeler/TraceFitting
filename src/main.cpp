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
#include <string>
#include <vector>

#include <TApplication.h>
#include <TAxis.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TFitResult.h>

#include "Tokenizer.hpp"
#include "Trace.hpp"

#include "EmCalTimingFunction.hpp"
#include "SiPmtFastTimingFunction.hpp"
#include "VandleTimingFunction.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "You must provide me with a text file containing a trace!!"
             << endl;
        cerr << "I suggest the following format x,y or x,y,y_err." << endl;
        exit(2);
    }

    string fileName = argv[1];
    Tokenizer token(fileName, " ");
    vector<double> xvals = token.GetXVals();
    vector<double> yvals = token.GetYVals();

    Trace trc(yvals, 5, 10);
    double lo = xvals.at(trc.GetWaveformLowSampleNum());
    double hi = xvals.at(trc.GetWaveformHighSampleNum());
    cout << lo << " " << trc.GetMaxPos() << " " << hi << " " << endl;

    VandleTimingFunction *fobj = new VandleTimingFunction();
    fobj->SetBaseline(trc.GetBaseline());

    TF1 *f = new TF1("f", fobj, 0., 1.e6, 4, "VandleTimingFunction");
    f->SetLineColor(kRed);
    f->SetParameters(lo, trc.GetQdc()*0.5, 0.5, 0.5);

    TGraphErrors *graph =
        new TGraphErrors(xvals.size(), &(xvals[0]), &(yvals[0]));

    for(unsigned int i = 0; i < xvals.size(); i++)
        graph->SetPointError(i,0.0,trc.GetStandardDeviationBaseline());

    graph->GetXaxis()->SetRangeUser(lo, hi);

    TFitResultPtr fitResults = graph->Fit(f,"MENRS", "", lo, hi);
    int fitStatus = fitResults;

    cout << "Fit Status : " << fitStatus << endl;
    cout << "QDC : " << trc.GetQdc() << endl;

    TApplication app("app", 0, 0);
    graph->Draw();
    f->Draw("same");
    app.Run(kTRUE);
}

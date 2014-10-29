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

#include "InputHandler.hpp"
#include "Tokenizer.hpp"
#include "Trace.hpp"

#include "EmCalTimingFunction.hpp"
#include "SiPmtFastTimingFunction.hpp"
#include "VandleTimingFunction.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) {
        cerr << "Usage: ./traceFit <pathToTrace>" << endl;
        cerr << "You must provide me with a text file containing a trace!!"
             << endl;
        cerr << "I suggest the following format x,y or x,y,y_err." << endl;

        exit(2);
    }

    InputHandler input;
    bool isFirstFit = true;

    SiPmtFastTimingFunction *siFunc;
    VandleTimingFunction *vandleFunc;
    EmCalTimingFunction *emcalFunc;
    TF1 *func;

    string fileName = argv[1];
    Tokenizer token(fileName, " ");
    vector<double> xvals = token.GetXVals();
    vector<double> yvals = token.GetYVals();

    Trace trc(yvals, input.GetRangeLow(), input.GetRangeHigh());
    double lo = xvals.at(trc.GetWaveformLowSampleNum());
    double hi = xvals.at(trc.GetWaveformHighSampleNum());
    cout << lo << " " << trc.GetMaxPos() << " " << hi << " " << endl;

    switch(input.GetFuncNum()) {
    case(0):
        vandleFunc = new VandleTimingFunction();
        vandleFunc->SetBaseline(trc.GetBaseline());
        func = new TF1("func", vandleFunc, 0., 1.e6, 4,
            "VandleTimingFunction");
        func->SetParameters(lo, trc.GetQdc()*0.5, 0.5, 0.5);
        break;
    case(1):
        siFunc = new SiPmtFastTimingFunction();
        siFunc->SetBaseline(trc.GetBaseline());
        func = new TF1("func", siFunc, 0., 1.e6, 3,
            "SiPmtFastTimingFunction");
        func->SetParameters(trc.GetMaxPos(), trc.GetQdc()*0.5, 0.5);
        break;
    case(2):
        emcalFunc = new EmCalTimingFunction();
        emcalFunc->SetBaseline(trc.GetBaseline());
        func = new TF1("func", emcalFunc, 0., 1.e6, 4,
            "EmCalTimingFunction");
        func->SetParameters(lo, trc.GetQdc()*0.5, 0.5, 0.5);
    default:
        vandleFunc = new VandleTimingFunction();
        vandleFunc->SetBaseline(trc.GetBaseline());
        func = new TF1("func", vandleFunc, 0., 1.e6, 4,
            "VandleTimingFunction");
        func->SetParameters(lo, trc.GetQdc()*0.5, 0.5, 0.5);
        break;
    }
    func->SetLineColor(kRed);

    TGraphErrors *graph =
    new TGraphErrors(xvals.size(), &(xvals[0]), &(yvals[0]));

    for(unsigned int i = 0; i < xvals.size(); i++)
        graph->SetPointError(i,0.0,trc.GetStandardDeviationBaseline());

    graph->GetXaxis()->SetRangeUser(lo, hi);

    TFitResultPtr fitResults = graph->Fit(func,"MENRS", "", lo, hi);
    int fitStatus = fitResults;

    cout << "Fit Status : " << fitStatus << endl;
    cout << "QDC : " << trc.GetQdc() << endl;

    TApplication app("app", 0, 0);
    graph->Draw();
    func->Draw("same");
    app.Run(kTRUE);
}

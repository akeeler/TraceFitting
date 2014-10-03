/** \file Trace.cpp
 *  \brief A class to handle the processing of traces
 *  \author S. V. Paulauskas
 *  \date 27 March 2014
 *
 * Parts of this code are adopted from the pixie_scan code
 * developed at the University of Tenneessee at Knoxville
 * by the Nuclear Structure group.
 */
#include <algorithm>
#include <iostream>
#include <limits>

#include <TF1.h>
#include <TGraph.h>

#include "Trace.hpp"
#include "Vars.hpp"

using namespace std;

Trace::Trace(const vector<short unsigned int> &trc) {
    waveformLow_ = 5;
    waveformHigh_ = 25;
    trc_ = trc;

    CalcMaxInfo();
    CalcWaveformBounds();
    CalcBaselineInfo();
    CalcWaveform();
    CalcQdc();
    //CalcSnr();
    CalcPhase();
};

void Trace::CalcBaselineInfo(void) {
    if(waveformLowSampleNum_ < 0) {
        baseline_ = numeric_limits<double>::quiet_NaN();
        stddev_ = numeric_limits<double>::quiet_NaN();
    }else {
        baseline_ = 0;
        stddev_ = 0;
        for(unsigned int i = 0; i < waveformLowSampleNum_; i++)
            baseline_ += trc_.at(i);
        baseline_ /= waveformLowSampleNum_;
        
        for(unsigned int i = 0; i < waveformLowSampleNum_; i++)
            stddev_ += pow(trc_.at(i) - baseline_,2);
        stddev_ = sqrt(stddev_/waveformLowSampleNum_);
    }
    cout << baseline_ << " " << stddev_ << " " << endl;
}

void Trace::CalcMaxInfo(void) {
    auto max = max_element(trc_.begin(), trc_.end());
    maxPos_ = (int)(max - trc_.begin());
    maxVal_ = *max;
}

void Trace::CalcPhase(void) {
    TF1 *traceFit = new TF1("traceFit", Trace::VandleFunction, 0.0, 
                            (double)waveform_.size(), 2);
    
    vector<double> xvals;
    for(unsigned int i = 0; i < waveform_.size(); i++) 
        xvals.push_back(i);

    TGraph *fitData = new TGraph(waveform_.size(), &(xvals[0]), &(waveform_[0]));


    delete(fitData);
    delete(traceFit);
}

void Trace::CalcQdc(void) {
    for(const auto it : waveform_)
        qdc_ += it;
}

void Trace::CalcSnr(void) {

}

void Trace::CalcWaveform(void) {
    for(unsigned int i = waveformLowSampleNum_; 
        i <= waveformHighSampleNum_; i++)
        waveform_.push_back(trc_[i] - baseline_);
}

void Trace::CalcWaveformBounds(void) {
    waveformLowSampleNum_ = maxPos_ - waveformLow_;
    waveformHighSampleNum_ = maxPos_ + waveformHigh_;
}

double Trace::VandleFunction(Double_t *x, Double_t *par) {
    double beta = 0.17706971465472;
    double gamma = 0.162673945899791;
    
    double phase = par[0];
    double amplitude = par[1];
    double diff = x[0] - phase;
    
    if(x[0] < phase)
        return(0.0);

    double val = qdc_ * amplitude * exp(-beta*diff) * 
        (1-exp(-pow(gamma*diff,4.)));

    return(val);
}


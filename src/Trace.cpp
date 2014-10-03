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

/*! \file Trace.cpp
 *  \brief A class to handle the processing of traces
 *  \author S. V. Paulauskas
 *  \date 27 March 2014
 *
 * Parts of this code are based off of from the pixie_scan code
 * developed at the University of Tenneessee at Knoxville
 * by the Nuclear Structure group.
 */
#include <algorithm>
#include <iostream>
#include <limits>

#include <TF1.h>
#include <TGraph.h>

#include "Trace.hpp"

using namespace std;

Trace::Trace(const vector<double> &trc) {
    waveformLow_ = 5;
    waveformHigh_ = 25;
    trc_ = trc;

    CalcMaxInfo();
    CalcWaveformBounds();
    CalcBaselineInfo();
    CalcWaveform();
    CalcQdc();
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
}

void Trace::CalcMaxInfo(void) {
    auto max = max_element(trc_.begin(), trc_.end());
    maxPos_ = (int)(max - trc_.begin());
    maxVal_ = *max;
}

void Trace::CalcQdc(void) {
    for(const auto it : waveform_)
        qdc_ += it;
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

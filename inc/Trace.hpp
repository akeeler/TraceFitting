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

/*! \file TraceHandler.hpp
 *  \brief A class to handle the processing of traces
 *  \author S. V. Paulauskas
 *  \date 27 March 2014
 */
#ifndef __TRACE_HPP__
#define __TRACE_HPP__
#include <vector>

class Trace {
public:
    Trace(){};
    Trace(const std::vector<double> &trc, const int &lo, const int &hi);
    ~Trace(){};

    double GetQdc(void){return(qdc_);};
    double GetBaseline(void){return(baseline_);};
    double GetWaveformLowSampleNum(void){return(waveformLowSampleNum_);};
    double GetWaveformHighSampleNum(void){return(waveformHighSampleNum_);};
    double GetStandardDeviationBaseline(void){return(stddev_);};
    double GetMaxPos(void){return(maxPos_);};

    std::vector<double> GetWaveform(void) {return(waveform_);};

private:
    double baseline_, maxVal_, phase_, qdc_, snr_, stddev_;
    unsigned int maxPos_, waveformLow_, waveformHigh_, waveformLowSampleNum_,
        waveformHighSampleNum_;
    std::vector<double> trc_;
    std::vector<double> waveform_;

    void CalcBaselineInfo(void);
    void CalcMaxInfo(void);
    void CalcPhase(void);
    void CalcQdc(void);
    void CalcWaveform(void);
    void CalcWaveformBounds(void);
};

#endif //__TRACE_HPP__

/** \file TraceHandler.hpp
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
    Trace(const std::vector<short unsigned int> &trc);
    ~Trace(){};

    double GetBaseline(void) {return(baseline_);};
    double GetStdDevBase(void) {return(stddev_);};
    double GetSnr(void) {return(snr_);};
    double GetPhase(void) {return(phase_);};
    std::vector<double> GetWaveform(void) {return(waveform_);};
    
private:
    double baseline_, maxVal_, phase_, qdc_, snr_, stddev_;
    unsigned int maxPos_, waveformLow_, waveformHigh_, waveformLowSampleNum_, 
        waveformHighSampleNum_;
    std::vector<short unsigned int> trc_;
    std::vector<double> waveform_;

    void CalcBaselineInfo(void);
    void CalcMaxInfo(void);
    void CalcPhase(void);
    void CalcQdc(void);
    void CalcSnr(void);
    void CalcWaveform(void);
    void CalcWaveformBounds(void);
   
    double VandleFunction(Double_t *x, Double_t *par);
};

#endif //__TRACE_HPP__

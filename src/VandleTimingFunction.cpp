/*! \file VandleTimingFunction.hpp
 *  \brief A class to handle the processing of traces
 *  \author S. V. Paulauskas
 *  \date 03 October 2014
 */

#include "VandleTimingFunciton.hpp"

VandleTimingFunction::Evaluate()(double *x, double *par) {
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

/*! \file VandleTimingFunction.hpp
 *  \brief A class to handle the processing of traces
 *  \author S. V. Paulauskas
 *  \date 03 October 2014
 */
#include <cmath>

#include "VandleTimingFunction.hpp"

double VandleTimingFunction::operator()(double *x, double *par) {
    //double beta = 0.17706971465472;
    //double gamma = 0.162673945899791;

    double phase = par[0];
    double amplitude = par[1];
    double beta = par[2];
    double gamma = par[3];
    double diff = x[0] - phase;

    if(x[0] < phase)
        return(15217.6388888889);

    double val = amplitude * exp(-beta*diff) * (1-exp(-pow(gamma*diff,4.)))
        +15217.6388888889;

    return(val);
}

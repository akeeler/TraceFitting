/*! \file VandleTimingFunction.hpp
 *  \brief A class to handle the processing of traces
 *  \author S. V. Paulauskas
 *  \date 03 October 2014
 */
#ifndef __VANDLETIMINGFUNCITON__HPP__
#define __VANDLETIMINGFUNCITON__HPP__

class VandleTimingFunction {
public:
    VandleTimingFunction() {};
    ~VandleTimingFunction(){};

    double Evaluate() (double *x, double *p);
};
#endif

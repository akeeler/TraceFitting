Trace Fitting ROOT
==================
Introduction
------------
This program implements a version of trace fitting inside the ROOT framework.
The previous versions of this fit were done with gnuplot. The results between
the two different programs/minimizers has been checked and the results are
consistent.

The fitting functions included with this program will be integrated into the
pixie_scan code developed by the Nuclear Structure group at the University of
Tennessee at Knoxville. They will makeup the core routines to perform high
resolution timing for VANDLE.

Input Data Formats
------------------
The program now recognizes the following data structure :
 * x,y
 * x,y,y_error
 * x,y,y_error,...,n
 Only the first two columns will be read into the program. In all of the current
 data files that I test with the x column is generally the trace sample number,
 and the y value is the amplitude of the trace at the sampling point. The
 program will return a y_error vector in the event that one wants to use it for
 some of the calculations. In principle, this vector is not used and is
 ignored.

 Usage
 -----
 ./traceFit <dataFile>

 Hardcoding
 ----------
 Currently, some of the features are hard coded. For example, the upper and
 lower bounds of the fit. I currently find it easier just changing them and
 recompiling than adding them as run time arguments (hooray IDEs). The same goes
 true for the fitting function to use. I have not found a trivial way to switch
 this up in the way that I am currently implementing the fitting. If somebody
 finds something better, let me know, please!

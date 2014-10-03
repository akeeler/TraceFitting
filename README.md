Trace Fitting ROOT
==================

This program implements a version of trace fitting inside the ROOT framework.
The previous versions of this fit were done with gnuplot. The results between
the two different programs/minimizers has been checked and the results are
consistent between the two.

This program will be integrated into the pixie_scan code developed by the
Nuclear Structure group at the University of Tennessee at Knoxville.

Note
----
Depending on the format of your data file you may or may not need to adjust the
code for reading in the data file. Currently, I assume a format of <x,y>. There
are other common formats in use that have <x,y,err_y>. This is not currently
coded.

Note 2
-------
It will be necessary to update the name of the file to be read. It is currently
hard coded, but I'm not planning to change that for now.

Note 3
-------
The baseline offset is also hard coded. That will need to be changed too.

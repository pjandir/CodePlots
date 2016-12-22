# EasyPlots

Using the ROOT framework, this is a drawing tool which will create plots (using the standard CMS style) from any flat or pseudo-flat nTuple structure. The package uses the DrawTree object as the workhorse and all other objects act as helpers: 

  * the Dataset object holds and represents a single dataset (or physics process) to plot;
  * the ToPlot object is what should be plotted including selections, any extra text, etc;
  * and the Color object exists for the use of any custom colors the user may wish. 

The user should look at the test directory for example code on how to use it. In addition, the user is encouraged to modify the package in any way necessary. Many functions, particularly in ToPlot, exist to make plotting or printing of info very easy and in some cases automatic. Any bugs or issues should be reported to the owner of this package. 

In the test/ directory, the user can find an example on the usage of this package. Additional information on ROOT and CMS can be found here: https://root.cern.ch/ and http://cms.web.cern.ch/, respectively.  

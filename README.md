# CodePlots

This is a drawing tool which will create plots (in CMS style) from any flat or psuedo-flat nTuple structure (within ROOT). See test directory for example code on how to use it. The package uses the DrawTree object as the workhorse and all other objects as helpers. The Dataset holds and represents a single dataset/process to plot, the ToPlot object is what should be plotted including selections, any extra text, etc and the Color object exists for the use of any custom colors the user may wish. The user is encouraged to modify the package in any way necessary. Many functions, particularly in ToPlot, exist to make plotting/printing of info very easy and in some cases automatic. Any bugs or issues should be reported to the owner of this package. 

Please also note no ROOT files are provided in this package; the user is resposible for the actual data. 

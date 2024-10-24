#ifndef PLOTTING_GNUPLOT_HPP
#define PLOTTING_GNUPLOT_HPP

#include <map>
#include <string>

using std::multimap;
using std::string;

// plotting.hpp
// Describes function related to
// result plotting and charting.
// 
// Most of the functions are using
// pbPlot library. You can browse more
// in detail at:
// https://repo.progsbase.com/repoviewer/no.inductive.libraries/Plots/latest/

int generate_plot_gnuplot( multimap<double,string> &map_time_series, short data_indices, 
const char *plot_title, const char *x_label, const char *y_label, 
const char *output_file_name );

#endif

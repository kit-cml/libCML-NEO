#ifndef PLOTTING_HPP
#define PLOTTING_HPP

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

int generate_plot( multimap<double,string> &map_time_series, short data_indices, 
const wchar_t *plot_title, const wchar_t *x_label, const wchar_t *y_label, 
const string output_file_name );

#endif
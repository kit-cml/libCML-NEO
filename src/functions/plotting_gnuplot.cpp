#include "plotting_gnuplot.hpp"

#include "../libs/pbPlots/pbPlots.hpp"
#include "../libs/pbPlots/supportLib.hpp"
#include "helper_stl.hpp"
#include "inputoutput.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::copy;
using std::multimap;
using std::pair;
using std::string;
using std::stringstream;
using std::vector;

int generate_plot_gnuplot( multimap<double,string> &map_time_series, short data_indices,
const char *plot_title, const char *x_label, const char *y_label,
const char *output_file_name )
{  
  FILE *pipe_gnuplot;
  int idx;
  vector<double> x_axis;
  vector<double> y_axis;
  vector<string> data_temp;

  if( map_time_series.size() == 0 ){
    mpi_fprintf(0, stderr, "No data to plot!\n");
    return 1;
  }
  for(std::multimap<double, string>::iterator itrmap = map_time_series.begin();
    itrmap != map_time_series.end() ;
    itrmap++ ){
    x_axis.push_back(itrmap->first);
    split_string(itrmap->second, ',', data_temp);
    y_axis.push_back(strtod((data_temp[data_indices]).c_str(),NULL));
    //mpi_printf(0, "%.4lf,%s\n", itrmap->first, (data_temp[data_indices]).c_str());
    data_temp.clear();
  }

  pipe_gnuplot = popen("gnuplot -persistent", "w");
  if(pipe_gnuplot == NULL){
    mpi_fprintf(0, stderr, "Problem opening pipeline to GNUplot!\n");
    return 1;
  }

  // set the output file type and name
  fprintf(pipe_gnuplot, "set terminal pngcairo enhanced\n");
  fprintf(pipe_gnuplot, "set output '%s'\n", output_file_name);

  // set labels and title
  fprintf(pipe_gnuplot, "set title '%s'\n", plot_title);
  fprintf(pipe_gnuplot, "set xlabel '%s'\n", x_label);
  fprintf(pipe_gnuplot, "set ylabel '%s'\n", y_label);

  // plot the data
  fprintf(pipe_gnuplot, "plot '-' with linepoints title 'Data Points'\n");
  for(idx = 0; idx < x_axis.size(); idx++){
    fprintf(pipe_gnuplot, "%lf %lf\n", x_axis[idx], y_axis[idx]);
  }
  fprintf(pipe_gnuplot, "e\n");

  fflush(pipe_gnuplot);
  pclose(pipe_gnuplot);
}

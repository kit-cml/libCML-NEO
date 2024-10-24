#include "plotting.hpp"

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

int generate_plot( multimap<double,string> &map_time_series, short data_indices, 
const wchar_t *plot_title, const wchar_t *x_label, const wchar_t *y_label, 
const string output_file_name )
{  
  vector<double> x_axis;
  vector<double> y_axis;
  vector<string> data_temp;
  char buffer[255];
  char *token;

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

  ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
  series->xs = &x_axis;
  series->ys = &y_axis;
  series->lineThickness = 5.;
  series->color = CreateRGBColor(0.631,0.403,0.647);
  
  ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
  settings->width = 1366;
  settings->height = 1080;
  settings->autoBoundaries = true;
  settings->autoPadding = true;
  settings->showGrid = false;
  settings->title = toVector(plot_title);
  settings->xAxisAuto = false;
  settings->xAxisBottom = true;
  settings->xAxisTop = false;
  settings->xLabel = toVector(x_label);
  settings->yLabel = toVector(y_label);
  settings->scatterPlotSeries->push_back(series);

  bool success;
  StringReference *errorMessage = CreateStringReferenceLengthValue(0, L' ');
  RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();
  success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

  if(success){
    vector<double> *pngdata = ConvertToPNG(imageReference->image);
    WriteToFile(pngdata, output_file_name);
    DeleteImage(imageReference->image);
  }else{
    mpi_fprintf(0, stderr, "Error: ");
    for(wchar_t c : *errorMessage->string){
      mpi_fprintf(0, stderr, "%c", c);
    }
    mpi_fprintf(0, stderr, "\n");
  }

  FreeAllocations();

  return success ? 0 : 1;
}
#ifndef CIPA_FEATURES_HPP
#define CIPA_FEATURES_HPP

#include <map>
#include <string>
#include <vector>

using std::multimap;
using std::string;
using std::vector;

struct Cipa_Features{
  short pace_target;
  double qnet;
  double qnet_apd;
  double qinward;
  double inal_auc;
  double ical_auc;
  double dvmdt_repol_max;
  double dvmdt_peak;
  double vm_peak;
  double vm_valley;
  double vm_amp30;
  double vm_amp50;
  double vm_amp90;
  double time_vm_peak;
  double apd90;
  double apd50;
  double apd_triangulation;
  double ca_peak;
  double ca_valley;
  double ca_amp30;
  double ca_amp50;
  double ca_amp90;
  double time_cad90_prev;
  double time_cad50_prev;
  double time_ca_peak;
  double cad90;
  double cad50;
  double cad_triangulation;
  multimap<double, string> time_series_data;
  multimap<double, double> vm_data;
  multimap<double, double> cai_data;
  vector<double> last_states;

  Cipa_Features();
  Cipa_Features( const Cipa_Features &source );
  Cipa_Features& operator=(const Cipa_Features & source);
  void copy(const Cipa_Features &source);
  void init(const double vm_val, const double ca_val);
};


#endif

#include "cipa_features.hpp"

Cipa_Features::Cipa_Features()
{

}

Cipa_Features::Cipa_Features( const Cipa_Features &source )
{
  copy(source);
}


Cipa_Features& Cipa_Features::operator=(const Cipa_Features & source)
{
  if( this != &source ) copy(source);

  return *this;
}

void Cipa_Features::copy(const Cipa_Features &source)
{
  pace_target = source.pace_target;
  qnet = source.qnet;
  qnet_apd = source.qnet_apd;
  qinward = source.qinward;
  inal_auc = source.inal_auc;
  ical_auc = source.ical_auc;
  dvmdt_repol_max = source.dvmdt_repol_max;
  dvmdt_peak = source.dvmdt_peak;
  vm_peak = source.vm_peak;
  vm_valley = source.vm_valley;
  apd90 = source.apd90;
  apd50 = source.apd50;
  vm_amp30 = source.vm_amp30;
  vm_amp50 = source.vm_amp50;
  vm_amp90 = source.vm_amp90;
  time_vm_peak = source.time_vm_peak;
  apd_triangulation = source.apd_triangulation;
  ca_peak = source.ca_peak;
  ca_valley = source.ca_valley;
  cad90 = source.cad90;
  cad50 = source.cad50;
  time_cad90_prev = source.time_cad90_prev;
  time_cad50_prev = source.time_cad50_prev;
  ca_amp30 = source.ca_amp30;
  ca_amp50 = source.ca_amp50;
  ca_amp90 = source.ca_amp90;
  time_ca_peak = source.time_ca_peak;
  cad_triangulation = source.cad_triangulation;
  time_series_data.clear();
  time_series_data.insert( (source.time_series_data).begin(), (source.time_series_data).end() );
  vm_data.clear();
  vm_data.insert( (source.vm_data).begin(), (source.vm_data).end() );
  cai_data.clear();
  cai_data.insert( (source.cai_data).begin(), (source.cai_data).end() );
  last_states.clear();
  last_states.insert( last_states.end(), (source.last_states).begin(), (source.last_states).end() );
}

void Cipa_Features::init(const double vm_val, const double ca_val)
{
  pace_target = 0;
  qnet = 0.;
  qnet_apd = 0.;
  qinward = 0.;
  inal_auc = 0.;
  ical_auc = 0.;
  dvmdt_repol_max = vm_val;
  dvmdt_peak = vm_val;
  vm_peak = vm_val;
  vm_valley = vm_val;
  vm_amp30 = vm_val;
  vm_amp50 = vm_val;
  vm_amp90 = vm_val;
  time_vm_peak = 0.0;
  apd90 = 0.;
  apd50 = 0.;
  ca_peak = ca_val;
  ca_valley = ca_val;
  ca_amp30 = ca_val;
  ca_amp50 = ca_val;
  ca_amp90 = ca_val;
  time_ca_peak = 0.0;
  time_cad90_prev = 0.0;
  time_cad50_prev = 0.0;
  cad90 = 0.;
  cad50 = 0.;
  time_series_data.clear();
  vm_data.clear();
  cai_data.clear();
  last_states.clear();
}

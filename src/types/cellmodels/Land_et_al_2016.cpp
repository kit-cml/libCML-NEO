/*
   There are a total of 24 entries in the algebraic variable array.
   There are a total of 7 entries in each of the rate and state variable arrays.
   There are a total of 30 entries in the constant variable array.
 */

#include "Land_et_al_2016.hpp"
#include <cmath>
#include <cstdlib>



Land_et_al_2016::Land_et_al_2016()
{
algebraic_size = 26;
constants_size = 29;
states_size = 7;
ALGEBRAIC = new double[algebraic_size];
CONSTANTS = new double[constants_size];
RATES = new double[states_size];
STATES = new double[states_size];
}

Land_et_al_2016::~Land_et_al_2016()
{
delete []ALGEBRAIC;
delete []CONSTANTS;
delete []RATES;
delete []STATES;
}

void Land_et_al_2016::initConsts()
{
// User input from Matlab functions
CONSTANTS[dlambda_dt] = 0; 
CONSTANTS[lambda] = 1.0;
CONSTANTS[C] = CONSTANTS[lambda] - 1;
CONSTANTS[Cai_elec] = 0.0;
CONSTANTS[is_skinned] = 0.;
STATES[XS] = 0.;
STATES[XW] = 0.;
STATES[TRPN] = 0.;
STATES[TmBlocked] = 0.;
STATES[ZETAS] = 0.;
STATES[ZETAW] = 0.;
STATES[dCd_dt] = 0.;


CONSTANTS[perm50] = 0.35;
CONSTANTS[TRPN_n] = 2;
CONSTANTS[koff] = 0.1;
CONSTANTS[dr] = 0.25;
CONSTANTS[wfrac] = 0.5;
CONSTANTS[TOT_A] = 25;
//CONSTANTS[ktm_unblock] = 1; // before margara
CONSTANTS[ktm_unblock] = 0.04; // after margara
CONSTANTS[beta_1_land] = -2.4;
CONSTANTS[beta_0] = 2.3;
CONSTANTS[gamma_idx] = 0.0085;
CONSTANTS[gamma_wu] = 0.615;
CONSTANTS[phi] = 2.23;
if ((int)CONSTANTS[is_skinned] == 0){
CONSTANTS[nperm] = 2.2;
ALGEBRAIC[ca50] = 2.5;
CONSTANTS[Tref] = 40.5;
CONSTANTS[nu] = 1;
CONSTANTS[mu] = 1;
}
else
{
//CONSTANTS[nperm] = 5.0; // before margara
CONSTANTS[nperm] = 2.4; // after margara
ALGEBRAIC[ca50] = 0.805;
CONSTANTS[Tref] = 120.0;
CONSTANTS[nu] = 7;
CONSTANTS[mu] = 3; 
}
CONSTANTS[k_ws] = 0.004 * CONSTANTS[mu];
CONSTANTS[k_uw] = 0.026 * CONSTANTS[nu];
CONSTANTS[par_k] = 7;
CONSTANTS[b] = 9.1;
CONSTANTS[eta_l] = 200;
CONSTANTS[eta_s] = 20;
CONSTANTS[land_a] = 2.1;

}


void Land_et_al_2016::computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC )
{
CONSTANTS[lambda] = fmin(1.2, CONSTANTS[lambda]);
ALGEBRAIC[Lfac]  = fmax(0, 1 + CONSTANTS[beta_0] * (CONSTANTS[lambda] + fmin(0.87, CONSTANTS[lambda]) - 1.87));
if (ALGEBRAIC[Lfac] < 0){
    ALGEBRAIC[Lfac] = 0 ;
}
ALGEBRAIC[cdw] = CONSTANTS[phi] * CONSTANTS[k_uw] * (1-CONSTANTS[dr])*(1-CONSTANTS[wfrac]) /  ((1-CONSTANTS[dr])*CONSTANTS[wfrac]);
ALGEBRAIC[cds] = CONSTANTS[phi] * CONSTANTS[k_ws] * (1-CONSTANTS[dr])*CONSTANTS[wfrac] / CONSTANTS[dr];
ALGEBRAIC[k_wu] = CONSTANTS[k_uw] * (1/CONSTANTS[wfrac] - 1) - CONSTANTS[k_ws];
ALGEBRAIC[k_su] = CONSTANTS[k_ws] * (1/CONSTANTS[dr] - 1) * CONSTANTS[wfrac]; 
ALGEBRAIC[A] = (0.25 * CONSTANTS[TOT_A]) / ((1-CONSTANTS[dr])*CONSTANTS[wfrac] + CONSTANTS[dr]) * (CONSTANTS[dr]/0.25);
ALGEBRAIC[XU] = (1 - STATES[TmBlocked]) - STATES[XW] - STATES[XS]; 
ALGEBRAIC[xb_ws] = CONSTANTS[k_ws] * STATES[XW];
ALGEBRAIC[xb_uw] = CONSTANTS[k_uw] * ALGEBRAIC[XU];
ALGEBRAIC[xb_wu] = ALGEBRAIC[k_wu] * STATES[XW];
ALGEBRAIC[xb_su] = ALGEBRAIC[k_su] * STATES[XS];
double temp_zetas1, temp_zetas2;
temp_zetas1=temp_zetas2=0;
if(STATES[ZETAS] > 0){
    temp_zetas1 = STATES[ZETAS];
}
if (STATES[ZETAS]<-1){
    temp_zetas2 = -1 * STATES[ZETAS] -1; 
}
ALGEBRAIC[gamma_rate] = CONSTANTS[gamma_idx] * fmax( temp_zetas1, temp_zetas2);
ALGEBRAIC[xb_su_gamma] = ALGEBRAIC[gamma_rate] * STATES[XS];
ALGEBRAIC[gamma_rate_w] = CONSTANTS[gamma_wu] * fabs(STATES[ZETAW]); 
ALGEBRAIC[xb_wu_gamma] = ALGEBRAIC[gamma_rate_w] * STATES[XW];
ALGEBRAIC[ca50] = ALGEBRAIC[ca50] + CONSTANTS[beta_1_land] * fmin(0.2, CONSTANTS[lambda] - 1);
ALGEBRAIC[XSSS] = CONSTANTS[dr] * 0.5;
ALGEBRAIC[XWSS] = (1 - CONSTANTS[dr]) * CONSTANTS[wfrac] * 0.5;
ALGEBRAIC[ktm_block]= CONSTANTS[ktm_unblock] * (pow(CONSTANTS[perm50], CONSTANTS[nperm]) * 0.5) / (0.5 - ALGEBRAIC[XSSS] - ALGEBRAIC[XWSS]);
ALGEBRAIC[Cd] = STATES[dCd_dt];
if ((CONSTANTS[C] - ALGEBRAIC[Cd]) < 0) {
CONSTANTS[eta] = CONSTANTS[eta_s];
} else {
CONSTANTS[eta] = CONSTANTS[eta_l];
}
ALGEBRAIC[v_C] = CONSTANTS[par_k] * (CONSTANTS[C] - CONSTANTS[Cd]) / CONSTANTS[eta];
ALGEBRAIC[Fd] = eta * ALGEBRAIC[v_C];
ALGEBRAIC[F1] = (exp(CONSTANTS[b] * CONSTANTS[C]) - 1);
ALGEBRAIC[Tp] = CONSTANTS[land_a] * (ALGEBRAIC[F1] + ALGEBRAIC[Fd]);
ALGEBRAIC[Ta] = ALGEBRAIC[Lfac] * (CONSTANTS[Tref] / CONSTANTS[dr]) * ( (STATES[ZETAS] + 1) * STATES[XS] + (STATES[ZETAW]) * STATES[XW]);
ALGEBRAIC[land_T] = ALGEBRAIC[Ta] + ALGEBRAIC[Tp];




RATES[XS] = ALGEBRAIC[xb_ws] - ALGEBRAIC[xb_su] - ALGEBRAIC[xb_wu_gamma];
RATES[XW] = ALGEBRAIC[xb_uw] - ALGEBRAIC[xb_wu] - ALGEBRAIC[xb_ws] - ALGEBRAIC[xb_wu_gamma];
RATES[TRPN] = CONSTANTS[koff] * (pow((CONSTANTS[Cai_elec] / ALGEBRAIC[ca50]), CONSTANTS[TRPN_n]) * (1 - STATES[TRPN]) - STATES[TRPN]);
RATES[TmBlocked] = CONSTANTS[ktm_block] * fmin(100, pow(STATES[TRPN], -(CONSTANTS[nperm] / 2))) * ALGEBRAIC[XU] - CONSTANTS[ktm_unblock]  * pow(STATES[TRPN], (CONSTANTS[nperm] / 2)) * STATES[TmBlocked];
RATES[ZETAS] = CONSTANTS[A] * CONSTANTS[dlambda_dt] - ALGEBRAIC[cds] * STATES[ZETAS];
RATES[ZETAW] = CONSTANTS[A] * CONSTANTS[dlambda_dt] - ALGEBRAIC[cdw] * STATES[ZETAW];
RATES[dCd_dt] = ALGEBRAIC[v_C];

}

void Land_et_al_2016::solveAnalytical(double dt)
{
}

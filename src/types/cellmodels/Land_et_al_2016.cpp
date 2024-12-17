/*
   There are a total of 37+1 entries in the algebraic variable array.
   There are a total of 11 entries in each of the rate and state variable arrays.
   There are a total of 39 entries in the constant variable array.
 */

#include "Land_et_al_2016.hpp"
#include <cmath>
#include <cstdlib>

/*
 * TIME is time in component environment (second).
 * CONSTANTS[n_CaTRPN] is n_CaTRPN in component crossbridge_TRPN_parameters (dimensionless).
 * STATES[q_TRPN] is q_TRPN in component environment (fmol).
 * STATES[q_Ca_i] is q_Ca_i in component environment (fmol).
 * STATES[q_Ca_TRPN] is q_Ca_TRPN in component environment (fmol).
 * STATES[q_B_XB] is q_B_XB in component environment (fmol).
 * STATES[q_U_XB] is q_U_XB in component environment (fmol).
 * STATES[q_W_XB] is q_W_XB in component environment (fmol).
 * STATES[q_S_XB] is q_S_XB in component environment (fmol).
 * ALGEBRAIC[v_R_TRPNCa] is v_R_TRPNCa in component crossbridge_TRPN (fmol_per_sec).
 * ALGEBRAIC[v_R_BU] is v_R_BU in component crossbridge_TRPN (fmol_per_sec).
 * ALGEBRAIC[v_R_UW] is v_R_UW in component crossbridge_TRPN (fmol_per_sec).
 * ALGEBRAIC[v_R_WS] is v_R_WS in component crossbridge_TRPN (fmol_per_sec).
 * ALGEBRAIC[v_R_SU] is v_R_SU in component crossbridge_TRPN (fmol_per_sec).
 * ALGEBRAIC[T_total] is T_total in component crossbridge_TRPN (kPa).
 * STATES[SL] is SL in component crossbridge_TRPN (metre).
 * ALGEBRAIC[v_Ca_stim] is v_Ca_stim in component environment (fmol_per_sec).
 * CONSTANTS[BCL] is BCL in component environment (second).
 * CONSTANTS[duration] is duration in component environment (second).
 * ALGEBRAIC[tPeriod] is tPeriod in component environment (second).
 * ALGEBRAIC[dSL] is dSL in component environment (m_per_s).
 * CONSTANTS[V_max] is V_max in component environment (m_per_s).
 * CONSTANTS[kappa_R_TRPNCa] is kappa_R_TRPNCa in component crossbridge_TRPN_parameters (fmol_per_sec).
 * CONSTANTS[kappa_R_BU] is kappa_R_BU in component crossbridge_TRPN_parameters (fmol_per_sec).
 * CONSTANTS[kappa_R_UW] is kappa_R_UW in component crossbridge_TRPN_parameters (fmol_per_sec).
 * CONSTANTS[kappa_R_WS] is kappa_R_WS in component crossbridge_TRPN_parameters (fmol_per_sec).
 * CONSTANTS[kappa_R_SU] is kappa_R_SU in component crossbridge_TRPN_parameters (fmol_per_sec).
 * CONSTANTS[K_TRPN] is K_TRPN in component crossbridge_TRPN_parameters (per_fmol).
 * CONSTANTS[K_Ca_i] is K_Ca_i in component crossbridge_TRPN_parameters (per_fmol).
 * CONSTANTS[K_Ca_TRPN] is K_Ca_TRPN in component crossbridge_TRPN_parameters (per_fmol).
 * CONSTANTS[K_B_XB] is K_B_XB in component crossbridge_TRPN_parameters (per_fmol).
 * CONSTANTS[K_U_XB] is K_U_XB in component crossbridge_TRPN_parameters (per_fmol).
 * CONSTANTS[K_W_XB] is K_W_XB in component crossbridge_TRPN_parameters (per_fmol).
 * CONSTANTS[K_S_XB] is K_S_XB in component crossbridge_TRPN_parameters (per_fmol).
 * CONSTANTS[n_Tm] is n_Tm in component crossbridge_TRPN_parameters (dimensionless).
 * CONSTANTS[R] is R in component constants (J_per_K_per_mol).
 * CONSTANTS[T] is T in component constants (kelvin).
 * ALGEBRAIC[mu_TRPN] is mu_TRPN in component crossbridge_TRPN (J_per_mol).
 * ALGEBRAIC[mu_Ca_i] is mu_Ca_i in component crossbridge_TRPN (J_per_mol).
 * ALGEBRAIC[mu_Ca_TRPN] is mu_Ca_TRPN in component crossbridge_TRPN (J_per_mol).
 * ALGEBRAIC[mu_B_XB] is mu_B_XB in component crossbridge_TRPN (J_per_mol).
 * ALGEBRAIC[mu_U_XB] is mu_U_XB in component crossbridge_TRPN (J_per_mol).
 * ALGEBRAIC[mu_W_XB] is mu_W_XB in component crossbridge_TRPN (J_per_mol).
 * ALGEBRAIC[mu_S_XB] is mu_S_XB in component crossbridge_TRPN (J_per_mol).
 * CONSTANTS[SL_0] is SL_0 in component crossbridge_TRPN (metre).
 * CONSTANTS[q_MS] is q_MS in component crossbridge_TRPN (fmol).
 * CONSTANTS[r_s] is r_s in component crossbridge_TRPN (dimensionless).
 * CONSTANTS[r_w] is r_w in component crossbridge_TRPN (dimensionless).
 * CONSTANTS[A_eff] is A_eff in component crossbridge_TRPN (dimensionless).
 * CONSTANTS[phi] is phi in component crossbridge_TRPN (dimensionless).
 * CONSTANTS[k_uw] is k_uw in component crossbridge_TRPN (per_sec).
 * CONSTANTS[k_ws] is k_ws in component crossbridge_TRPN (per_sec).
 * STATES[G_w] is G_w in component crossbridge_TRPN (metre).
 * STATES[G_s] is G_s in component crossbridge_TRPN (metre).
 * CONSTANTS[c_w] is c_w in component crossbridge_TRPN (per_sec).
 * CONSTANTS[c_s] is c_s in component crossbridge_TRPN (per_sec).
 * CONSTANTS[A_w] is A_w in component crossbridge_TRPN (dimensionless).
 * CONSTANTS[A_s] is A_s in component crossbridge_TRPN (dimensionless).
 * ALGEBRAIC[nu_1] is nu_1 in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[nu_2] is nu_2 in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[nu_3] is nu_3 in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[nu_4] is nu_4 in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[nu_5] is nu_5 in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[nu_6] is nu_6 in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[v_1] is v_1 in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[v_2] is v_2 in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[v_4] is v_4 in component crossbridge_TRPN (m_per_s).
 * CONSTANTS[v_to_mu] is v_to_mu in component crossbridge_TRPN (Js_per_m2).
 * ALGEBRAIC[T_active] is T_active in component crossbridge_TRPN (kPa).
 * CONSTANTS[T_ref] is T_ref in component crossbridge_TRPN (kPa).
 * ALGEBRAIC[F_T_S] is F_T_S in component crossbridge_TRPN (kPa).
 * ALGEBRAIC[F_T_W] is F_T_W in component crossbridge_TRPN (kPa).
 * ALGEBRAIC[C_s] is C_s in component crossbridge_TRPN (metre).
 * STATES[C_d] is C_d in component crossbridge_TRPN (metre).
 * ALGEBRAIC[eta] is eta in component crossbridge_TRPN (second).
 * CONSTANTS[eta_l] is eta_l in component crossbridge_TRPN (second).
 * CONSTANTS[eta_s] is eta_s in component crossbridge_TRPN (second).
 * CONSTANTS[k] is k in component crossbridge_TRPN (dimensionless).
 * CONSTANTS[alpha] is alpha in component crossbridge_TRPN (kPa).
 * ALGEBRAIC[v_Cdd] is v_Cdd in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[nu_d] is nu_d in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[nu_k] is nu_k in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[nu_f] is nu_f in component crossbridge_TRPN (m_per_s).
 * ALGEBRAIC[F_d] is F_d in component crossbridge_TRPN (kPa).
 * ALGEBRAIC[F_1] is F_1 in component crossbridge_TRPN (kPa).
 * ALGEBRAIC[T_passive] is T_passive in component crossbridge_TRPN (kPa).
 * CONSTANTS[b] is b in component crossbridge_TRPN (dimensionless).
 * CONSTANTS[F] is F in component constants (C_per_mol).
 * RATES[q_Ca_i] is d/dt q_Ca_i in component environment (fmol).
 * RATES[q_TRPN] is d/dt q_TRPN in component environment (fmol).
 * RATES[q_Ca_TRPN] is d/dt q_Ca_TRPN in component environment (fmol).
 * RATES[q_B_XB] is d/dt q_B_XB in component environment (fmol).
 * RATES[q_U_XB] is d/dt q_U_XB in component environment (fmol).
 * RATES[q_W_XB] is d/dt q_W_XB in component environment (fmol).
 * RATES[q_S_XB] is d/dt q_S_XB in component environment (fmol).
 * RATES[G_w] is d/dt G_w in component crossbridge_TRPN (metre).
 * RATES[SL] is d/dt SL in component crossbridge_TRPN (metre).
 * RATES[G_s] is d/dt G_s in component crossbridge_TRPN (metre).
 * RATES[C_d] is d/dt C_d in component crossbridge_TRPN (metre).
 */


Land_et_al_2016::Land_et_al_2016()
{
algebraic_size = 37+1;
constants_size = 39;
states_size = 11;
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
CONSTANTS[n_CaTRPN] = 2;
STATES[q_TRPN] = 2.57;
STATES[q_Ca_i] = 6.82e-1;
STATES[q_Ca_TRPN] = 1e-6;
STATES[q_B_XB] = 1;
STATES[q_U_XB] = 0;
STATES[q_W_XB] = 0;
STATES[q_S_XB] = 0;
STATES[SL] = 2e-6;
CONSTANTS[BCL] = 1;
CONSTANTS[duration] = 0.001;
CONSTANTS[V_max] = 19e-6;
CONSTANTS[kappa_R_TRPNCa] = 22.8658;
CONSTANTS[kappa_R_BU] = 2.56831;
CONSTANTS[kappa_R_UW] = 0.338467;
CONSTANTS[kappa_R_WS] = 0.00796392;
CONSTANTS[kappa_R_SU] = 143351;
CONSTANTS[K_TRPN] = 0.428971;
CONSTANTS[K_Ca_i] = 6.33016;
CONSTANTS[K_Ca_TRPN] = 0.127132;
CONSTANTS[K_B_XB] = 5.95481;
CONSTANTS[K_U_XB] = 2.23305;
CONSTANTS[K_W_XB] = 14.6007;
CONSTANTS[K_S_XB] = 3.65018e-06;
CONSTANTS[n_Tm] = 1.1;
CONSTANTS[R] = 8.31;
CONSTANTS[T] = 310;
CONSTANTS[SL_0] = 2e-6;
CONSTANTS[q_MS] = 1e-6;
CONSTANTS[r_s] = 0.25;
CONSTANTS[r_w] = 0.5;
CONSTANTS[A_eff] = 25;
CONSTANTS[phi] = 2.23;
CONSTANTS[k_uw] = 26;
CONSTANTS[k_ws] = 4;
STATES[G_w] = 1e-6;
STATES[G_s] = 1e-6;
CONSTANTS[v_to_mu] = 1;
CONSTANTS[T_ref] = 40.5;
STATES[C_d] = 0;
CONSTANTS[eta_l] = 200e3;
CONSTANTS[eta_s] = 20e3;
CONSTANTS[k] = 7;
CONSTANTS[alpha] = 2.1;
CONSTANTS[b] = 9.1;
CONSTANTS[F] = 96485;
CONSTANTS[A_w] = ( CONSTANTS[A_eff]*CONSTANTS[r_s])/( (1.00000 - CONSTANTS[r_s])*CONSTANTS[r_w]+CONSTANTS[r_s]);
CONSTANTS[c_w] = ( CONSTANTS[phi]*CONSTANTS[k_uw]*(1.00000 - CONSTANTS[r_w]))/CONSTANTS[r_w];
CONSTANTS[c_s] = ( CONSTANTS[phi]*CONSTANTS[k_ws]*(1.00000 - CONSTANTS[r_s])*CONSTANTS[r_w])/CONSTANTS[r_s];
CONSTANTS[A_s] = CONSTANTS[A_w];
}


void Land_et_al_2016::computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC )
{
ALGEBRAIC[dSL] = (TIME<0.0600000 ?  1.00000*CONSTANTS[V_max] : TIME>0.500000&&TIME<0.560000 ?  - 1.00000*CONSTANTS[V_max] :  0.00000*CONSTANTS[V_max]);
ALGEBRAIC[v_2] = ALGEBRAIC[dSL];
ALGEBRAIC[mu_TRPN] =  CONSTANTS[R]*CONSTANTS[T]*log( CONSTANTS[K_TRPN]*STATES[q_TRPN]);
ALGEBRAIC[mu_Ca_i] =  CONSTANTS[R]*CONSTANTS[T]*log( CONSTANTS[K_Ca_i]*STATES[q_Ca_i]);
ALGEBRAIC[mu_Ca_TRPN] =  CONSTANTS[R]*CONSTANTS[T]*log( CONSTANTS[K_Ca_TRPN]*STATES[q_Ca_TRPN]);
ALGEBRAIC[v_R_TRPNCa] =  CONSTANTS[kappa_R_TRPNCa]*(exp(( CONSTANTS[n_CaTRPN]*ALGEBRAIC[mu_Ca_i]+ALGEBRAIC[mu_TRPN])/( CONSTANTS[R]*CONSTANTS[T])) - exp(ALGEBRAIC[mu_Ca_TRPN]/( CONSTANTS[R]*CONSTANTS[T])));
ALGEBRAIC[tPeriod] = TIME -  floor(TIME/CONSTANTS[BCL])*CONSTANTS[BCL];
ALGEBRAIC[v_Ca_stim] = (ALGEBRAIC[tPeriod]>=0.300000&&ALGEBRAIC[tPeriod]<=0.300000+CONSTANTS[duration] ?  1.00000*80.0000 : 0.00000);
ALGEBRAIC[nu_2] =  - CONSTANTS[A_w]*ALGEBRAIC[v_2];
ALGEBRAIC[nu_3] =  CONSTANTS[c_w]*STATES[G_w];
ALGEBRAIC[nu_1] = - ALGEBRAIC[nu_2] - ALGEBRAIC[nu_3];
ALGEBRAIC[v_1] = ALGEBRAIC[nu_1];
ALGEBRAIC[nu_5] =  - CONSTANTS[A_s]*ALGEBRAIC[v_2];
ALGEBRAIC[nu_6] =  CONSTANTS[c_s]*STATES[G_s];
ALGEBRAIC[nu_4] = - ALGEBRAIC[nu_5] - ALGEBRAIC[nu_6];
ALGEBRAIC[v_4] = ALGEBRAIC[nu_4];
ALGEBRAIC[C_s] = (STATES[SL] - CONSTANTS[SL_0]) - STATES[C_d];
ALGEBRAIC[eta] = (ALGEBRAIC[C_s]>0.00000 ? CONSTANTS[eta_l] : CONSTANTS[eta_s]);
ALGEBRAIC[v_Cdd] = ( CONSTANTS[k]*ALGEBRAIC[C_s])/ALGEBRAIC[eta];
ALGEBRAIC[mu_B_XB] =  CONSTANTS[R]*CONSTANTS[T]*log( CONSTANTS[K_B_XB]*STATES[q_B_XB]);
ALGEBRAIC[mu_U_XB] =  CONSTANTS[R]*CONSTANTS[T]*log( CONSTANTS[K_U_XB]*STATES[q_U_XB]);
ALGEBRAIC[v_R_BU] =  CONSTANTS[kappa_R_BU]*(exp((ALGEBRAIC[mu_B_XB]+ CONSTANTS[n_Tm]*ALGEBRAIC[mu_Ca_TRPN])/( CONSTANTS[R]*CONSTANTS[T])) - exp((ALGEBRAIC[mu_U_XB]+ CONSTANTS[n_Tm]*ALGEBRAIC[mu_Ca_TRPN])/( CONSTANTS[R]*CONSTANTS[T])));
ALGEBRAIC[mu_W_XB] =  CONSTANTS[R]*CONSTANTS[T]*log( CONSTANTS[K_W_XB]*STATES[q_W_XB]);
ALGEBRAIC[v_R_UW] =  CONSTANTS[kappa_R_UW]*(exp(ALGEBRAIC[mu_U_XB]/( CONSTANTS[R]*CONSTANTS[T])) - exp(ALGEBRAIC[mu_W_XB]/( CONSTANTS[R]*CONSTANTS[T])));
ALGEBRAIC[mu_S_XB] =  CONSTANTS[R]*CONSTANTS[T]*log( CONSTANTS[K_S_XB]*STATES[q_S_XB]);
ALGEBRAIC[v_R_WS] =  CONSTANTS[kappa_R_WS]*(exp(ALGEBRAIC[mu_W_XB]/( CONSTANTS[R]*CONSTANTS[T])) - exp(ALGEBRAIC[mu_S_XB]/( CONSTANTS[R]*CONSTANTS[T])));
ALGEBRAIC[v_R_SU] =  CONSTANTS[kappa_R_SU]*(exp(ALGEBRAIC[mu_S_XB]/( CONSTANTS[R]*CONSTANTS[T])) - exp(ALGEBRAIC[mu_U_XB]/( CONSTANTS[R]*CONSTANTS[T])));
ALGEBRAIC[F_T_S] =  (CONSTANTS[T_ref]/( CONSTANTS[SL_0]*CONSTANTS[q_MS]*CONSTANTS[r_s]))*STATES[q_S_XB]*(STATES[G_s]+CONSTANTS[SL_0]);
ALGEBRAIC[F_T_W] =  (CONSTANTS[T_ref]/( CONSTANTS[SL_0]*CONSTANTS[q_MS]*CONSTANTS[r_s]))*STATES[q_W_XB]*STATES[G_w];
ALGEBRAIC[T_active] = ALGEBRAIC[F_T_S]+ALGEBRAIC[F_T_W];
ALGEBRAIC[nu_k] =  (CONSTANTS[k]/ALGEBRAIC[eta])*STATES[C_d];
ALGEBRAIC[nu_f] =  (CONSTANTS[k]/ALGEBRAIC[eta])*(STATES[SL] - CONSTANTS[SL_0]);
ALGEBRAIC[lmbda] = STATES[SL]/CONSTANTS[SL_0];
ALGEBRAIC[F_1] =  CONSTANTS[alpha]*(exp(( CONSTANTS[b]*STATES[SL])/CONSTANTS[SL_0]) - 1.00000);
ALGEBRAIC[nu_d] = - ALGEBRAIC[nu_k]+ALGEBRAIC[nu_f];
ALGEBRAIC[F_d] =  (( CONSTANTS[alpha]*ALGEBRAIC[eta])/CONSTANTS[SL_0])*ALGEBRAIC[v_Cdd];
ALGEBRAIC[T_passive] = ALGEBRAIC[F_1]+ALGEBRAIC[F_d];
ALGEBRAIC[T_total] = ALGEBRAIC[T_active]+ALGEBRAIC[T_passive];

RATES[SL] = ALGEBRAIC[v_2];
RATES[q_Ca_i] =  - ALGEBRAIC[v_R_TRPNCa]*CONSTANTS[n_CaTRPN]+ALGEBRAIC[v_Ca_stim];
RATES[q_TRPN] = - ALGEBRAIC[v_R_TRPNCa];
RATES[q_Ca_TRPN] = ALGEBRAIC[v_R_TRPNCa];
RATES[G_w] = ALGEBRAIC[v_1];
RATES[G_s] = ALGEBRAIC[v_4];
RATES[C_d] = ALGEBRAIC[v_Cdd];
RATES[q_B_XB] = - ALGEBRAIC[v_R_BU];
RATES[q_W_XB] = ALGEBRAIC[v_R_UW] - ALGEBRAIC[v_R_WS];
RATES[q_U_XB] = (ALGEBRAIC[v_R_BU] - ALGEBRAIC[v_R_UW])+ALGEBRAIC[v_R_SU];
RATES[q_S_XB] = ALGEBRAIC[v_R_WS] - ALGEBRAIC[v_R_SU];
}

void Land_et_al_2016::solveAnalytical(double dt)
{
}

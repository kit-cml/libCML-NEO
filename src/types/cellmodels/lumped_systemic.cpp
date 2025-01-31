/*
   There are a total of 17 entries in the algebraic variable array.
   There are a total of 7 entries in each of the rate and state variable arrays.
   There are a total of 32 entries in the constant variable array.
 */

#include "lumped_systemic.hpp"
#include <cmath>
#include <cstdlib>
 
/*
 * TIME is t in component environment (second).
 * ALGEBRAIC[9] is Pi in component TempCDa (UnitP).
 * STATES[0] is Pi in component TempRLC (UnitP).
 * ALGEBRAIC[15] is Qo in component TempRC (UnitQ).
 * ALGEBRAIC[5] is Qo in component TempCDv (UnitQ).
 * ALGEBRAIC[3] is Pi in component TempCDv (UnitP).
 * ALGEBRAIC[11] is Qo in component TempCDa (UnitQ).
 * CONSTANTS[0] is CVao in component ParaLeftHeart (UnitCV).
 * ALGEBRAIC[2] is E in component EVentricle (UnitE).
 * STATES[1] is V in component TempCDv (UnitV).
 * CONSTANTS[1] is PlvIni in component ParaLeftHeart (UnitP).
 * CONSTANTS[2] is VlvIni in component ParaLeftHeart (UnitV).
 * ALGEBRAIC[4] is Tao in component TempCDv (dimensionless).
 * CONSTANTS[3] is Vlv0 in component ParaLeftHeart (UnitV).
 * CONSTANTS[4] is CVmi in component ParaLeftHeart (UnitCV).
 * ALGEBRAIC[8] is E in component EAtrium (UnitE).
 * STATES[2] is V in component TempCDa (UnitV).
 * CONSTANTS[5] is PlaIni in component ParaLeftHeart (UnitP).
 * CONSTANTS[6] is VlaIni in component ParaLeftHeart (UnitV).
 * ALGEBRAIC[10] is Tao in component TempCDa (dimensionless).
 * CONSTANTS[7] is Vla0 in component ParaLeftHeart (UnitV).
 * CONSTANTS[8] is ElvMax in component ParaLeftHeart (UnitE).
 * CONSTANTS[9] is ElvMin in component ParaLeftHeart (UnitE).
 * CONSTANTS[10] is T in component ParaLeftHeart (second).
 * CONSTANTS[11] is Ts1 in component ParaLeftHeart (dimensionless).
 * CONSTANTS[12] is Ts2 in component ParaLeftHeart (dimensionless).
 * ALGEBRAIC[0] is mt in component EVentricle (second).
 * ALGEBRAIC[1] is et in component EVentricle (dimensionless).
 * CONSTANTS[13] is ElaMax in component ParaLeftHeart (UnitE).
 * CONSTANTS[14] is ElaMin in component ParaLeftHeart (UnitE).
 * CONSTANTS[15] is Tpwb in component ParaLeftHeart (dimensionless).
 * CONSTANTS[16] is Tpww in component ParaLeftHeart (dimensionless).
 * ALGEBRAIC[6] is mt in component EAtrium (second).
 * ALGEBRAIC[7] is et in component EAtrium (dimensionless).
 * STATES[3] is Pi in component TempRLC (UnitP).
 * STATES[4] is Qo in component TempRLC (UnitQ).
 * CONSTANTS[17] is Rsas in component ParaSys (UnitR).
 * CONSTANTS[18] is Csas in component ParaSys (UnitC).
 * CONSTANTS[19] is Lsas in component ParaSys (UnitL).
 * CONSTANTS[20] is P0sas in component ParaSys (UnitP).
 * CONSTANTS[21] is Q0sas in component ParaSys (UnitQ).
 * ALGEBRAIC[16] is Pi in component TempR (UnitP).
 * STATES[5] is Qo in component TempRLC (UnitQ).
 * CONSTANTS[22] is Rsat in component ParaSys (UnitR).
 * CONSTANTS[23] is Csat in component ParaSys (UnitC).
 * CONSTANTS[24] is Lsat in component ParaSys (UnitL).
 * CONSTANTS[25] is P0sat in component ParaSys (UnitP).
 * CONSTANTS[26] is Q0sat in component ParaSys (UnitQ).
 * ALGEBRAIC[14] is Pi in component TempR (UnitP).
 * ALGEBRAIC[12] is Qo in component TempR (UnitQ).
 * CONSTANTS[27] is Rsar in component ParaSys (UnitR).
 * STATES[6] is Pi in component TempRC (UnitP).
 * ALGEBRAIC[13] is Qo in component TempR (UnitQ).
 * CONSTANTS[28] is Rscp in component ParaSys (UnitR).
 * CONSTANTS[29] is Rsvn in component ParaSys (UnitR).
 * CONSTANTS[30] is Csvn in component ParaSys (UnitC).
 * CONSTANTS[31] is P0svn in component ParaSys (UnitP).
 * RATES[1] is d/dt V in component TempCDv (UnitV).
 * RATES[2] is d/dt V in component TempCDa (UnitV).
 * RATES[0] is d/dt Pi in component TempRLC (UnitP).
 * RATES[4] is d/dt Qo in component TempRLC (UnitQ).
 * RATES[3] is d/dt Pi in component TempRLC (UnitP).
 * RATES[5] is d/dt Qo in component TempRLC (UnitQ).
 * RATES[6] is d/dt Pi in component TempRC (UnitP).
 */

lumped_systemic::lumped_systemic()
{
algebraic_size = 17;
constants_size = 32;
states_size = 7;
ALGEBRAIC = new double[algebraic_size];
CONSTANTS = new double[constants_size];
RATES = new double[states_size];
STATES = new double[states_size];
}

lumped_systemic::~lumped_systemic()
{
delete []ALGEBRAIC;
delete []CONSTANTS;
delete []RATES;
delete []STATES;
}

void lumped_systemic::initConsts()
{
CONSTANTS[0] = 350.;
CONSTANTS[1] = 1.0;
CONSTANTS[2] = 5.0;
CONSTANTS[3] = 500;
CONSTANTS[4] = 400.;
CONSTANTS[5] = 1.0;
CONSTANTS[6] = 4.0;
CONSTANTS[7] = 20;
CONSTANTS[8] = 2.5;
CONSTANTS[9] = 0.1;
CONSTANTS[10] = 1.0;
CONSTANTS[11] = 0.3;
CONSTANTS[12] = 0.45;
CONSTANTS[13] = 0.25;
CONSTANTS[14] = 0.15;
CONSTANTS[15] = 0.92;
CONSTANTS[16] = 0.09;
CONSTANTS[17] = 0.003;
CONSTANTS[18] = 0.08;
CONSTANTS[19] = 0.000062;
CONSTANTS[20] = 100.;
CONSTANTS[21] = 0.;
CONSTANTS[22] = 0.05;
CONSTANTS[23] = 1.6;
CONSTANTS[24] = 0.0017;
CONSTANTS[25] = 100.;
CONSTANTS[26] = 0.;
CONSTANTS[27] = 0.5;
CONSTANTS[28] = 0.52;
CONSTANTS[29] = 0.075;
CONSTANTS[30] = 20.5;
CONSTANTS[31] = 0.;
STATES[0] = CONSTANTS[20];
STATES[1] = CONSTANTS[3];
STATES[2] = CONSTANTS[7];
STATES[3] = CONSTANTS[25];
STATES[4] = CONSTANTS[21];
STATES[5] = CONSTANTS[26];
STATES[6] = CONSTANTS[31];
}


void lumped_systemic::computeRates( double TIME, double *CONSTANTS, double *RATES, double *STATES, double *ALGEBRAIC )
{
RATES[4] = ((STATES[0] - STATES[3]) -  CONSTANTS[17]*STATES[4])/CONSTANTS[19];
RATES[3] = (STATES[4] - STATES[5])/CONSTANTS[23];
ALGEBRAIC[0] = TIME -  CONSTANTS[10]*floor(TIME/CONSTANTS[10]);
ALGEBRAIC[1] = (ALGEBRAIC[0]>=0.00000&&ALGEBRAIC[0]<= CONSTANTS[11]*CONSTANTS[10] ? 1.00000 - cos(( 3.14159*ALGEBRAIC[0])/( CONSTANTS[11]*CONSTANTS[10])) : ALGEBRAIC[0]> CONSTANTS[11]*CONSTANTS[10]&&ALGEBRAIC[0]<= CONSTANTS[12]*CONSTANTS[10] ? 1.00000+cos(( 3.14159*(ALGEBRAIC[0] -  CONSTANTS[11]*CONSTANTS[10]))/( (CONSTANTS[12] - CONSTANTS[11])*CONSTANTS[10])) : ALGEBRAIC[0]> CONSTANTS[12]*CONSTANTS[10]&&ALGEBRAIC[0]<CONSTANTS[10] ? 0.00000 : 0.0/0.0);
ALGEBRAIC[2] = CONSTANTS[9]+( ALGEBRAIC[1]*(CONSTANTS[8] - CONSTANTS[9]))/2.00000;
ALGEBRAIC[3] = CONSTANTS[1]+ ALGEBRAIC[2]*(STATES[1] - CONSTANTS[2]);
ALGEBRAIC[4] = (ALGEBRAIC[3]>=STATES[0] ? 1.00000 : ALGEBRAIC[3]<STATES[0] ? 0.00000 : 0.0/0.0);
ALGEBRAIC[5] = (ALGEBRAIC[3]>=STATES[0] ?  CONSTANTS[0]*ALGEBRAIC[4]*pow(fabs(ALGEBRAIC[3] - STATES[0]), 0.500000) : ALGEBRAIC[3]<STATES[0] ?  -1.00000*CONSTANTS[0]*ALGEBRAIC[4]*pow(fabs(STATES[0] - ALGEBRAIC[3]), 0.500000) : 0.0/0.0);
RATES[0] = (ALGEBRAIC[5] - STATES[4])/CONSTANTS[18];
ALGEBRAIC[6] = TIME -  CONSTANTS[10]*floor(TIME/CONSTANTS[10]);
ALGEBRAIC[7] = (ALGEBRAIC[6]>=0.00000&&ALGEBRAIC[6]<= ((CONSTANTS[15]+CONSTANTS[16]) - 1.00000)*CONSTANTS[10] ? 1.00000 - cos(( 2.00000*3.14159*(ALGEBRAIC[6] -  (CONSTANTS[15] - 1.00000)*CONSTANTS[10]))/( CONSTANTS[16]*CONSTANTS[10])) : ALGEBRAIC[6]> ((CONSTANTS[15]+CONSTANTS[16]) - 1.00000)*CONSTANTS[10]&&ALGEBRAIC[6]<= CONSTANTS[15]*CONSTANTS[10] ? 0.00000 : ALGEBRAIC[6]> CONSTANTS[15]*CONSTANTS[10]&&ALGEBRAIC[6]<=CONSTANTS[10] ? 1.00000 - cos(( 2.00000*3.14159*(ALGEBRAIC[6] -  CONSTANTS[15]*CONSTANTS[10]))/( CONSTANTS[16]*CONSTANTS[10])) : 0.0/0.0);
ALGEBRAIC[8] = CONSTANTS[14]+( ALGEBRAIC[7]*(CONSTANTS[13] - CONSTANTS[14]))/2.00000;
ALGEBRAIC[9] = CONSTANTS[5]+ ALGEBRAIC[8]*(STATES[2] - CONSTANTS[6]);
ALGEBRAIC[10] = (ALGEBRAIC[9]>=ALGEBRAIC[3] ? 1.00000 : ALGEBRAIC[9]<ALGEBRAIC[3] ? 0.00000 : 0.0/0.0);
ALGEBRAIC[11] = (ALGEBRAIC[9]>=ALGEBRAIC[3] ?  CONSTANTS[4]*ALGEBRAIC[10]*pow(fabs(ALGEBRAIC[9] - ALGEBRAIC[3]), 0.500000) : ALGEBRAIC[9]<ALGEBRAIC[3] ?  -1.00000*CONSTANTS[4]*ALGEBRAIC[10]*pow(fabs(ALGEBRAIC[3] - ALGEBRAIC[9]), 0.500000) : 0.0/0.0);
RATES[1] = ALGEBRAIC[11] - ALGEBRAIC[5];
ALGEBRAIC[15] = (STATES[6] - ALGEBRAIC[9])/CONSTANTS[29];
RATES[2] = ALGEBRAIC[15] - ALGEBRAIC[11];
ALGEBRAIC[12] = STATES[5];
ALGEBRAIC[14] = STATES[6]+ CONSTANTS[28]*ALGEBRAIC[12];
ALGEBRAIC[16] = ALGEBRAIC[14]+ CONSTANTS[27]*STATES[5];
RATES[5] = ((STATES[3] - ALGEBRAIC[16]) -  CONSTANTS[22]*STATES[5])/CONSTANTS[24];
ALGEBRAIC[13] = ALGEBRAIC[12];
RATES[6] = (ALGEBRAIC[13] - ALGEBRAIC[15])/CONSTANTS[30];
}

void lumped_systemic::solveAnalytical(double dt)
{
}

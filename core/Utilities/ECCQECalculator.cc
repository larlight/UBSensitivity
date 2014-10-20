#ifndef ECCQECALCULATOR_CC
#define ECCQECALCULATOR_CC

#include "ECCQECalculator.hh"
namespace ubsens{
  namespace util{

    double ECCQECalculator::ComputeECCQE(double E_lept, double U_z){
      
      double M_n = 939.565;    // MeV/c2
      double M_p = 938.272;    // MeV/c2
      double M_e = 0.511;      // MeV/c2
      double E_b = 30;         // MeV (binding energy)
            
      double numerator = pow(M_p,2) - pow((M_n-E_b),2) - pow(M_e,2) + 2*(M_n-E_b)*E_lept;
      double denominator = 2*( M_n - E_b - E_lept + U_z*pow(pow(E_lept,2) - pow(M_e,2),0.5) );
	
      return (numerator/denominator);
    }

  }// end namespace util
}// end namespace ubsens  
#endif

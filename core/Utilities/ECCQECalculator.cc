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

    double ECCQECalculator::ComputeECCQE(const std::vector<double> &lepton_momentum){

      double l_energy = lepton_momentum.at(3);
      return ComputeECCQE(l_energy,lepton_momentum);

    }

    double ECCQECalculator::ComputeECCQE(double energy, const std::vector<double> &lepton_momentum){

      if ( lepton_momentum.size() != 4 ){
	std::cerr << "From ComputeECCQE: input 4-momentum doesn't have size 4! Quitting..."<<std::endl;
	return -99.;
      }

      ///.at(0) is x momentum in MeV/C
      ///.at(3) is total energy [ == (x^2 + y^2 + z^2 )^0.5 ]

      double M_n = 939.565;    // MeV/c2
      double M_p = 938.272;    // MeV/c2
      double M_e = 0.511;      // MeV/c2
      double bindingE = 30.0;  // MeV

      double l_energy = energy;
      double l_mom = pow(pow(l_energy,2) - pow(M_e,2), 0.5);

      // Only truth info goes into theta calculation
      double l_theta = 
	TMath::ACos(lepton_momentum.at(2)/
		    pow(
		      (
			pow(lepton_momentum.at(0),2)+
			pow(lepton_momentum.at(1),2)+
			pow(lepton_momentum.at(2),2)
		      ), 0.5
		    )
	);

      double nu_energy_num = pow(M_p,2) - pow(M_n - bindingE,2)
        - pow(M_e,2) + 2.0*(M_n - bindingE)*l_energy;
      double nu_energy_den = 2.0*(M_n - bindingE - l_energy + l_mom*TMath::Cos(l_theta));
      
      return nu_energy_num/nu_energy_den;

    }

  }// end namespace util
}// end namespace ubsens  
#endif

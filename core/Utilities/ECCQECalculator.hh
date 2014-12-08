/**
 * \file ECCQECalculator.hh
 *
 * \ingroup Utilities
 * 
 * \brief A static function to calculate CCQE energy.
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef ECCQECALCULATOR_HH
#define ECCQECALCULATOR_HH

#include <vector>
#include <iostream>
#include <math.h> //pow
#include "TMath.h"

/**
   \class ECCQECalculator
   A static function to calculate CCQE energy.
 */
namespace ubsens{
  namespace util{

    class ECCQECalculator{
      
    public:
      
      /// Default constructor
      ECCQECalculator(){};
      
      /// Default destructor
      virtual ~ECCQECalculator(){};
      
      static double ComputeECCQE(double E_lept, double U_z);

      /// Method using only truth momentum 4-vector (wrapper)
      static double ComputeECCQE(const std::vector<double> &lepton_momentum);
      

      /// Method using manually-input energy (IE if you smear energy first)
      static double ComputeECCQE(double energy, const std::vector<double> &lepton_momentum);

    };
  }// end namespace util
}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


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

#include <math.h> //pow

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
    };
  }// end namespace util
}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


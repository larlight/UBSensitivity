/**
 * \file ECCQECalculator.hh
 *
 * \ingroup Utilities
 * 
 * \brief Class def header for a class ECCQECalculator
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef ECCQECALCULATOR_HH
#define ECCQECALCULATOR_HH

#include <iostream>
#include <math.h> //pow
/**
   \class ECCQECalculator
   User defined class ECCQECalculator ... these comments are used to generate
   doxygen documentation!
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


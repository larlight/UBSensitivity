/**
 * \file POTScaling.hh
 *
 * \ingroup LEE
 * 
 * \brief Class def header for a class POTScaling
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef POTSCALING_HH
#define POTSCALING_HH

#include <iostream>
#include "Constants/UBOscConstants.h"
/**
   \class POTScaling
   User defined class POTScaling ... these comments are used to generate
   doxygen documentation!
 */
class POTScaling{

public:

  /// Default constructor
  POTScaling(){
    _MINIBOONE_POT = 0.;
    _my_POT = 0.;
  };

  /// Default destructor
  virtual ~POTScaling(){};
  
  void SetMINIBOONEPOT(double input_param){ _MINIBOONE_POT = input_param; }

  void SetMyPOT(double input_param){ _my_POT = input_param; }

  double GetPOTScaling();
  
protected:

  //the POT that miniboone used
  double _MINIBOONE_POT;

  //the POT you want to look at in your detector
  double _my_POT;

};

#endif
/** @} */ // end of doxygen group 


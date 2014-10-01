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
#include "Constants/DataConstants.h"
/**
   \class POTScaling
   User defined class POTScaling ... these comments are used to generate
   doxygen documentation!
 */
class POTScaling{

public:

  /// Default constructor
  POTScaling(){
    _MINIBOONE_POT = DATA::MINIBOONE_POT_DEFAULT;
    _my_POT = DATA::UB_POT_DEFAULT;
  };

  /// Default destructor
  virtual ~POTScaling(){};
  
  //optional, else default 6.46 is used
  void SetMINIBOONEPOT(double input_param){ _MINIBOONE_POT = input_param; }

  //optional, else default 6.6 is used (microboone)
  void SetMyPOT(double input_param){ _my_POT = input_param; }

  double GetPOTScaling() { return _my_POT/_MINIBOONE_POT; };
  
protected:

  //the POT that miniboone used, default 6.46
  double _MINIBOONE_POT;

  //the POT you want to look at in your detector
  double _my_POT;

};

#endif
/** @} */ // end of doxygen group 


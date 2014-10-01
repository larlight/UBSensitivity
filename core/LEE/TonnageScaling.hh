/**
 * \file TonnageScaling.hh
 *
 * \ingroup LEE
 * 
 * \brief Class def header for a class TonnageScaling
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef TONNAGESCALING_HH
#define TONNAGESCALING_HH

#include <iostream>
#include <TMath.h>

/**
   \class TonnageScaling
   User defined class TonnageScaling ... these comments are used to generate
   doxygen documentation!
 */
class TonnageScaling{

public:

  /// Default constructor
  TonnageScaling(){
    _my_tonnage = 0;
  };

  /// Default destructor
  virtual ~TonnageScaling(){};

  //note: make data enums for different detectors
  void SetMyDetector(std::string input_param) { _my_Detector = input_param; }

  //optional to manually set the tonnage of your detector
  void SetMyTonnage(double input_param){ _my_tonnage = input_param; }

  double GetTonnageScaling();

protected:

  double _my_tonnage;
  
  std::string _my_Detector;


};

#endif
/** @} */ // end of doxygen group 


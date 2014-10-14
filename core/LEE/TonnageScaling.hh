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
#include <sstream>
#include "LEEException.hh"
#include "Constants/GeometryConstants.hh"

/**
   \class TonnageScaling
   User defined class TonnageScaling ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens{
  
  class TonnageScaling{
    
  public:
    
    /// Default constructor
    TonnageScaling(){
      _my_Detector = geo::kNULLDetector;
      _my_tonnage = 0.;   
      _classname = "TonnageScaling";
    };
    
    /// Default destructor
    virtual ~TonnageScaling(){};
    
    //note: make data enums for different detectors
    void SetMyDetector(geo::Detector_t mydet) { _my_Detector = mydet; }
    
    //optional to manually set the tonnage of your detector
    void SetMyTonnage(double input_param){ _my_tonnage = input_param; }
    
    double GetTonnageScaling();
    
  protected:
    
    double _my_tonnage;
    
    geo::Detector_t _my_Detector;

    std::string _classname;
  };
  
}//end namespace ubsens

#endif
/** @} */ // end of doxygen group 


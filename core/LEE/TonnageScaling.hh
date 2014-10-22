/**
 * \file TonnageScaling.hh
 *
 * \ingroup LEE
 * 
 * \brief Simple class to handle tonnage scaling.
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef TONNAGESCALING_HH
#define TONNAGESCALING_HH

#include "LEEBase.hh"
#include "Constants/GeometryConstants.hh"
#include "Utilities/FindInMapMap.hh"

/**
   \class TonnageScaling
   Simple class to handle tonnage scaling.
 */

namespace ubsens{
  
  class TonnageScaling : public LEEBase{
    
  public:
    
    /// Default constructor
    TonnageScaling(){
      _my_Detector = geo::kNULLDetector;
      _my_tonnage = 0.;   
      _my_Detector_string = "";
      _name = "TonnageScaling";
    };
    
    /// Inherited configure function from LEEBase
    virtual bool Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap);


    /// Default destructor
    virtual ~TonnageScaling(){};
    
    //note: make data enums for different detectors
    void SetMyDetector(geo::Detector_t mydet) { _my_Detector = mydet; }
    
    //optional to manually set the tonnage of your detector
    void SetMyTonnage(double input_param){ _my_tonnage = input_param; }
    
    double GetTonnageScaling();
    
  private:
    
    double _my_tonnage;
    
    std::string _my_Detector_string;
    
    geo::Detector_t _my_Detector;

  };
  
}//end namespace ubsens

#endif
/** @} */ // end of doxygen group 


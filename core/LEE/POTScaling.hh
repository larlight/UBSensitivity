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
#include "LEEBase.hh"
#include "Constants/POTConstants.hh"
#include "Utilities/FindInMapMap.hh"
/**
   \class POTScaling
   User defined class POTScaling ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens{
  
  class POTScaling : public LEEBase{
    
  public:
    
    /// Default constructor
    POTScaling(){
      _MINIBOONE_POT = pot::MINIBOONE_POT_DEFAULT;
      _my_POT = pot::UB_POT_DEFAULT;
      _name = "POTScaling";
      _MINIBOONE_POT_string = "";
      _my_POT_string = "";
    };

    /// Inherited configure function from LEEBase
    virtual bool Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap);
    
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

    std::string _MINIBOONE_POT_string;
    std::string _my_POT_string;
  };
  
}//end namespace ubsens

#endif
  /** @} */ // end of doxygen group 
  

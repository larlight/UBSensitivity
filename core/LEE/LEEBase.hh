/**
 * \file LEEBase.hh
 *
 * \ingroup LEE
 * 
 * \brief Class def header for a class LEEBase
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef LEEBASE_HH
#define LEEBASE_HH

#include <iostream>
#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/Message.hh"
#include "FMWKBase/FMWKException.hh"
#include <map>
#include "TGraph.h"


/**
   \class LEEBase
   User defined class LEEBase ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{

  class LEEBase : public ::ubsens::fmwk::FMWKBase{
    
  public:
    
    /// Default constructor
    LEEBase(){ _name="LEEBase"; };
    
    /// Default destructor
    virtual ~LEEBase(){};
    
    /// Function to configure
    virtual bool Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap){ return false; }
    
  };

}// end namespace ubsens

#endif
/** @} */ // end of doxygen group 


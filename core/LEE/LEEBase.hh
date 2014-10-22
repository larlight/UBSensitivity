/**
 * \file LEEBase.hh
 *
 * \ingroup LEE
 * 
 * \brief Base class for LEE modules. Holds a Configure function that all modules will inherit to grab their specific configuration parameters from the ConfigManager (configuration files). Also has WritePlots function that will be inherited by modules, telling them to hand off their relevant plots to PlotWriter for writing to the output file.
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef LEEBASE_HH
#define LEEBASE_HH

#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/FMWKException.hh"
#include <map>


/**
   \class LEEBase
   Base class for LEE modules. Holds a Configure function that all modules will inherit to grab their specific configuration parameters from the ConfigManager (configuration files). Also has WritePlots function that will be inherited by modules, telling them to hand off their relevant plots to PlotWriter for writing to the output file.
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
    
    /// Function to write relevant plots (histos, tgraphs) to shared out file
    virtual void WritePlots(){};
    
  };

}// end namespace ubsens

#endif
/** @} */ // end of doxygen group 


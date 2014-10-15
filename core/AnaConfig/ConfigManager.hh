/**
 * \file ConfigManager.hh
 *
 * \ingroup AnaConfig
 * 
 * \brief Class def header for a class ConfigManager
 *
 * @author davidkaleko
 */

/** \addtogroup AnaConfig

    @{*/
#ifndef CONFIGMANAGER_HH
#define CONFIGMANAGER_HH

#include <iostream>
#include <sstream>
#include <map>
#include "ConfigReader.hh"
#include "ConfigConstants.hh"
#include "FMWKBase/Message.hh"

/**
   \class ConfigManager
   User defined class ConfigManager ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens{

  namespace config{
    
    class ConfigManager{
      
    public:
      /// Default constructor
      ConfigManager(){
	_classname = "ConfigManager";
      };
      
      /// Default destructor
      virtual ~ConfigManager(){};

      /// Function to read in the config file
      bool LoadConfig(std::string filename);

      /// Main function: module asks ConfigManager for a parameter
      /// that ConfigManager has read in from input config file
      std::string GetParam(MODULE_TYPE_t module, std::string param_name);

      void Reset();
      
    protected:
      
      ::ubsens::config::ConfigReader _cr;

      std::map<std::string,std::map<std::string,std::string> > _map;

    private:
      
      ::ubsens::fmwk::Message fMsg;

      std::string _classname;
    };

  }// end namespace config

}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


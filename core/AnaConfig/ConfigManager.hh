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
#include <map>
#include "ConfigReader.hh"
#include "ConfigConstants.hh"
#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/Message.hh"

/**
   \class ConfigManager
   User defined class ConfigManager ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens{

  namespace config{
    
    class ConfigManager : public ::ubsens::fmwk::FMWKBase{
      
    public:
      /// Default constructor
      ConfigManager(){
	_name = "ConfigManager";
	_config_loaded = false;
      };
      
      /// Default destructor
      virtual ~ConfigManager(){};

      /// Function to read in the config file
      bool LoadConfig(std::string filename);

      /// Main function: module asks ConfigManager for a parameter
      /// that ConfigManager has read in from input config file
      std::string GetParam(MODULE_TYPE_t module, std::string param_name);

      /// Getter function for the configuration mapping.
      /// Note: individule modules shouldn't know ConfigManager exists,
      /// they should be handed their configurations by whoever owns
      /// ConfigManager (IE the event loop+plotting script)
      const std::map<std::string,std::map<std::string,std::string>> & GetConfigMap()
      {	return _map; }

      void Reset();
      
      void DebugDump() { _cr.Dump(); }

    protected:
      
      ::ubsens::config::ConfigReader _cr;

      //Map of module name --> < parameter name --> parameter value >
      std::map<std::string,std::map<std::string,std::string> > _map;

    private:

      bool _config_loaded;
      
      ::ubsens::fmwk::Message fMsg;

    };

  }// end namespace config

}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 

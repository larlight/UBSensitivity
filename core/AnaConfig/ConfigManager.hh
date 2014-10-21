/**
 * \file ConfigManager.hh
 *
 * \ingroup AnaConfig
 * 
 * \brief Manager class to handle configuration scripts. Talks to ConfigReader to read in the text file and creates a std::map to handle it. This map is handed to each module, which is in charge of searching through it to grab any configuration parameters relevant to that module.
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
#include "Utilities/PlotWriter.hh"
#include "time.h"

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
	_saved_configfilename = "";
      };
      
      /// Default destructor
      virtual ~ConfigManager(){};

      /// Function to read in the config file
      bool LoadConfig(std::string filename);

      /// Function that copies contents of the configuration file 
      /// into the output file (along with all the plots, graphs, etc)
      /// The purpose is to have one self-describing output file that
      /// contains all relevant information. Don't need to save and
      /// keep track of all the input configuration files.
      void SaveConfig();

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
      
      std::string _saved_configfilename;

      ::ubsens::fmwk::Message fMsg;

    };

  }// end namespace config

}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


/**
 * \file ConfigReader.hh
 *
 * \ingroup AnaConfig
 * 
 * \brief Class to read in a specially formatted text file (see sample.config) and parse it into a std::map, which it hands to ConfigManager
 *
 * @author davidkaleko
 */

/** \addtogroup AnaConfig

    @{*/
#ifndef CONFIGREADER_HH
#define CONFIGREADER_HH

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm> //std::find
#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/FMWKException.hh"
#include "ConfigConstants.hh"

/**
   \class ConfigReader
   User defined class ConfigReader ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{

  namespace config{

    class ConfigReader : public ::ubsens::fmwk::FMWKBase{
      
    public:
      
      /// Default constructor
      ConfigReader()
      {
	_in_filename = "";
	_name = "ConfigReader";
      }
      
      /// Default destructor
      virtual ~ConfigReader(){};

      /// Set the input configuration filename
      bool SetConfigFile(std::string f);

      /// Function to read in the input file
      bool Read();

      /// Function to reset filename, clear _map, etc
      void Reset();

      /// Debug function to dump contents of _map
      void Dump();

      /// Utility function to loop through ConfiConstants::Module list and see
      /// if "mystring" is in the list of names anywhere.
      bool IsInModuleList(std::string mystring);

      /// Function to grab the configuration map
      std::map<std::string,std::map<std::string,std::string> > GetMap(){ return _map; }

  protected:
      
      std::string _in_filename;
      
      /// Map of module name --> (variable name --> variable value)
      std::map<std::string,std::map<std::string,std::string> > _map;

    };

  }// end namespace config

}// end namespace ubsens
#endif
    /** @} */ // end of doxygen group 
    

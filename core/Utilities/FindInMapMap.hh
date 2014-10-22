/**
 * \file FindInMapMap.hh
 *
 * \ingroup Utilities
 * 
 * \brief Class takes in const pointer to map<string,map<string,string>>
 * (the map is modulename --> map<parametername --> paramvalue> )
 * and a module name, and a parameter name.
 * it greps the map for the module and parameter, and returns the value
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef FINDINMAPMAP_HH
#define FINDINMAPMAP_HH

#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/FMWKException.hh"
#include <map>

/**
   \class FindInMapMap
   Class takes in const pointer to map<string,map<string,string>>
   (the map is modulename --> map<parametername --> paramvalue> )
   and a module name, and a parameter name.
   it greps the map for the module and parameter, and returns the value
*/
namespace ubsens{

  namespace util{
    
    class FindInMapMap : public ::ubsens::fmwk::FMWKBase {
      
    public:
      
      /// Default constructor
      FindInMapMap(){ _name = "FindInMapMap"; };
      
      /// Default destructor
      virtual ~FindInMapMap(){};
      
      std::string GetParamValue(std::string key1,
				std::string key2,
				const std::map<std::string,std::map<std::string,std::string>> &_map);

    };
  }//end namespace util
}//end namespace ubsens
#endif
/** @} */ // end of doxygen group 


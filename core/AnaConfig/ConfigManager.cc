#ifndef CONFIGMANAGER_CC
#define CONFIGMANAGER_CC

#include "ConfigManager.hh"

namespace ubsens{

  namespace config{

    bool ConfigManager::LoadConfig(std::string filename){
     
      Reset();
      
      _cr.Reset();


      try{
	_cr.SetConfigFile(filename);
      }
      catch (AnaConfigException &e) {
	fMsg.send(::ubsens::fmwk::msg::kERROR,e.what());
      }
  
  
      
      _cr.Read();

      _map = _cr.GetMap();
      
      return true;

    }

    std::string ConfigManager::GetParam(MODULE_TYPE_t module, std::string param_name){

      //this function loops thru map and finds parameter
      std::string blah;
      blah = "davidkaleko";
      return blah;
    }

    void ConfigManager::Reset(){

      _map.clear();

    }
  }

}
#endif

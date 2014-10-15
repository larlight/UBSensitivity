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
	_cr.Read();      
      }
      catch (::ubsens::fmwk::FMWKException &e) {
	fMsg.send(::ubsens::fmwk::msg::kERROR,e.what());
      }
  
      _map = _cr.GetMap();
      
      return true;

    }

    void ConfigManager::Reset(){

      _map.clear();

    }
  }

}
#endif

#ifndef POTSCALING_CC
#define POTSCALING_CC

#include "POTScaling.hh"

namespace ubsens{

  bool POTScaling::Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap){
        
        
    try{
      _my_POT_string = util::FindInMapMap().GetParamValue(class_name(),std::string("MyPOT"),_configMap);
      _MINIBOONE_POT_string = util::FindInMapMap().GetParamValue(class_name(),std::string("MBPOT"),_configMap);
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kEXCEPTION, __FUNCTION__, e.what());
    }
   
    //If the config file has blank lines, use defaults
    if(_my_POT_string.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _my_POT_string.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _my_POT_string = "6.6";
    }
    if(_MINIBOONE_POT_string.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _MINIBOONE_POT_string.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _MINIBOONE_POT_string = "6.46";
    }

    //Convert _my_*_string into a actual POTs
    _my_POT = atof(_my_POT_string.c_str());
    _MINIBOONE_POT = atof(_MINIBOONE_POT_string.c_str());
      
    return true;
    
  }


}//end namespace ubsens

#endif

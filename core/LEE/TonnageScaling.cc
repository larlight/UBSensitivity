#ifndef TONNAGESCALING_CC
#define TONNAGESCALING_CC

#include "TonnageScaling.hh"

namespace ubsens {

  bool TonnageScaling::Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap){
        
    try{
      _my_Detector_string = util::FindInMapMap().GetParamValue(class_name(),std::string("MyDetector"),_configMap);
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kEXCEPTION, __FUNCTION__, e.what());
    }
   
    //If the config file has blank lines, use defaults
    if(_my_Detector_string.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _my_Detector_string.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _my_Detector_string = "MicroBooNE";
    }

    //Convert _my_Detector_string into an actual detector
    if(std::strcmp(_my_Detector_string.c_str(),"MicroBooNE")==0)
      _my_Detector = geo::kMicroBooNE;
    else if(std::strcmp(_my_Detector_string.c_str(),"LAr1")==0)
      _my_Detector = geo::kLAr1;
    else{
      std::string msg = "";
      msg += "You chose a bad detector! Rewrite your config file and try again.";
      fMsg.send(::ubsens::fmwk::msg::kERROR, __FUNCTION__, msg);
      return false;
    }
      
    return true;
  };


  double TonnageScaling::GetTonnageScaling(){
    
    //if the user has manually set tonnage, skip all this
    if( !_my_tonnage ){
      
      //if the user has set the detector they want to use
      if(_my_Detector == geo::kNULLDetector){
	std::string msg = "";
	msg += "Note your detector is still set to kNULLDetector. Something might have gone awry... I'm assuming you meant MicroBooNE tonnage.";
	fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
	_my_tonnage = geo::UB_TONNAGE_GRAMS;
      }
      else if(_my_Detector == geo::kMicroBooNE)
	_my_tonnage = geo::UB_TONNAGE_GRAMS;
      else{
	std::ostringstream msg;
	msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	    << "ERROR: You set the detector to something I dunno the tonnage for. Better fix this yourself."
	    << std::endl;
	throw fmwk::FMWKException(msg.str());
      }
      
    }
    
    return (_my_tonnage / geo::MINIBOONE_TONNAGE_GRAMS);
  }

}//end namespace ubsens
#endif

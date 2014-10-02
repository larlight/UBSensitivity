#ifndef TONNAGESCALING_CC
#define TONNAGESCALING_CC

#include "TonnageScaling.hh"

namespace ubsens {

  double TonnageScaling::GetTonnageScaling(){
    
    //if the user has manually set tonnage, skip all this
    if( !_my_tonnage ){
      
      //if the user has set the detector they want to use
      if(_my_Detector == GEOCONSTANTS::kNULLDetector){
	std::cerr<<"Ruh roh. You need to either manually set tonnage, or set the detector to something I recognize. Assuming you're using MicroBooNE..."<<std::endl;
	_my_tonnage = GEOCONSTANTS::UB_TONNAGE_GRAMS;
      }
      else if(_my_Detector == GEOCONSTANTS::kMicroBooNE)
	_my_tonnage = GEOCONSTANTS::UB_TONNAGE_GRAMS;
      else{
	std::cerr<<"You set the detector to something I dunno the tonnage for. Better fix this yourself."<<std::endl;
      }
      
    }
    
    return (_my_tonnage / GEOCONSTANTS::MINIBOONE_TONNAGE_GRAMS);
  }

}//end namespace ubsens
#endif

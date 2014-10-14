#ifndef TONNAGESCALING_CC
#define TONNAGESCALING_CC

#include "TonnageScaling.hh"

namespace ubsens {

  double TonnageScaling::GetTonnageScaling(){
    
    //if the user has manually set tonnage, skip all this
    if( !_my_tonnage ){
      
      //if the user has set the detector they want to use
      if(_my_Detector == geo::kNULLDetector){
	std::cout<<"WARNING: You need to either manually set tonnage, or set the detector. For now, I'll assume you're using MicroBooNE..."<<std::endl;
	_my_tonnage = geo::UB_TONNAGE_GRAMS;
      }
      else if(_my_Detector == geo::kMicroBooNE)
	_my_tonnage = geo::UB_TONNAGE_GRAMS;
      else{
	std::ostringstream msg;
	msg << "<<" << _classname << "::" << __FUNCTION__ << ">> "
	    << "ERROR: You set the detector to something I dunno the tonnage for. Better fix this yourself."
	    << std::endl;
	throw LEEException(msg.str());
      }
      
    }
    
    return (_my_tonnage / geo::MINIBOONE_TONNAGE_GRAMS);
  }

}//end namespace ubsens
#endif

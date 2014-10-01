#ifndef POTSCALING_CC
#define POTSCALING_CC

#include "POTScaling.hh"

double POTScaling::GetPOTScaling(){
  
  if( _MINIBOONE_POT == 0 || _my_POT == 0){
    std::cerr<<"MINIBOONE or my POT not set! Set them!"<<std::endl;
    return -1.;
  }

  return _MINIBOONE_POT/_my_POT;
  
}


#endif

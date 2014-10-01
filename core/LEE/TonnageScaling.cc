#ifndef TONNAGESCALING_CC
#define TONNAGESCALING_CC

#include "TonnageScaling.hh"


double TonnageScaling::GetTonnageScaling(){

  //if the user has set the detector they want to use
  if(!_my_Detector.empty()){
    
    if(!_my_tonnage)
      std::cerr<<"You manually set the tonnage. Why are you setting the detector?!"<<std::endl;

    if(_my_Detector == "UB"){
      //volume in cm^3. use total volume, not fiducial... 
      //fid vol is taken into account when you apply efficiency cuts
      //this is a data constant, should be stored somewhere
      double Vol_UB = 3.14159 * pow(190.,2) * 1079.;
      double LAr_Density = 1.3954;      
      _my_tonnage = LAr_Density * Vol_UB;
    }
    else
      std::cerr<<"You need to set the detector to something I recognize... like \"UB\"!"<<std::endl;
    
  }
  
  double Vol_MINIBOONE =(4/3) * 3.14159 * pow(610.6,3);
  double MINIBOONE_Density = 0.855;
  double MINIBOONE_tonnage = MINIBOONE_Density * Vol_MINIBOONE;

  return (_my_tonnage / MINIBOONE_tonnage);
}
#endif

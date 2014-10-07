#ifndef GEOMETRYCONSTANTS_H
#define GEOMETRYCONSTANTS_H

namespace ubsens {

  namespace geo {
    
    enum Detector_t {
      kNULLDetector, //null detector (initialization value)
      kMicroBooNE,   //microboone
      kMiniBooNE,    //miniboone
      kLAr1,         //have you figured out the pattern yet?
      kDetectorMax
    };
    
    //microboone tonnage (total) in grams
    //from 1.3954 [g/cm^3] * pi * 190^2 * 1079 [cm^3]
    static const double UB_TONNAGE_GRAMS = 170756353.192;
    
    //miniboone tonnage (total) in grams
    //from 0.855 [g/cm^3] * (4/3) * pi * 610.6^3 [cm^3]
    static const double MINIBOONE_TONNAGE_GRAMS = 815313732.1;
    
    //number of argon atoms per gram (in units of avogadro's #)
    // 1/39.948 = 0.0250325
    static const double UB_TARGETS_PER_GRAM = 0.0250325;
    
    //number of CH2 molecules per gram (in units of avogadro's #)
    // 1/14.02 = 0.0713267
    static const double MINIBOONE_TARGETS_PER_GRAM = 0.0713267;
    
  } //end namespace GEOCONSTANTS

} //end namespace ubsens
  
#endif

#ifndef RECOSHOWER_CC
#define RECOSHOWER_CC

#include "RecoShower.hh"

namespace ubsens {

  namespace data {

    RecoShower::RecoShower() 
    {
      Reset();
    }

    void RecoShower::Reset()
    {

      for(size_t i=0; i<3; ++i) {
	fDCosStart[i]      = ::ubsens::fmwk::INVALID_DOUBLE;
	fSigmaDCosStart[i] = ::ubsens::fmwk::INVALID_DOUBLE;
	fXYZstart[i]       = ::ubsens::fmwk::INVALID_DOUBLE;
	fSigmaXYZstart[i]  = ::ubsens::fmwk::INVALID_DOUBLE;
      }

      fTotalEnergy      = ::ubsens::fmwk::INVALID_DOUBLE;
      fSigmaTotalEnergy = ::ubsens::fmwk::INVALID_DOUBLE;
      fdEdx             = ::ubsens::fmwk::INVALID_DOUBLE;
      fSigmadEdx        = ::ubsens::fmwk::INVALID_DOUBLE;
    }

  }

}
#endif

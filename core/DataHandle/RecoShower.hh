/**
 * \file RecoShower.hh
 *
 * \ingroup DataHandle
 * 
 * \brief Class def header for a class RecoShower
 *
 * @author davidkaleko
 */

/** \addtogroup DataHandle

    @{*/
#ifndef RECOSHOWER_HH
#define RECOSHOWER_HH

#include <iostream>
#include <TVector3.h>

namespace ubsens {

  namespace data {
    
    /**
       \class RecoShower
    */
    class RecoShower{
      
    public:
      
      /// Default constructor
      RecoShower();
      
      /// Default destructor
      virtual ~RecoShower(){};
      
      /// Method to bring back the default values
      void Reset();
      
    protected:
      
      TVector3 fDCosStart;
      TVector3 fSigmaDCosStart;
      TVector3 fXYZstart;
      TVector3 fSigmaXYZstart;
      std::vector< Double_t > fTotalEnergy;
      std::vector< Double_t > fSigmaTotalEnergy;
      std::vector< Double_t > fTotalMIPEnergy;
      std::vector< Double_t > fSigmaTotalMIPEnergy;
      Int_t fBestPlane;
      std::vector< Double_t > fdEdx;
      std::vector< Double_t > fSigmadEdx;

    };
  }
}
#endif
/** @} */ // end of doxygen group 


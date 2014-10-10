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
<<<<<<< HEAD
#include "FMWKBase/FMWKConstants.hh"
=======
#include "FMWKConstants.hh"
>>>>>>> 55a19f0d54facde2c6fe5aaff942c6d82f7ad917
#include "DHException.hh"

namespace ubsens {

  namespace data {
    
    /**
       \class RecoShower
       Data holder for a single reco-ed shower data product info
    */
    class RecoShower : public TObject {
      
    public:
      
      /// Default constructor
      RecoShower();
      
      /// Default destructor
      virtual ~RecoShower(){};
      
      /// Method to bring back the default values
      void Reset();

      //
      // Setters
      //
      /// Shower direction unit vector setter
      void DCosStart(TVector3 const& dir, TVector3 const& dir_err)
      { fDCosStart = dir; fSigmaDCosStart = dir_err; }
      /// Shower start vtx unit vector setter
      void XYZStart(TVector3 const& vtx, TVector3 const& vtx_err)
      { fXYZstart = vtx; fSigmaXYZstart = vtx_err; }
      /// Energy [MeV] setter
      void TotalEnergy(double const& e, double const& e_err)
      { fTotalEnergy = e; fSigmaTotalEnergy = e_err; }
      /// dEdx setter
      void dEdx(double const& dedx, double const& dedx_err)
      { fdEdx = dedx; fSigmadEdx = dedx_err; }

      //
      // Getters
      //
      /// Shower direction unit vector getter
      const TVector3& DCosStart() const      { return fDCosStart;        }
      /// Shower direction error unit vector getter
      const TVector3& SigmaDCosStart() const { return fSigmaDCosStart;   }
      /// Shower start vtx unit vector getter
      const TVector3& XYZStart() const       { return fXYZstart;         }
      /// Shower start vtx error unit vector getter
      const TVector3& SigmaXYZStart() const  { return fSigmaXYZstart;    }
      /// Energy [MeV] getter
      const double TotalEnergy() const       { return fTotalEnergy;      }
      /// Energy [MeV] error getter
      const double SigmaTotalEnergy() const  { return fSigmaTotalEnergy; }
      /// dEdx [MeV/cm] getter
      const double dEdx() const              { return fdEdx;             }
      /// dEdx [MeV/cm] error getter
      const double SigmadEdx() const         { return fSigmadEdx;        }
      
    protected:

      /// Direction (x,y,z) unit vector
      TVector3 fDCosStart;
      /// Error on direction (x,y,z) unit vector
      TVector3 fSigmaDCosStart;
      /// (x,y,z) [cm] start point vtx
      TVector3 fXYZstart;
      /// Error on (x,y,z) [cm] start point vtx
      TVector3 fSigmaXYZstart;
      /// Energy [MeV] of the shower
      double fTotalEnergy;
      /// Error on energy [MeV]
      double fSigmaTotalEnergy;
      /// dE/dX 
      double fdEdx;
      /// Error on fdEdx
      double fSigmadEdx;

      ClassDef(RecoShower,1)
    };
  }
}
#endif
/** @} */ // end of doxygen group 


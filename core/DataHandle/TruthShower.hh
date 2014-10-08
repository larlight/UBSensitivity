/**
 * \file TruthShower.hh
 *
 * \ingroup DataHandle
 * 
 * \brief Class def header for a class TruthShower
 *
 * @author davidkaleko
 */

/** \addtogroup DataHandle

    @{*/
#ifndef TRUTHSHOWER_HH
#define TRUTHSHOWER_HH

#include <iostream>
#include <TVector3.h>
#include "DHException.hh"
#include "FMWKConstants.hh"

namespace ubsens {

  namespace data {

    /**
       \class TruthShower
       Data holder for a single truth shower data product info
    */
    class TruthShower {
      
    public:
      
      /// Default constructor
      TruthShower(){};
      
      /// Default destructor
      virtual ~TruthShower(){};
      
      /// Method to bring back the default values
      void Reset();

      //
      // Setters
      //
      /// Mother PDGID setter
      void MotherPDGID(unsigned int const& id) { fMotherPDGID=id; }
      /// Mother vtx position (4-position in cm & ns) setter
      void MotherVtx(std::vector<double> const& vtx);
      /// Mother momentum (4-momentum in MeV/c & MeV) setter
      void MotherMomentum(std::vector<double> const& mom);
      /// Daughter vtx position (4-position in cm & ns) setter
      void DaughterVtx(std::vector<double> const& vtx);
      /// Daughter momentum (4-momentum in MeV/c & MeV) setter
      void DaughterMomentum(std::vector<double> const& mom);

      //
      // Getters
      //
      /// Mother PDGID getter
      const unsigned int MotherPDGID() const              { return fMotherPDGID;      }
      /// Mother vtx position (4-position in cm & ns) getter
      const std::vector<double>& MotherVtx() const        { return fMotherVtx;        }
      /// Mother momentum (4-momentum in MeV/c & MeV) getter
      const std::vector<double>& MotherMomentum() const   { return fMotherMomentum;   }
      /// Daughter vtx position (4-position in cm & ns) getter
      const std::vector<double>& DaughterVtx() const      { return fDaughterVtx;      }
      /// Daughter momentum (4-momentum in MeV/c & MeV) getter
      const std::vector<double>& DaughterMomentum() const { return fDaughterMomentum; }
      
    protected:

      //---- Mother info  -----//
      int  fMotherPDGID;                   ///< mother PDG code
      std::vector<double> fMotherVtx;      ///< mother position 4-vector @ generation
      std::vector<double> fMotherMomentum; ///< mother momentum 4-vector @ generation
      
      //---- Daughter info ----//
      std::vector<double> fDaughterVtx;      ///< Daughters' deposit point closest to the mother vtx
      std::vector<double> fDaughterMomentum; ///< Daughters' deposit sum momentum 4-vector

    };
    
  }//end namespace data
  
}//end namespace ubsens

#endif
    /** @} */ // end of doxygen group 


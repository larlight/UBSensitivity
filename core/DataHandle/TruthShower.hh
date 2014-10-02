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

/**
   \class TruthShower
   User defined class TruthShower ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens {

  namespace data {

    
    class TruthShower{
      
    public:
      
      /// Default constructor
      TruthShower(){};
      
      /// Default destructor
      virtual ~TruthShower(){};
      
      /// Method to bring back the default values
      void Reset();
      
    protected:
      
      Int_t  fMotherPDGID;                   ///< mother PDG code
      std::vector<Double_t> fMotherVtx;      ///< mother position 4-vector @ generation
      std::vector<Double_t> fMotherMomentum; ///< mother momentum 4-vector @ generation
      /// mother 3D angle phi (along shower angle definition, not ordinary coord. system)
      Double_t fMotherPhi;
      /// mother 3D angle theta (along shower angle definition, not ordinary coord. system)
      Double_t fMotherTheta;
      
      //---- Daughter info ----//
      std::vector<UInt_t>  fDaughterTrackID;  ///< Daughters' track ID
      std::vector<Double_t> fDaughterVtx;      ///< Daughters' deposit point closest to the mother vtx
      std::vector<Double_t> fDaughterMomentum; ///< Daughters' deposit sum momentum 4-vector
      /// daughter 3D angle phi (along shower angle definition, not ordinary coord. system)
      Float_t fDaughterPhi;
      /// daughter 3D angle theta (along shower angle definition, not ordinary coord. system)
      Float_t fDaughterTheta;
      
      //---- Charge per plane ----//
      std::vector<Float_t> fPlaneCharge; ///< Charge deposit per plane
      
    };
    
  }//end namespace data
  
}//end namespace ubsens

#endif
    /** @} */ // end of doxygen group 


#ifndef TRUTHSHOWER_CC
#define TRUTHSHOWER_CC

#include "TruthShower.hh"

namespace ubsens {

  namespace data {

    void TruthShower::MotherVtx(std::vector<double> const& vtx)
    {
      if(vtx.size()!=4) throw DHException(__FUNCTION__,
					  Form("Mismatch in vector length: %zu != 4",vtx.size())
					  );
      fMotherVtx = vtx;    
    }

    void TruthShower::MotherMomentum(std::vector<double> const& mom)
    {
      if(mom.size()!=4) throw DHException(__FUNCTION__,
					  Form("Mismatch in vector length: %zu != 4",mom.size())
					  );
      fMotherMomentum = mom;
    }

    void TruthShower::DaughterVtx(std::vector<double> const& vtx)
    {
      if(vtx.size()!=4) throw DHException(__FUNCTION__,
					  Form("Mismatch in vector length: %zu != 4",vtx.size())
					  );
      fDaughterVtx = vtx;
    }

    void TruthShower::DaughterMomentum(std::vector<double> const& mom)
    {
      if(mom.size()!=4) throw DHException(__FUNCTION__,
					  Form("Mismatch in vector length: %zu != 4",mom.size())
					  );
      fDaughterMomentum = mom;
    }

    void TruthShower::Reset() 
    {

      fMotherPDGID = ::ubsens::fmwk::INVALID_INT;

      fMotherVtx.clear();
      fMotherVtx.resize(4,::ubsens::fmwk::INVALID_DOUBLE);

      fMotherMomentum.clear();
      fMotherMomentum.resize(4,::ubsens::fmwk::INVALID_DOUBLE);

      fDaughterVtx.clear();
      fDaughterVtx.resize(4,::ubsens::fmwk::INVALID_DOUBLE);

      fDaughterMomentum.clear();
      fDaughterMomentum.resize(4,::ubsens::fmwk::INVALID_DOUBLE);

    }
  }
}
#endif

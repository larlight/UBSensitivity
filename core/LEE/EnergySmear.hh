/**
 * \file EnergySmear.hh
 *
 * \ingroup LEE
 * 
 * \brief Class to smear the lepton energy with custom smearing.
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef ENERGYSMEAR_HH
#define ENERGYSMEAR_HH

#include "LEEBase.hh"
#include "TF1.h"
#include "TH2.h"
#include "Utilities/PlotWriter.hh"
#include "TRandom.h"

/**
   \class EnergySmear
   Class to smear the lepton energy with custom smearing. For now, the energy smearing function is assumed to be 15% / sqrt(lepton energy).
*/

namespace ubsens{
  
  class EnergySmear : public LEEBase{
    
  public:
    
    /// Default constructor
    EnergySmear(){ _name = "EnergySmear"; };
    
    /// Default destructor
    virtual ~EnergySmear(){};
  
    void Initialize();
  
    double SmearEnergy(double lept_energy_GEV);
  
    /// Inherited writeplots function from LEEBase
    void WritePlots();

  private:

    TF1 *mysmearing;
  
    TH2F *correlation;

  };
  
}//end namespace ubsens
#endif
/** @} */ // end of doxygen group 


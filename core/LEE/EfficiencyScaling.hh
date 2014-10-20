/**
 * \file EfficiencyScaling.hh
 *
 * \ingroup LEE
 * 
 * \brief Class def header for a class EfficiencyScaling
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef EFFICIENCYSCALING_HH
#define EFFICIENCYSCALING_HH

#include <iostream>
#include "LEEBase.hh"
#include "Utilities/PlotWriter.hh"

/**
   \class EfficiencyScaling
   User defined class EfficiencyScaling ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{

  class EfficiencyScaling : public LEEBase {
    
  public:
    
    /// Default constructor
    EfficiencyScaling(){
      _name = "EfficiencyScaling";
    };
    
    /// Inherited writeplots function from LEEBase
    void WritePlots();

    /// Default destructor
    virtual ~EfficiencyScaling(){};

///Function to make a hard-coded efficiency graph at 80%. Will update 
///in the future
void MakeGraph();

///Function to get the efficiency graph (vs lepton energy in GEV)
TGraph* GetEfficiencyGraph() { return _eff_graph; }

  private:

    ::ubsens::fmwk::Message fMsg;

  protected:

    /// TGraph of selection efficiency vs. lepton energy
    TGraph *_eff_graph;

  };

}//end namespace ubsens
#endif
/** @} */ // end of doxygen group 


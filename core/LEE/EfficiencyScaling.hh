/**
 * \file EfficiencyScaling.hh
 *
 * \ingroup LEE
 * 
 * \brief Class to scale the efficiency. For now it just makes a flat graph at 0.8 and calls that the efficiency. Can be improved once our actual event selection efficiency is studied in depth (after automated reconstruction is developed more, etc).
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef EFFICIENCYSCALING_HH
#define EFFICIENCYSCALING_HH

#include "LEEBase.hh"
#include "Utilities/PlotWriter.hh"
#include "TGraph.h"

/**
   \class EfficiencyScaling
   Class to scale the efficiency. For now it just makes a flat graph at 0.8 and calls that the efficiency. Can be improved once our actual event selection efficiency is studied in depth (after automated reconstruction is developed more, etc).
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

    /// TGraph of selection efficiency vs. lepton energy
    TGraph *_eff_graph;

  };

}//end namespace ubsens
#endif
/** @} */ // end of doxygen group 


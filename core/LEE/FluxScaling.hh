/**
 * \file FluxScaling.hh
 *
 * \ingroup LEE
 * 
 * \brief Class def header for a class FluxScaling
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef FLUXSCALING_HH
#define FLUXSCALING_HH

#include <iostream>
#include "LEEBase.hh"
#include "Utilities/PlotReader.hh"
#include "Utilities/PlotWriter.hh"
#include "Utilities/FindInMapMap.hh"

/**
   \class FluxScaling
   User defined class FluxScaling ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens {

  class FluxScaling : public LEEBase {
    
  public:
    
    /// Default constructor
    FluxScaling(){
      _my_flux = 0;
      _MB_flux = 0;
      _flux_ratio = 0;
      _my_flux_input_filename = "";
      _my_flux_TGraph_name = "";
      _MB_flux_input_filename = "";
      _MB_flux_TGraph_name = "";
      _name = "FluxScaling";
    };

    /// Inherited configure function from LEEBase
    virtual bool Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap);

    /// Inherited writeplots function from LEEBase
    void WritePlots();
    
    /// Default destructor
    virtual ~FluxScaling(){};
    
    void SetMyInputFile(std::string filename_and_path)
    { _my_flux_input_filename = filename_and_path; }
    
    void SetMBInputFile(std::string filename_and_path)
    { _MB_flux_input_filename = filename_and_path; }
    
    void SetMyInputGraphName(std::string in_graph)
    { _my_flux_TGraph_name = in_graph; }

    void SetMBInputGraphName(std::string in_graph)
    { _MB_flux_TGraph_name = in_graph; }
    
    bool LoadInputGraphs();
    
    void ComputeFluxRatio();
    
    TGraph* GetFluxRatio(){ return _flux_ratio; }
    
    
  private:

    ::ubsens::fmwk::Message fMsg;

  protected:
    
    //cross section graph for your detector
    TGraph *_my_flux;
    //cross section graph for miniboone
    TGraph *_MB_flux;
    //division of the two cross section graphs
    TGraph *_flux_ratio;
    
    std::string _my_flux_input_filename;
    std::string _my_flux_TGraph_name;
    std::string _MB_flux_input_filename;
    std::string _MB_flux_TGraph_name;

  };
  
}// end namespace ubsens

#endif
/** @} */ // end of doxygen group 


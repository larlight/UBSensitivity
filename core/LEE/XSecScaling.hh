/**
 * \file XSecScaling.hh
 *
 * \ingroup LEE
 * 
 * \brief This grabs xsection graphs from files and divides them.
 *        It also multiplies cross sections by n-targets-per-ton,
 *        so it's really more than just cross section scaling.
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef XSECSCALING_HH
#define XSECSCALING_HH

#include <iostream>
#include <sstream>
#include "LEEException.hh"
#include "Utilities/PlotReader.hh"
#include "Utilities/PlotWriter.hh"
#include "Constants/GeometryConstants.hh"
#include "FMWKBase/Message.hh"
#include "TGraph.h"

/**
   \class XSecScaling
   User defined class XSecScaling ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{
  
  class XSecScaling{
    
  public:
    
    /// Default constructor
    XSecScaling()
    {
      _my_xsec = 0;
      _MB_xsec = 0;
      _xsec_ratio = 0;
      _my_xsec_input_filename = "";
      _my_xsec_TGraph_name = "";
      _MB_xsec_input_filename = "";
      _MB_xsec_TGraph_name = "";
      _my_ntargetspergram = geo::UB_TARGETS_PER_GRAM;
      _MB_ntargetspergram = geo::MINIBOONE_TARGETS_PER_GRAM;
      _classname = "XSecScaling";
    };
    
    /// Default destructor
    virtual ~XSecScaling(){};
    
    void SetMyInputFile(std::string filename_and_path)
    { _my_xsec_input_filename = filename_and_path; }
    
    void SetMBInputFile(std::string filename_and_path)
    { _MB_xsec_input_filename = filename_and_path; }
    
    void SetMyInputGraphName(std::string in_graph)
    { _my_xsec_TGraph_name = in_graph; }
    
    void SetMBInputGraphName(std::string in_graph)
    { _MB_xsec_TGraph_name = in_graph; }
    
    
    //optional. default is microboone
    void SetMyNTargetsPerGram(double value) { _my_ntargetspergram = value; }
    
    //optional. default is MB
    void SetMBNTargetsPerGram(double value) { _MB_ntargetspergram = value; }
    
    bool LoadInputGraphs();
    
    void ComputeXSecRatio();
    
    TGraph* GetXSecRatio(){ return _xsec_ratio; }
    
    void WritePlots();
    
  private:

    ::ubsens::fmwk::Message fMsg;

  protected:
    
    //cross section graph for your detector
    TGraph *_my_xsec;
    //cross section graph for miniboone
    TGraph *_MB_xsec;
    //division of the two cross section graphs
    TGraph *_xsec_ratio;
    
    std::string _my_xsec_input_filename;
    std::string _my_xsec_TGraph_name;
    std::string _MB_xsec_input_filename;
    std::string _MB_xsec_TGraph_name;
    
    double _my_ntargetspergram;
    double _MB_ntargetspergram;

    std::string _classname;
  };
  
}//end namespace ubsens

#endif
/** @} */ // end of doxygen group 


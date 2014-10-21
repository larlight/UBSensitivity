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
#include "LEEBase.hh"
#include "Utilities/PlotReader.hh"
#include "Utilities/PlotWriter.hh"
#include "Utilities/FindInMapMap.hh"
#include "Constants/GeometryConstants.hh"

/**
   \class XSecScaling
   User defined class XSecScaling ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{
  
  class XSecScaling : public LEEBase{
    
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
      _xsec_ratio_maximum="";
      _xsec_ratio_minimum="";
      _name = "XSecScaling";
    };
    
    /// Inherited configure function from LEEBase
    virtual bool Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap);

    /// Inherited writeplots function from LEEBase
    void WritePlots();

    /// Default destructor
    virtual ~XSecScaling(){};
        
    /// Manual setters if you aren't getting this info from ConfigManager
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

    std::string _xsec_ratio_maximum;
    std::string _xsec_ratio_minimum;
  };
  
}//end namespace ubsens

#endif
/** @} */ // end of doxygen group 


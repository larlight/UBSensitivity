/**
 * \file XSecScaling.hh
 *
 * \ingroup LEE
 * 
 * \brief Class def header for a class XSecScaling
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef XSECSCALING_HH
#define XSECSCALING_HH

#include <iostream>
#include "Utilities/TGraphReader.hh"
#include "TGraph.h"

/**
   \class XSecScaling
   User defined class XSecScaling ... these comments are used to generate
   doxygen documentation!
 */
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

  bool LoadInputGraphs();

  void ComputeXSecRatio();

  TGraph* GetXSecRatio(){ return _xsec_ratio; }


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

};

#endif
/** @} */ // end of doxygen group 


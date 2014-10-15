/**
 * \file PlotReader.hh
 *
 * \ingroup LEE
 * 
 * \brief This opens up TFiles and reads in TGraphs, TH1D, TH2Fs etc, 
 * and returns them
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef PLOTREADER_HH
#define PLOTREADER_HH

#include <iostream>
#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/FMWKException.hh"
#include "TGraph.h"
#include "TH2.h"
#include "TFile.h"

/**
   \class PlotReader
   User defined class PlotReader ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens{

  namespace util{
    
    class PlotReader : public ::ubsens::fmwk::FMWKBase {
      
    public:
      
      void SetFileName(std::string filename) { _filename = filename; }
      
      void SetPlotName(std::string plotname) { _plotname = plotname; }
    
      void Reset() {
	_filename = "";
	_plotname = "";
	_name = "PlotReader";
      }

      TGraph* GetGraph();
      
      TH2F* GetTH2F();

      //singleton getter?!?!?!
      static PlotReader* GetME(){
	if(!_me) _me = new PlotReader;
	return _me;
      }
    
    private:
      //singleton!?!
      static PlotReader* _me;
      
      //constructor is private for singletons right?
      /// Default constructor
      PlotReader(){
	_filename = "";
	_plotname = "";
      }
      
      /// Default destructor
      virtual ~PlotReader(){};
      
      
    protected:
      
      std::string _filename;
      std::string _plotname;

    };
    
  }//end namespace util

}//end namespace ubsens

#endif
/** @} */ // end of doxygen group 


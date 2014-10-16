/**
 * \file PlotWriter.hh
 *
 * \ingroup Utilities
 * 
 * \brief Singleton that writes all tgraphs/histos to a single output file
 * (actually it can write anything that inherits from TObject)
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities
    
    @{*/
#ifndef PLOTWRITER_HH
#define PLOTWRITER_HH

#include <iostream>
#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/FMWKException.hh"
#include "TFile.h"
#include "TObjString.h"
#include "TGraph.h"
#include "TH2.h"


/**
   \class PlotWriter
   User defined class PlotWriter ... these comments are used to generate
   doxygen documentation!
*/

namespace ubsens{
  namespace util{
    
    class PlotWriter : public ::ubsens::fmwk::FMWKBase {
      
    public:
      
      /// Manual setter of output file name to save all plots
      void SetFileName(std::string filename) { _filename = filename; }
      
      /// Main funciton to write objects to file
      void Write(TObject *object_to_write,std::string subdirectory="",std::string writeoptions="");
      
      //singleton getter?!?!?!
      static PlotWriter* GetME(){
	if(!_me) _me = new PlotWriter;
	return _me;
      }
      
    private:
      //singleton!?!
      static PlotWriter* _me;
      
      /// Default constructor
      PlotWriter(){
	_filename = "";
	_plotname = "";
	_plottitle = "";
	_name = "PlotWriter";
      };
      
      /// Default destructor
      virtual ~PlotWriter(){};
      
      
    protected:
      
      std::string _filename;
      std::string _plotname;
      std::string _plottitle;
      
    };
    
  } //end namespace util
} //end namespace ubsens
#endif
/** @} */ // end of doxygen group 


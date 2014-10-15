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
#include "TGraph.h"
#include "TH2.h"
#include "TFile.h"

/**
   \class PlotWriter
   User defined class PlotWriter ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens{
  namespace util{
    
    class PlotWriter : public ::ubsens::fmwk::FMWKBase {
      
    public:
      
      void SetFileName(std::string filename) { _filename = filename; }
      
      void Write(TObject *object_to_write,std::string subdirectory="");

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


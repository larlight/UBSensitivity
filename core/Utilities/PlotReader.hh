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
#include "TObject.h"
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
      
      void SetObjectName(std::string objectname) { _objectname = objectname; }
    
      void Reset() {
	_filename = "";
	_objectname = "";
	_name = "PlotReader";
      }

      /// Function to get an object from a file
      /// (whoever gets the object should cast it to the appropriate type)
      TObject* GetObject();

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
	_objectname = "";
      }
      
      /// Default destructor
      virtual ~PlotReader(){};
      
      
    protected:
      
      std::string _filename;
      std::string _objectname;

    };
    
  }//end namespace util

}//end namespace ubsens

#endif
/** @} */ // end of doxygen group 


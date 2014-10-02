/**
 * \file PlotWriter.hh
 *
 * \ingroup Utilities
 * 
 * \brief Singleton that writes all tgraphs/histos to a single output file
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef PLOTWRITER_HH
#define PLOTWRITER_HH

#include <iostream>
#include "TGraph.h"
#include "TFile.h"

/**
   \class PlotWriter
   User defined class PlotWriter ... these comments are used to generate
   doxygen documentation!
 */

namespace util{
  
  class PlotWriter{
    
  public:
    
    void SetFileName(std::string filename) { _filename = filename; }
    
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
    };
    
    /// Default destructor
    virtual ~PlotWriter(){};
    
    
  protected:
    
    std::string _filename;
    std::string _plotname;
    std::string _plottitle;

    
  };
  
} //end namespace util

#endif
/** @} */ // end of doxygen group 


/**
 * \file TGraphReader.hh
 *
 * \ingroup LEE
 * 
 * \brief This opens up TFiles and reads in TGraphs, and returns them
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef TGRAPHREADER_HH
#define TGRAPHREADER_HH

#include <iostream>
#include "TGraph.h"
#include "TFile.h"

/**
   \class TGraphReader
   User defined class TGraphReader ... these comments are used to generate
   doxygen documentation!
 */
class TGraphReader{

public:

  void SetFileName(std::string filename) { _filename = filename;}

  void SetGraphName(std::string graphname) { _graphname = graphname;}

  TGraph* GetGraph();

  //singleton getter?!?!?!
  static TGraphReader* GetME(){
    if(!_me) _me = new TGraphReader;
    return _me;
  }

private:
  //singleton!?!
  static TGraphReader* _me;

  //constructor is private for singletons right?
  /// Default constructor
  TGraphReader(){};

  /// Default destructor
  virtual ~TGraphReader(){};

  
protected:

  std::string _filename;
  std::string _graphname;

};

#endif
/** @} */ // end of doxygen group 


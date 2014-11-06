/**
 * \file TGraphManip.hh
 *
 * \ingroup Utilities
 * 
 * \brief Class def header for a class TGraphManip
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef TGRAPHMANIP_HH
#define TGRAPHMANIP_HH

#include <iostream>
#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/FMWKException.hh"
#include "TGraph.h"

/**
   \class TGraphManip
   User defined class TGraphManip ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{
  namespace util{
    
    class TGraphManip : public ::ubsens::fmwk::FMWKBase {
      
    public:
      
      /// Default constructor
      TGraphManip(){ _name = "TGraphManip"; };
      
      /// Default destructor
      virtual ~TGraphManip(){};

      TGraph* MultiplyTwoGraphs(TGraph* const g1, TGraph* const g2);
      
      TGraph* DivideTwoGraphs(TGraph* const numerator, TGraph* const denominator);

      void ScaleGraph(TGraph & g1, double scaling_factor);

    };

    }//end namespace util
  }//end namespace ubsens

#endif
/** @} */ // end of doxygen group 


/**
 * \file FinalPlotter.hh
 *
 * \ingroup LEE
 * 
 * \brief Class def header for a class FinalPlotter
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef FINALPLOTTER_HH
#define FINALPLOTTER_HH

#include <iostream>
#include "FMWKBase/FMWKBase.hh"
#include "TH1.h"
#include "THStack.h"

/**
   \class FinalPlotter
   User defined class FinalPlotter ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{

  class FinalPlotter : public ::ubsens::fmwk::FMWKBase{
    
  public:
    
    /// Default constructor
    FinalPlotter(){ _name = "FinalPlotter"; };
    
    /// Default destructor
    virtual ~FinalPlotter(){};
    
    THStack* AddTH1FToStack(TH1F *hist, THStack *stack);

    THStack* RebinStack(THStack *stack, size_t somenumberinvolvingbins);

    TH1F* RebinTH1F(TH1F *hist, size_t somenumberinvolvingbins);

  };

}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


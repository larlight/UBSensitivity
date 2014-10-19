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
#include <vector>

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

    /// Utility function to check and make sure the new custom bins are
    /// integer multiples of the previous histo binning... if they aren't,
    /// "all entries in the split bin in the original histogram will be 
    /// transferred to the lower of the two possible bins in the new histogram.
    /// This is probably not what you want" (from TH1 root documentation)
    bool CheckBins(const TH1F *hist, std::vector<double> *bins);
    
    /// Function to add a TH1F to a THStack of TH1F, then return the new stack
    THStack* AddTH1FToStack(const TH1F *hist, const THStack *stack);

    /// Function to loop through histos in a stack, rebin each, then return 
    /// a new stack
    // THStack* RebinStack(const THStack *stack, const std::vector<double> *newbins);

    /// Function to rebin a TH1F with custom bins, then return the new TH1F
    //    TH1F* RebinTH1F(const TH1F *hist, const std::vector<double> *newbins);

  };

}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


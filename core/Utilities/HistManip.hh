/**
 * \file HistManip.hh
 *
 * \ingroup Utilities
 * 
 * \brief Class def header for a class HistManip
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef HISTMANIP_HH
#define HISTMANIP_HH

#include <iostream>
#include "FMWKBase/FMWKBase.hh"
#include "TH1.h"
#include "THStack.h"
#include "TList.h"
#include <vector>

/**
   \class HistManip
   User defined class HistManip ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens{
  namespace util{
    
    class HistManip : public ::ubsens::fmwk::FMWKBase{
      
    public:
      
      /// Default constructor
      HistManip(){ _name = "HistManip"; };
      
      /// Default destructor
      virtual ~HistManip(){};
      
      /// Utility function to check and make sure the new custom bins are
      /// integer multiples of the previous histo binning... if they aren't,
      /// "all entries in the split bin in the original histogram will be 
      /// transferred to the lower of the two possible bins in the new histogram.
      /// This is probably not what you want" (from TH1 root documentation)
      static bool CheckBins(const TH1F * const hist, const std::vector<double> *bins);
      
      /// Function to add a TH1F to a THStack of TH1F, then return the new stack
      static THStack* AddTH1FToStack(TH1F * const hist, THStack * const stack);
      
      /// Function to rebin a TH1F with custom bins, then return the new TH1F
      static TH1F* RebinTH1F(TH1F * const hist, const std::vector<double> *newbins);
      
      /// Function to loop through histos in a stack, rebin each, then return 
      /// a new stack
      static THStack* RebinStack(const THStack *stack, const std::vector<double> *newbins);
      
    };
    
  }// end namespace util
}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 

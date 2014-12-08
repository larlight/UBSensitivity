/**
 * \file HistManip.hh
 *
 * \ingroup Utilities
 * 
 * \brief Utility to rebin histograms, add histograms to THStacks, etc.
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef HISTMANIP_HH
#define HISTMANIP_HH

#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/FMWKException.hh"
#include "TH1.h"
#include "THStack.h"
#include "TList.h"

/**
   \class HistManip
   Utility to rebin histograms, add histograms to THStacks, etc.
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
      bool CheckBins(const TH1F * const hist, const std::vector<double> *bins);
      
      /// Function to add a TH1F to a THStack of TH1F, then return the new stack
      THStack* AddTH1FToStack(TH1F * const hist, THStack * const stack);
      
      /// Function to rebin a TH1F with custom bins, then return the new TH1F
      TH1F* RebinTH1F(TH1F * const hist, const std::vector<double> *newbins);
      
      /// Function to loop through histos in a stack, rebin each, then return 
      /// a new stack
      THStack* RebinStack(const THStack *stack, const std::vector<double> *newbins);
		
      /// Function to convert a histogram in terms of raw events to one
      /// in terms of events/GeV (for example) by including bin width
      /// note: modifies the actual histogram, doesn't make a new one
      void ConvertToEventsPerBinWidth( TH1F & hist );

      /// Function to convert a histogram in terms of events/GeV (for example)
      /// to one of raw events.
      /// note: modifies the actual histogram, doesn't make a new one
      void ConvertToEvents( TH1F & hist );

      /// Function to do this for each histo in a stack
      THStack* ConvertToEvents( THStack & stack );

      /// Function to set all errors in a histogram to zero
      void SetZeroErrors( TH1F & hist );

    private:

      /// Messenger instance
      ::ubsens::fmwk::Message fMsg;

    };
    
  }// end namespace util
}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


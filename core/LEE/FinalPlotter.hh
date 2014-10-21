/**
 * \file FinalPlotter.hh
 *
 * \ingroup LEE
 * 
 * \brief This is the function that takes in the end LEE histogram from
 * LEEMain and makes it pretty. It also grabs background stacks and plots
 * the LEE signal on top, and saves a legend.
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef FINALPLOTTER_HH
#define FINALPLOTTER_HH

#include <iostream>
#include "LEEBase.hh"
#include "TH1.h"
#include "THStack.h"
#include "TList.h"
#include <vector>
#include "TLegend.h"
#include "Utilities/FindInMapMap.hh"
#include "Utilities/PlotReader.hh"
#include "Utilities/PlotWriter.hh"
#include "Utilities/StringParser.hh"
#include "Utilities/HistManip.hh"

/**
   \class FinalPlotter
   User defined class FinalPlotter ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{

  class FinalPlotter : public LEEBase{
    
  public:
    
    /// Default constructor
    FinalPlotter(){ 
      _name = "FinalPlotter"; 
      _background_stackfile = "";
      _background_stackname = "";
      _background_legendname= "";
      _final_hist_bins_string="";
      _final_stack_title="";
      _final_stack=0;
      _final_LEE_histo=0;
      _final_legend=0;
    };
    
    /// Default destructor
    virtual ~FinalPlotter(){};

    /// Inherited configure fucntion from LEEBase
    virtual bool Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap);

    /// Inherited writeplots function from LEEBase
    void WritePlots();

    /// Function to make the final output stacked plot on backgrounds
    void MakeStackedHisto();

    /// Function to load the LEE histo from LEEMain
    void LoadLEEHisto(TH1F* histo){ _final_LEE_histo = histo; }


  private:

    std::string _background_stackfile;
    std::string _background_stackname;
    std::string _background_legendname;
    std::string _final_hist_bins_string;
    std::string _final_stack_title;

    THStack* _final_stack;
    TH1F* _final_LEE_histo;
    TLegend* _final_legend;


  };

}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


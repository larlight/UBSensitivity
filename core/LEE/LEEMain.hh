/**
 * \file LEEMain.hh
 *
 * \ingroup LEE
 * 
 * \brief Main class that performs event loop, owns DataManager and 
 * ConfigManager instances, configures all of the subprocesses, and
 * saves final histograms to output file
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef LEEMAIN_HH
#define LEEMAIN_HH

#include <iostream>
#include "LEEBase.hh"
#include "AnaConfig/ConfigManager.hh"
#include "DataHandle/DataManager.hh"
#include "XSecScaling.hh"
#include "TGraph.h"
/**
   \class LEEMain
   User defined class LEEMain ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{
  
  class LEEMain : public LEEBase{
    
  public:
    
    /// Default constructor
    LEEMain(){ _name="LEEMain"; };
    
    /// Default destructor
    virtual ~LEEMain(){};

    /// Initialization function
    bool Initialize();
    
    /// Main event loop function
    bool Run();

    /// Finalize stuff
    bool Finalize();

  private:

    ::ubsens::config::ConfigManager _cfgmgr;

    ::ubsens::data::DataManager _datamgr;

  };

}
#endif
/** @} */ // end of doxygen group 


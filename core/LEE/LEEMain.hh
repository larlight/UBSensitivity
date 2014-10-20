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
#include "POTScaling.hh"
#include "TonnageScaling.hh"
#include "XSecScaling.hh"
#include "FluxScaling.hh"
#include "NuLeptECorrelation.hh"
#include "EfficiencyScaling.hh"
#include "Utilities/FindInMapMap.hh"
#include "Utilities/StringParser.hh"
#include "Utilities/HistManip.hh"
#include "Utilities/ECCQECalculator.hh"
#include "TMath.h"
#include "THStack.h"
#include "TLegend.h"

/**
   \class LEEMain
   User defined class LEEMain ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{
  
  class LEEMain : public LEEBase{
    
  public:
    
    /// Default constructor
    LEEMain(){ 
      _name="LEEMain"; 
      _cfg_file="";
      _data_file="";
      _LEE_hist_name="";
      _LEE_hist_title="";
      _LEE_hist_bins_string="";
      _LEE_hist=0;
      _ElectronOrGamma="";
      _isElectronSample=true;
      _tmp_stack=0;
    };
    
    /// Default destructor
    virtual ~LEEMain(){};

    /// Initialization function
    bool Initialize();
    
    /// Main event loop function
    bool Run();

    /// Finalize stuff
    bool Finalize();

    void SetConfigFile(std::string cfgfile){ 
      _cfg_file = cfgfile; 
      std::cout<<"Using configuration file: "<<_cfg_file<<std::endl;
    };

    /// Inherited configure fucntion from LEEBase
    virtual bool Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap);

    void ConfigurePlotWriter();

    void InitializeHistos();

    void InitializeScalings();

  private:

    ::ubsens::config::ConfigManager _cfgmgr;

    ::ubsens::data::DataManager _datamgr;

    NuLeptECorrelation _nulec;
    XSecScaling _xsecscaling;
    FluxScaling _fluxscaling;
    POTScaling _potscaling;
    TonnageScaling _tonnagescaling;
    EfficiencyScaling _effscaling;


    std::string _cfg_file;
    std::string _data_file;
    std::string _LEE_hist_name;
    std::string _LEE_hist_title;
    std::string _LEE_hist_bins_string;
    std::string _ElectronOrGamma;

    bool _isElectronSample;
    
    TH1F* _LEE_hist;

    THStack* _tmp_stack;
  };

}
#endif
/** @} */ // end of doxygen group 


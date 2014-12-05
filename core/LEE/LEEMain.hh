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

//#include <iostream>
#include "LEEBase.hh"
#include "AnaConfig/ConfigManager.hh"
#include "DataHandle/DataManager.hh"
#include "POTScaling.hh"
#include "TonnageScaling.hh"
#include "XSecScaling.hh"
#include "FluxScaling.hh"
#include "NuLeptECorrelation.hh"
#include "EfficiencyScaling.hh"
#include "FinalPlotter.hh"
#include "EnergySmear.hh"
#include "Utilities/FindInMapMap.hh"
#include "Utilities/StringParser.hh"
#include "Utilities/HistManip.hh"
#include "Utilities/ECCQECalculator.hh"
#include "TH1.h"
#include "TMath.h"

/**
   \class LEEMain
   Main class that performs event loop, owns DataManager and 
   ConfigManager instances, configures all of the subprocesses, and
   saves final histograms to output file
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
      _EnergyDefinition="";
      _useSmearing=false;;
      _n_evts_generated="";
      _true_MB_excess_evts="";
      _isElectronSample=true;
      _useSmearingString="";
     
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
      std::string msg = "";
      msg += class_name() + " is using configuration file: "
	+ _cfg_file;
      fMsg.send(::ubsens::fmwk::msg::kINFO, __FUNCTION__, msg);
    };

    /// Inherited configure fucntion from LEEBase
    virtual bool Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap);

    void ConfigurePlotWriter();

    void InitializeHistos();

    void InitializeScalings();

    //get th1f function here?
  private:

    ::ubsens::config::ConfigManager _cfgmgr;

    ::ubsens::data::DataManager _datamgr;

    NuLeptECorrelation _nulec;
    XSecScaling _xsecscaling;
    FluxScaling _fluxscaling;
    POTScaling _potscaling;
    TonnageScaling _tonnagescaling;
    EfficiencyScaling _effscaling;
    EnergySmear _energysmear;

    std::string _cfg_file;
    std::string _data_file;
    std::string _LEE_hist_name;
    std::string _LEE_hist_title;
    std::string _LEE_hist_bins_string;
    std::string _ElectronOrGamma;
    std::string _EnergyDefinition;
    std::string _n_evts_generated;
    std::string _true_MB_excess_evts;
    std::string _useSmearingString;
    std::string _OptionalWeight;

    bool _isElectronSample;
    bool _useSmearing;

    TH1F* _LEE_hist;

  };

}
#endif
/** @} */ // end of doxygen group 


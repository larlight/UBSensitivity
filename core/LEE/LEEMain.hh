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

#include "Utilities/FindInMapMap.hh"
#include "Utilities/StringParser.hh"

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

  private:

    ::ubsens::config::ConfigManager _cfgmgr;

    ::ubsens::data::DataManager _datamgr;

    std::string _cfg_file;
    std::string _data_file;
    std::string _LEE_hist_name;
    std::string _LEE_hist_title;
    std::string _LEE_hist_bins_string;
    std::string _ElectronOrGamma;

    bool _isElectronSample;
    
    TH1F* _LEE_hist;
  };

}
#endif
/** @} */ // end of doxygen group 


#ifndef LEEMAIN_CC
#define LEEMAIN_CC

#include "LEEMain.hh"

namespace ubsens{
  

  bool LEEMain::Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap){

    try{
      _LEE_hist_name = util::FindInMapMap().GetParamValue(class_name(),std::string("LEEHistName"),_configMap);
      _LEE_hist_title = util::FindInMapMap().GetParamValue(class_name(),std::string("LEEHistTitle"),_configMap);
      _LEE_hist_bins_string =  util::FindInMapMap().GetParamValue(class_name(),std::string("LEEHistBins"),_configMap);
    }
    catch (fmwk::FMWKException &e) {
      std::cout<<e.what()<<std::endl;
    }

    //If the config file has blank lines, use defaults
    if(_LEE_hist_name.empty()){
      std::cout<<class_name()<<" is using default value for _LEE_hist_name."<<std::endl;
      _LEE_hist_name = "default_LEE_histname";
    }
    if(_LEE_hist_title.empty()){
      std::cout<<class_name()<<" is using default value for _LEE_hist_title."<<std::endl;
      _LEE_hist_title = "Default LEE histogram title";
    }
    if(_LEE_hist_bins_string.empty()){
      std::cout<<class_name()<<" is using default value for _LEE_hist_bins_string."<<std::endl;
      _LEE_hist_bins_string = "[0.2,0.48,0.76,1.04,1.32,1.6,1.88,2.16,2.44,2.72,3.0]";
    }

    return true;
  }

  bool LEEMain::Initialize(){

    //Configure the DataManager
    _datamgr.SetIOMode(ubsens::data::DataManager::READ);
    _datamgr.AddInputFilename("/Users/davidkaleko/UBSensitivity/single_electrons_allfiles.root");
    _datamgr.Open();
    
    //Configure the ConfigManager
    _cfgmgr.LoadConfig("/Users/davidkaleko/UBSensitivity/core/AnaConfig/mac/sample_config.config");

    //Configure the PlotWriter
    ConfigurePlotWriter();

    //Configure itself (LEEMain)
    Configure(_cfgmgr.GetConfigMap());

    //Save the config info to output file (must be done after configuring
    //PlotWriter, since that is what manages the output file)
    _cfgmgr.SaveConfig();
    //    _cfgmgr.DebugDump();
    
    const double* xbins = util::StringParser().ParseBinsString(_LEE_hist_bins_string);

    //kaleko start here tomorrow... custom binning! also implement parsebinsstring
    _LEE_hist = new TH1F(_LEE_hist_name.c_str(),_LEE_hist_title.c_str(),10,0.2,3.0);
    //    _LEE_hist = new TH1F(_LEE_hist_name.c_str(),_LEE_hist_title.c_str(),xbins);
    
    return true;
  }

  bool LEEMain::Run(){

    std::cout<<_datamgr.GetEntries()<<std::endl;

    int counter = 0;
    //loop over all events
    while(_datamgr.NextEntry()){
      counter++;
      
      //fill histo here
      _LEE_hist->Fill(0.56);

    }

    std::cout<<"counter = "<<counter<<std::endl;

    //NuLeptECorrelation stuff here
    NuLeptECorrelation _nulec;
    _nulec.Configure(_cfgmgr.GetConfigMap());
    _nulec.LoadInputTH2F();
    _nulec.WritePlots();
    std::cout<<"debug: nuleptE 1.234 turns into "<<_nulec.NuEFromLeptE(1.234)<<std::endl;

    //POTScaling stuff here
    //MyPOT
    //MBPOT

    //XSecScaling stuff here
    XSecScaling _xsecscaling;
    _xsecscaling.Configure(_cfgmgr.GetConfigMap());
    _xsecscaling.LoadInputGraphs();
    _xsecscaling.ComputeXSecRatio();
    TGraph *xsecratio = _xsecscaling.GetXSecRatio();
    _xsecscaling.WritePlots();
    std::cout<<"debug: xsec ratio has :" << xsecratio->GetN()<<std::endl;

    //FluxScaling stuff here
    FluxScaling _fluxscaling;
    _fluxscaling.Configure(_cfgmgr.GetConfigMap());
    _fluxscaling.LoadInputGraphs();
    _fluxscaling.ComputeFluxRatio();
    TGraph *fluxratio = _fluxscaling.GetFluxRatio();
    _fluxscaling.WritePlots();
    std::cout<<"debug: flux ratio has :" << fluxratio->GetN()<<std::endl;


    return true;


  }

  bool LEEMain::Finalize(){

    _datamgr.Close();

    util::PlotWriter::GetME()->Write(_LEE_hist,class_name());

    delete _LEE_hist;

    return true;
  }


  void LEEMain::ConfigurePlotWriter(){

    std::string pw_filename = "";

    pw_filename = util::FindInMapMap().GetParamValue(std::string("PlotWriter"),
						     std::string("OutFileName"),
						     _cfgmgr.GetConfigMap());
    if( pw_filename.empty() ) //use default
      util::PlotWriter::GetME()->SetFileName("/Users/davidkaleko/UBSensitivity/core/LEE/mac/plotwriter_out.root");
    else
      util::PlotWriter::GetME()->SetFileName(pw_filename);
    
    util::PlotWriter::GetME()->Reset();
  }

}//end namespace ubsens
#endif

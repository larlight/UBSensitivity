#ifndef LEEMAIN_CC
#define LEEMAIN_CC

#include "LEEMain.hh"

namespace ubsens{
  
  bool LEEMain::Initialize(){

    _datamgr.SetIOMode(ubsens::data::DataManager::READ);
    _datamgr.AddInputFilename("/Users/davidkaleko/UBSensitivity/single_electrons_allfiles.root");
    _datamgr.Open();
    
    _cfgmgr.LoadConfig("/Users/davidkaleko/UBSensitivity/core/AnaConfig/mac/sample_config.config");

    //Configure the class that saves all the histos/graphs/configlog etc
    ConfigurePlotWriter();

    _cfgmgr.SaveConfig();
    _cfgmgr.DebugDump();
    
    return true;
  }

  bool LEEMain::Run(){

    std::cout<<_datamgr.GetEntries()<<std::endl;

    int counter = 0;
    //loop over all events
    while(_datamgr.NextEntry()){
      counter++;
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
    
  }

}//end namespace ubsens
#endif

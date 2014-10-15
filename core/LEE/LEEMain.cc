#ifndef LEEMAIN_CC
#define LEEMAIN_CC

#include "LEEMain.hh"

namespace ubsens{
  
  bool LEEMain::Initialize(){

    _datamgr.SetIOMode(ubsens::data::DataManager::READ);
    _datamgr.AddInputFilename("/Users/davidkaleko/UBSensitivity/single_electrons_allfiles.root");
    _datamgr.Open();
    
    _cfgmgr.LoadConfig("/Users/davidkaleko/UBSensitivity/core/AnaConfig/mac/sample_config.config");
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

    //test: run xsec scaling stuff from here
    XSecScaling _xsecscaling;
    _xsecscaling.Configure(_cfgmgr.GetConfigMap());
    _xsecscaling.LoadInputGraphs();
    _xsecscaling.ComputeXSecRatio();

    TGraph *xsecratio = _xsecscaling.GetXSecRatio();
    std::cout<<xsecratio->GetN()<<std::endl;
    return true;
  }

  bool LEEMain::Finalize(){

    _datamgr.Close();

    return true;
  }
}//end namespace ubsens
#endif

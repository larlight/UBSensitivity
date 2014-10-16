#ifndef LEEMAIN_CC
#define LEEMAIN_CC

#include "LEEMain.hh"

namespace ubsens{
  

  bool LEEMain::Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap){

    try{
      _LEE_hist_name = util::FindInMapMap().GetParamValue(class_name(),std::string("LEEHistName"),_configMap);
      _LEE_hist_title = util::FindInMapMap().GetParamValue(class_name(),std::string("LEEHistTitle"),_configMap);
      _LEE_hist_bins_string =  util::FindInMapMap().GetParamValue(class_name(),std::string("LEEHistBins"),_configMap);
      _ElectronOrGamma = util::FindInMapMap().GetParamValue(class_name(),std::string("ElectronOrGamma"),_configMap);
      _data_file = util::FindInMapMap().GetParamValue(class_name(),std::string("DataFile"),_configMap);
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
    if(_data_file.empty()){
      std::cout<<class_name()<<" is using default data file."<<std::endl;
      _data_file="/Users/davidkaleko/UBSensitivity/single_electrons_allfiles.root";
    }
    if(_ElectronOrGamma.empty()){
      std::cout<<class_name()<<" is using default value for _ElectronOrGamma."<<std::endl;
      _ElectronOrGamma = "Electron";
    }

    //Convert "Electron" or "Gamma" string into a bool
    if(strcmp(_ElectronOrGamma.c_str(),"Electron")==0)
      _isElectronSample=true;
    else if (strcmp(_ElectronOrGamma.c_str(),"Gamma")==0)
      _isElectronSample=false;
    else{
      std::cerr<<"ERROR: use \"Electron\" or \"Gamma\" as ElectronOrGamma parameter in your config file."<<std::endl;
      return false;
    }


    return true;
  }


  bool LEEMain::Initialize(){

    //Configure the ConfigManager
    if(_cfg_file.empty()){
      std::cout<<"Set config file!"<<std::endl;
      return false;
    }
    _cfgmgr.LoadConfig(_cfg_file);

    //Configure the PlotWriter
    ConfigurePlotWriter();

    //Configure itself (LEEMain)
    Configure(_cfgmgr.GetConfigMap());

    //Save the config info to output file (must be done after configuring
    //PlotWriter, since that is what manages the output file)
    _cfgmgr.SaveConfig();
    //    _cfgmgr.DebugDump();

    //Configure the DataManager
    if(_data_file.empty()){
      std::cout<<"Set data file!"<<std::endl;
      return false;
    }
    _datamgr.SetIOMode(ubsens::data::DataManager::READ);
    _datamgr.AddInputFilename(_data_file);
    _datamgr.Open();
        
    InitializeHistos();

    return true;
  }

  bool LEEMain::Run(){

    data::EventRecord myEventRecord;

    std::vector<data::TruthShower> myTruthShowers;

    //loop over all events
    while(_datamgr.NextEntry()){
      
      myEventRecord.Reset();
      myTruthShowers.clear();

      myEventRecord = _datamgr.GetData();
      myTruthShowers= myEventRecord.TruthShowerCollection();

      if(myTruthShowers.size() > 1){
	std::cout << "wtf more than 1 truth shower?"
		  << " I thought you were generating single e or g's"
		  << ". Skipping this event." 
		  << std::endl;
	continue;
      }

      // Fill histo here
      // (truth shower energy is MeV, want GeV, so divide by 1000)
      double truth_energy_GEV = myTruthShowers.at(0).MotherMomentum().at(3)/1000.;
      _LEE_hist->Fill(truth_energy_GEV);

    }

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

  void LEEMain::InitializeHistos(){

    const std::vector<double> *xbins_vec = util::StringParser().ParseBinsString(_LEE_hist_bins_string);
    
    size_t nbins = xbins_vec->size();

    double xbins[nbins];

    //    std::cout<<"nbins = "<<nbins<<", xbins is: "<<std::endl;;

    for (size_t i = 0; i < nbins; i++){
      xbins[i]=xbins_vec->at(i);
      //      std::cout<<"xbins["<<i<<"] = "<<xbins[i]<<std::endl;
    }

    //_LEE_hist = new TH1F(_LEE_hist_name.c_str(),_LEE_hist_title.c_str(),10,0.2,3.0);
    _LEE_hist = new TH1F(_LEE_hist_name.c_str(),_LEE_hist_title.c_str(),nbins-1,xbins);
    


  }
}//end namespace ubsens
#endif

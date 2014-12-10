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
      _EnergyDefinition = util::FindInMapMap().GetParamValue(class_name(),std::string("EnergyDefinition"),_configMap);
      _data_file = util::FindInMapMap().GetParamValue(class_name(),std::string("DataFile"),_configMap);
      _n_evts_generated = util::FindInMapMap().GetParamValue(class_name(),std::string("NEventsGenerated"),_configMap);
      _true_MB_excess_evts = util::FindInMapMap().GetParamValue(class_name(),std::string("NTrueMBExcessEvts"),_configMap);
      _useSmearingString = util::FindInMapMap().GetParamValue(class_name(),std::string("UseSmearing"),_configMap);
      _OptionalWeight = util::FindInMapMap().GetParamValue(class_name(),std::string("OptionalWeight"),_configMap);
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kEXCEPTION, __FUNCTION__, e.what());
    }

    //If the config file has blank lines, use defaults
    if(_LEE_hist_name.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _LEE_hist_name.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _LEE_hist_name = "default_LEE_histname";
    }
    if(_LEE_hist_title.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _LEE_hist_title.";
 fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _LEE_hist_title = "Default LEE histogram title";
    }
    if(_LEE_hist_bins_string.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _LEE_hist_bins_string.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _LEE_hist_bins_string = "[0.2,0.48,0.76,1.04,1.32,1.6,1.88,2.16,2.44,2.72,3.0]";
    }
    if(_data_file.empty()){
      std::string msg = "";
      msg += class_name() + " is using default data file.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _data_file="/Users/davidkaleko/UBSensitivity/single_electrons_allfiles.root";
    }
    if(_ElectronOrGamma.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _ElectronOrGamma.";
 fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _ElectronOrGamma = "Electron";
    }
    
    //Convert "Electron" or "Gamma" string into a bool
    if(strcmp(_ElectronOrGamma.c_str(),"Electron")==0)
      _isElectronSample=true;
    else if (strcmp(_ElectronOrGamma.c_str(),"Gamma")==0)
      _isElectronSample=false;
    else{
      std::string msg = "";
      msg += "ERROR: use \"Electron\" or \"Gamma\" as ElectronOrGamma parameter in your config file.";
      fMsg.send(::ubsens::fmwk::msg::kERROR, __FUNCTION__, msg);
      return false;
    }


    if(_useSmearingString.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value (False) for _useSmearingString.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _useSmearingString = "False";
    }
    
    //Convert _useSmearingString to bool
    if(strcmp(_useSmearingString.c_str(),"True")==0)
      _useSmearing=true;
    else if (strcmp(_useSmearingString.c_str(),"False")==0)
      _useSmearing=false;
    else{
      std::string msg = "";
      msg += "ERROR: use \"True\" or \"False\" as UseSmearing parameter in your config file.";
      fMsg.send(::ubsens::fmwk::msg::kERROR, __FUNCTION__, msg);
      return false;
    }


    if(_EnergyDefinition.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _EnergyDefinition.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _EnergyDefinition = "TrueLepE";
    }
    if(_n_evts_generated.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _n_evts_generated.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _n_evts_generated = "50000";
    }
    if(_true_MB_excess_evts.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _true_MB_excess_evts.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _true_MB_excess_evts = "1212.114";
    }

    if(_OptionalWeight.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value (1.) for _OptionalWeight.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _OptionalWeight = "1.";
    }

    
    return true;
  }
  
  
  bool LEEMain::Initialize(){


    if(_cfg_file.empty()){
      std::string msg = "";
      msg += "Set the configuration file before running Initialize!";
      fMsg.send(::ubsens::fmwk::msg::kERROR, __FUNCTION__, msg);
      return false;
    }

    //Configure the ConfigManager
    _cfgmgr.LoadConfig(_cfg_file);

    //Configure the PlotWriter
    ConfigurePlotWriter();

    //Configure itself (LEEMain)
    Configure(_cfgmgr.GetConfigMap());

    //Save the config info to output file (must be done after configuring
    //PlotWriter, since that is what manages the output file)
    _cfgmgr.SaveConfig();
    //    _cfgmgr.DebugDump();

    //Configure the DataManager (note, _data_file gets set by Configure())
    if(_data_file.empty()){
      std::string msg = "";
      msg += "Set the data file before running Initialize!";
      fMsg.send(::ubsens::fmwk::msg::kERROR, __FUNCTION__, msg);
      return false;
    }

    _datamgr.SetIOMode(ubsens::data::DataManager::READ);
    _datamgr.AddInputFilename(_data_file);
    _datamgr.Open();
        
    InitializeScalings();

    InitializeHistos();

    InitializeTTree();

    return true;
  }

  bool LEEMain::Run(){

    data::EventRecord myEventRecord;

    std::vector<data::TruthShower> myTruthShowers;

    ////////////////
    // EVENT LOOP //
    ////////////////
    while(_datamgr.NextEntry()){
      
      myEventRecord.Reset();
      myTruthShowers.clear();

      myEventRecord = _datamgr.GetData();
      myTruthShowers= myEventRecord.TruthShowerCollection();

      if(myTruthShowers.size() > 1){
	std::string msg = "";
	msg += "Why is there more than 1 truth shower? ";
	msg += "I thought you were generating single e or g's. ";
	msg += "Skipping this event.";
	fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
	continue;
      }
      

      //Debug: save coordinates of selected events to cross-check fid. vol
      //      _x->Fill(myTruthShowers.at(0).MotherVtx().at(0));
      //      _y->Fill(myTruthShowers.at(0).MotherVtx().at(1));
      //      _z->Fill(myTruthShowers.at(0).MotherVtx().at(2));


      double true_lept_E_MEV = myTruthShowers.at(0).MotherMomentum().at(3);
      double true_lept_E_GEV = true_lept_E_MEV/1000.; 
      double correlated_nu_energy_GEV = _nulec.NuEFromLeptE(true_lept_E_GEV);

      // Weight event by all scaling factors
      double weight = 1.;

      // POT weight (implement this w/ Configure() function, using default now)
      weight *= _potscaling.GetPOTScaling();

      // Tonnage weight (implement this w/ Configure() function, default now):
      weight *= _tonnagescaling.GetTonnageScaling();

      // X-Sec weight:
      weight *= _xsecscaling.GetXSecRatio()->Eval(correlated_nu_energy_GEV);

      // Flux weight:
      weight *= _fluxscaling.GetFluxRatio()->Eval(correlated_nu_energy_GEV);

      // Efficiency weight:
      weight *= _effscaling.GetEfficiencyGraph()->Eval(true_lept_E_GEV);

      // Overall normalization to true MB excess events
      weight *= atof(_true_MB_excess_evts.c_str()) / atof(_n_evts_generated.c_str());

      // Optional additional weighting factor:
      weight *= atof(_OptionalWeight.c_str());

      //Smear the final lepton energy by 15%/sqrt(E)
      if(_useSmearing)
	true_lept_E_GEV = _energysmear.SmearEnergy(true_lept_E_GEV);

      /// Formula takes in MeV energy and momentum, returns GeV energy
      double e_ccqe = util::ECCQECalculator::ComputeECCQE(true_lept_E_GEV*1000.,myTruthShowers.at(0).MotherMomentum());

      if(_EnergyDefinition == "ECCQE")
	_LEE_hist->Fill(e_ccqe,weight);
      else if (_EnergyDefinition == "TrueLepE")
	_LEE_hist->Fill(true_lept_E_GEV,weight);
      else{
	std::string msg = "";
	msg += "ERROR: Your energy definition is not one of the allowed values in the configuration file, and apparently wasn't set to a default.";
	fMsg.send(::ubsens::fmwk::msg::kERROR, __FUNCTION__, msg);
	return false;
      }

      //Fill ttree stuff
      _tree_lept_E = true_lept_E_GEV;
      _tree_ccqe_E = e_ccqe;
      _tree_weight= weight;
      _LEE_event_tree->Fill();
    }
    
    return true;
  }
    
  bool LEEMain::Finalize(){

    _datamgr.Close();

    // Set errors on all LEE hist bins to zero for now
    // Until I figure out how to actually compute them
    util::HistManip hm;
    hm.SetZeroErrors(*_LEE_hist);

    // Save LEE Hist to output file
    util::PlotWriter::GetME()->Write(_LEE_hist,class_name());

    //Debug: save coordinates of selected events to cross-check fid. vol
    //    util::PlotWriter::GetME()->Write(_x,class_name());
    //    util::PlotWriter::GetME()->Write(_y,class_name());
    //    util::PlotWriter::GetME()->Write(_z,class_name());

    //Make a FinalPlotter instance and have it do its magic
    FinalPlotter fp;
    fp.Configure(_cfgmgr.GetConfigMap());
    fp.LoadLEEHisto(_LEE_hist);
    fp.MakeStackedHisto();
    fp.WritePlots();

    // Save ttree to output file
    TObjString *_README = new TObjString("Note: For this event TTree, it includes only events that passed event selection cuts in MicroBooNE. That means, if you loop through and fill a histogram with energy, weighted by UB weight, then you will reproduce the LEE histogram for that data sample's fiducial volume definition in MicroBooNE. If you want to make this histogram for LAr1ND, you will need to get the TTree with a weight calculated using the LAr1ND flux (and if available, the LAr1ND fiducial volume... if the LAr1ND weight is not including the LAr1ND fiducial volume, THEN ADDITIONALLY SCALE THIS TO THE LAr1ND FIDUCIAL VOLUME.) If you do not know what fiducial volume was used in MicroBooNE to fill this tree, then the LAr1ND weight is useless.");
    if(_LEE_event_tree){
      util::PlotWriter::GetME()->Write(_LEE_event_tree,class_name());
      util::PlotWriter::GetME()->Write(_README,class_name());
    }

    delete _LEE_hist;

    delete _LEE_event_tree;
    delete _README;
    //Write the plots from EnergySmear module
    _energysmear.WritePlots();

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

    for (size_t i = 0; i < nbins; i++){
      xbins[i]=xbins_vec->at(i);
    }

    _LEE_hist = new TH1F(_LEE_hist_name.c_str(),_LEE_hist_title.c_str(),nbins-1,xbins);
    
    //Debug: save coordinates of selected events to cross-check fid. vol
    //    _x = new TH1F("x","selected x coords",100,0,500);
    //    _y = new TH1F("y","selected y coords",100,-200,200);
    //    _z = new TH1F("z","selected z coords",100,0,1500);
    
  }

  void LEEMain::InitializeTTree(){

    if(!_LEE_event_tree){
      _LEE_event_tree = new TTree("LEE_event_tree","");
      _LEE_event_tree->Branch("E_lept",&_tree_lept_E,"E_lept/D");
      _LEE_event_tree->Branch("E_ccqe",&_tree_ccqe_E,"E_ccqe/D");
      _LEE_event_tree->Branch("weight_UBFidVol",&_tree_weight,"weight_UBFidVol/D");
    }


  }
  void LEEMain::InitializeScalings(){

    //NuLeptECorrelation stuff here
    _nulec.Configure(_cfgmgr.GetConfigMap());
    _nulec.LoadInputTH2F();
    _nulec.WritePlots();
    
    //XSecScaling stuff here
    _xsecscaling.Configure(_cfgmgr.GetConfigMap());
    //    _xsecscaling.PrintConfig();
    _xsecscaling.LoadInputGraphs();
    _xsecscaling.ComputeXSecRatio();
    _xsecscaling.WritePlots();

    //FluxScaling stuff here
    _fluxscaling.Configure(_cfgmgr.GetConfigMap());
    _fluxscaling.LoadInputGraphs();
    _fluxscaling.ComputeFluxRatio();
    _fluxscaling.WritePlots();

    //POT scaling stuff here (implement this)
    _potscaling.Configure(_cfgmgr.GetConfigMap());

    //Tonnage scaling stuff here (implement this)
    _tonnagescaling.Configure(_cfgmgr.GetConfigMap());

    //Efficiency scaling stuff here:
    //todo: uncomment this when efficiency is more complex than just flat 80%
    //_effscaling.Configure(_cfgmgr.GetConfigMap());
    _effscaling.MakeGraph();
    _effscaling.WritePlots();

    //Energy smearing stuff here:
    _energysmear.Initialize();
    //Do the WritePlots for energysmear in finalize, one plot depends on the
    //events fed into energysmear

  }

}//end namespace ubsens
#endif

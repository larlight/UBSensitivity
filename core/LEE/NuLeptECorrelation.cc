#ifndef NULEPTECORRELATION_CC
#define NULEPTECORRELATION_CC

#include "NuLeptECorrelation.hh"

namespace ubsens{

  bool NuLeptECorrelation::Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap){

    try{
      _my_fosc_filename = util::FindInMapMap().GetParamValue(class_name(),std::string("FullOscFileName"),_configMap);
      _my_th2f_name = util::FindInMapMap().GetParamValue(class_name(),std::string("TH2FName"),_configMap);
      _n_draws_to_avg = util::FindInMapMap().GetParamValue(class_name(),std::string("NDrawsToAvg"),_configMap);
      
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kEXCEPTION, __FUNCTION__, e.what());
    }
    
    //If the config file has blank lines, use defaults
    if(_my_fosc_filename.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _my_fosc_filename.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _my_fosc_filename = "/Users/davidkaleko/Data/LEE/combined_ntuple_470m_nu_fosc_CC_nu_lept_energycorrelation.root";
    }
    if(_my_th2f_name.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _my_th2f_name.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _my_th2f_name = "fosc_isCC_enugen_vs_Elep";
    }
    if(_n_draws_to_avg.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _n_draws_to_avg.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _n_draws_to_avg = "1";
    }
    //convert string to size_t (int)
    n_draws_to_avg = stoi(_n_draws_to_avg);

    return true;
  }
  

  bool NuLeptECorrelation::LoadInputTH2F(){

    util::PlotReader::GetME()->Reset();

    util::PlotReader::GetME()->SetFileName(_my_fosc_filename);
    util::PlotReader::GetME()->SetObjectName(_my_th2f_name);
    _my_th2f = (TH2F*)util::PlotReader::GetME()->GetObject();

    return true;
  }


  double NuLeptECorrelation::NuEFromLeptE(double lept_e){

    //For good measure, reset slice before starting
    if( _my_tmp_slice )
      _my_tmp_slice->Reset();
 
    //check that _my_th2f is loaded, etc
    if( !_my_th2f ){
      std::ostringstream msg;
      msg << "<<" << class_name() <<"::"<< __FUNCTION__ <<">> "
	  << "ERROR: You need to load in the TH2F from the fullosc file "
	  << "if you want to correlate lepton energy with nu energy!"
	  << std::endl;
      throw fmwk::FMWKException(msg.str());
      return -1;
    }

    //Find the x-bin # that corresponds to this lepton energy
    Int_t bin = _my_th2f->GetXaxis()->FindBin(lept_e);

    //Draw 1D projection of this bin from 2D histogram
    _my_tmp_slice = _my_th2f->ProjectionY("_my_tmp_slice",bin,bin);
    
    //Pull random from this 1D distribution
    double generated_nu_E = 0;
    for (size_t i = 0; i < n_draws_to_avg; ++i)
      generated_nu_E += _my_tmp_slice->GetRandom();
    generated_nu_E /= n_draws_to_avg;

    //Return that random value
    return generated_nu_E;

  }

  void NuLeptECorrelation::WritePlots(){
   
    //check that _my_th2f is loaded, etc
    if( !_my_th2f ){
      std::ostringstream msg;
      msg << "<<" << __FUNCTION__ <<">> "
	  << "ERROR: You need to load in the TH2F from the fullosc file "
	  << "if you want to correlate lepton energy with nu energy!"
	  << std::endl;
      throw fmwk::FMWKException(msg.str());
    }
    
    try{
      util::PlotWriter::GetME()->Write(_my_th2f,class_name().c_str());
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kEXCEPTION, __FUNCTION__, e.what());
    }
  
  }
  
}//end namespace ubsens
#endif

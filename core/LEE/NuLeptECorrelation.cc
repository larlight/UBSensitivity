#ifndef NULEPTECORRELATION_CC
#define NULEPTECORRELATION_CC

#include "NuLeptECorrelation.hh"

namespace ubsens{

  bool NuLeptECorrelation::LoadInputTH2F(){

    _my_fosc_filename = "/Users/davidkaleko/Data/LEE/combined_ntuple_470m_nu_fosc_CC_nu_lept_energycorrelation.root";
    _my_th2f_name = "fosc_isCC_enugen_vs_Elep";

    util::PlotReader::GetME()->Reset();

    util::PlotReader::GetME()->SetFileName(_my_fosc_filename);
    util::PlotReader::GetME()->SetPlotName(_my_th2f_name);
    _my_th2f = util::PlotReader::GetME()->GetTH2F();

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
    double generated_nu_E = _my_tmp_slice->GetRandom();

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
      std::cout<<"Caught an exception! It is "<<e.what()<<std::endl;
    }
  
  }
  
}//end namespace ubsens
#endif

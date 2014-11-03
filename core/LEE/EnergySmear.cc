#ifndef ENERGYSMEAR_CC
#define ENERGYSMEAR_CC

#include "EnergySmear.hh"

namespace ubsens{

  
  double EnergySmear::SmearEnergy(double lept_energy_GEV){
    
    if(!mysmearing) {
      std::ostringstream msg;
      msg << "<<" << class_name() << "::" << __FUNCTION__ <<">> "
	  << "ERROR: You need to initialize EnergySmear before you can use it."
	  << std::endl;
      throw fmwk::FMWKException(msg.str());
      
      return -1;
    }
    
    double gaus_width = mysmearing->Eval(lept_energy_GEV);

    double smeared_E = gRandom->Gaus(lept_energy_GEV,gaus_width*lept_energy_GEV);
    //This 2D plot is just for cross-checks, isn't used for anything
    correlation->Fill(smeared_E,lept_energy_GEV);

    return smeared_E;
    
  }
  
  void EnergySmear::Initialize(){
    
    mysmearing = new TF1("mysmearing","0.15/pow(x,0.5)",0.1,3);
    correlation = new TH2F("correlation","Smearing Correlation CrossCheck;Smeared lepton energy by .15/sqrt(E) [GeV];True lepton energy [GeV]",100,0,1.5,100,0,1.5);    

  }
  
  void EnergySmear::WritePlots(){

    if(!mysmearing || !correlation) {
      std::ostringstream msg;
      msg << "<<" << class_name() << "::" << __FUNCTION__ <<">> "
	  << "ERROR: You need to initialize EnergySmear before you can write stuff."
	  << std::endl;
      throw fmwk::FMWKException(msg.str());
    }
    
    try{
      util::PlotWriter::GetME()->Write(mysmearing,class_name().c_str());
      util::PlotWriter::GetME()->Write(correlation,class_name().c_str());
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kERROR,e.what());
    }
    
  }//end WritePlots
  
}//end namespace ubsens

#endif

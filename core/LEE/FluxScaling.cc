#ifndef FLUXSCALING_CC
#define FLUXSCALING_CC

#include "FluxScaling.hh"

namespace ubsens{


  bool FluxScaling::Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap){
        
    try{
      _my_flux_input_filename = util::FindInMapMap().GetParamValue(class_name(),std::string("DetectorFluxFile"),_configMap);
      _my_flux_TGraph_name = util::FindInMapMap().GetParamValue(class_name(),std::string("DetectorGraphName"),_configMap);
      _MB_flux_input_filename = util::FindInMapMap().GetParamValue(class_name(),std::string("MBFluxFile"),_configMap);
      _MB_flux_TGraph_name = util::FindInMapMap().GetParamValue(class_name(),std::string("MBGraphName"),_configMap);

    }
    catch (fmwk::FMWKException &e) {
      std::cout<<e.what()<<std::endl;
    }
   

    //If the config file has blank lines, use defaults
    if(_my_flux_input_filename.empty()){
      std::cout<<class_name()<<" is using default value for _my_flux_input_filename."<<std::endl;
      _my_flux_input_filename = "/Users/davidkaleko/Data/LEE/total_nu_flux_ub_mb.root";
    }
    if(_my_flux_TGraph_name.empty()){
      std::cout<<class_name()<<" is using default value for _my_flux_TGraph_name."<<std::endl;
      _my_flux_TGraph_name = "uB_total_nu_flux";
    }
    if(_MB_flux_input_filename.empty()){
      std::cout<<class_name()<<" is using default value for _MB_flux_input_filename."<<std::endl;
      _MB_flux_input_filename = "/Users/davidkaleko/Data/LEE/total_nu_flux_ub_mb.root";
    }
    if(_MB_flux_TGraph_name.empty()){
      std::cout<<class_name()<<" is using default value for _MB_flux_TGraph_name."<<std::endl;
      _MB_flux_TGraph_name = "MB_total_nu_flux";
    }

    return true;
  };
  

  bool FluxScaling::LoadInputGraphs(){
    /*
    //temporary... will set by hand later
    _my_flux_input_filename = "/Users/davidkaleko/Data/LEE/total_nu_flux_ub_mb.root";
    _MB_flux_input_filename = "/Users/davidkaleko/Data/LEE/total_nu_flux_ub_mb.root";
    _my_flux_TGraph_name = "uB_total_nu_flux";
    _MB_flux_TGraph_name = "MB_total_nu_flux";
    */
    util::PlotReader::GetME()->Reset();
    
    util::PlotReader::GetME()->SetFileName(_my_flux_input_filename);
    util::PlotReader::GetME()->SetPlotName(_my_flux_TGraph_name);
    _my_flux = util::PlotReader::GetME()->GetGraph();
    util::PlotReader::GetME()->SetFileName(_MB_flux_input_filename);
    util::PlotReader::GetME()->SetPlotName(_MB_flux_TGraph_name);
    _MB_flux = util::PlotReader::GetME()->GetGraph();
    

    return true;
  }
  
  
  void FluxScaling::ComputeFluxRatio(){
    
    if(!_my_flux || !_MB_flux){
	std::ostringstream msg;
	msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	    << "ERROR: You need to get the flux graphs/files first!"
	    << std::endl;
	throw fmwk::FMWKException(msg.str());

      return;
    }

    _flux_ratio = new TGraph();
    _flux_ratio->SetName("flux_ratio");
    _flux_ratio->Set(0);
    
    //ratio graph should have same # of points as input graph with most points
    //for now hard-coding as using the points from the miniboone graph
    for(size_t i = 0; i < _MB_flux->GetN(); ++i){
      
      double myx = _MB_flux->GetX()[i];
      
      //avoid divide-by-zero errors
      if( !_MB_flux->GetY()[i] ) continue;
      
      double myy = _my_flux->Eval(myx)/_MB_flux->GetY()[i];
      
      _flux_ratio->SetPoint(i,myx,myy);
      
    }
  }
  
  void FluxScaling::WritePlots(){

    if ( !_my_flux || !_MB_flux || !_flux_ratio ){
      std::ostringstream msg;
      msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	  << "ERROR: Either flux filenames aren't set, graph names aren't set,"
	  << " or you haven't yet computed the ratio graph."
	  << std::endl;
      throw fmwk::FMWKException(msg.str());

      return;
    }

    try{
      util::PlotWriter::GetME()->Write(_my_flux,class_name().c_str());
      util::PlotWriter::GetME()->Write(_MB_flux,class_name().c_str());
      util::PlotWriter::GetME()->Write(_flux_ratio,class_name().c_str());
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kERROR,e.what());
    }
  

  }

} //end namespace ubsens
#endif

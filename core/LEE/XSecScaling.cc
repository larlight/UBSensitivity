#ifndef XSECSCALING_CC
#define XSECSCALING_CC

#include "XSecScaling.hh"

namespace ubsens{

  bool XSecScaling::Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap){
        
    try{
      _my_xsec_input_filename = util::FindInMapMap().GetParamValue(class_name(),std::string("MyInFileName"),_configMap);
      _my_xsec_TGraph_name = util::FindInMapMap().GetParamValue(class_name(),std::string("MyGraphName"),_configMap);
      _MB_xsec_input_filename = util::FindInMapMap().GetParamValue(class_name(),std::string("MBInFileName"),_configMap);
      _MB_xsec_TGraph_name = util::FindInMapMap().GetParamValue(class_name(),std::string("MBGraphName"),_configMap);

    }
    catch (fmwk::FMWKException &e) {
      std::cout<<e.what()<<std::endl;
    }
   
    //If the config file has blank lines, use defaults
    if(_my_xsec_input_filename.empty()){
      std::cout<<class_name()<<" is using default value for _my_xsec_input_filename."<<std::endl;
      _my_xsec_input_filename = "/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root";
    }
    if(_my_xsec_TGraph_name.empty()){
      std::cout<<class_name()<<" is using default value for _my_xsec_TGraph_name."<<std::endl;
      _my_xsec_TGraph_name = "genie_total_cc_graph";
    }
    if(_MB_xsec_input_filename.empty()){
      std::cout<<class_name()<<" is using default value for _MB_xsec_input_filename."<<std::endl;
      _MB_xsec_input_filename = "/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root";
    }
    if(_MB_xsec_TGraph_name.empty()){
      std::cout<<class_name()<<" is using default value for _MB_xsec_TGraph_name."<<std::endl;
      _MB_xsec_TGraph_name = "nuance_total_cc_graph";
    }

    return true;
  };
  
  bool XSecScaling::LoadInputGraphs(){
    
    util::PlotReader::GetME()->Reset();
    
    util::PlotReader::GetME()->SetFileName(_my_xsec_input_filename);
    util::PlotReader::GetME()->SetObjectName(_my_xsec_TGraph_name);
    _my_xsec = (TGraph*)util::PlotReader::GetME()->GetObject();
    util::PlotReader::GetME()->SetFileName(_MB_xsec_input_filename);
    util::PlotReader::GetME()->SetObjectName(_MB_xsec_TGraph_name);
    _MB_xsec = (TGraph*)util::PlotReader::GetME()->GetObject();
    
    return true;
  }
  

  void XSecScaling::ComputeXSecRatio(){
    
    if(!_my_xsec || !_MB_xsec){
      std::ostringstream msg;
      msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	  << "ERROR: You need to set the cross section graphs/files first!"
	  << std::endl;
      throw fmwk::FMWKException(msg.str());

      return;
    }
    
    if(!_my_ntargetspergram || !_MB_ntargetspergram){
      std::ostringstream msg;
      msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	  << "ERROR: You need to set the n targets per gram for both detectors!"
	  << std::endl;
      throw fmwk::FMWKException(msg.str());
      
      return;
    }
    
    _xsec_ratio = new TGraph();
    _xsec_ratio->SetName("xsec_ratio");
    
    //ratio graph should have same # of points as input graph with most points
    //for now hard-coding as using the points from the miniboone graph
    int point_counter = 0;
    
    for(size_t i = 0; i < _MB_xsec->GetN(); ++i){
      
      double myx = _MB_xsec->GetX()[i];
      
      //avoid divide-by-zero errors
      if( !_MB_xsec->GetY()[i] ) continue;
      
      double myy = _my_xsec->Eval(myx)/_MB_xsec->GetY()[i];
      
      //multiply by n targets per gram... that's included in xsecscaling!
      myy *= ( _my_ntargetspergram / _MB_ntargetspergram );
      
      //for now hard code: the ratio BLOWS UP at low energy, so have cut
      //on ratio not being huge
      //this is a PHYSICS DECISION that I need to make here
      //for now, setting ratio to be 1.575 up until it deviates
      //this is HARD CODING that i should probably fix
      if(myy > 1.575) myy = 1.575;
      
      _xsec_ratio->SetPoint(point_counter,myx,myy);
      point_counter++;
      
    }
  }
  
  void XSecScaling::WritePlots(){

    if ( _my_xsec_input_filename == "" ||
	 _MB_xsec_input_filename == "" ||
	 _my_xsec_TGraph_name == "" ||
	 _MB_xsec_TGraph_name == "" ||
	 !_xsec_ratio ){
      std::ostringstream msg;
      msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	  << "ERROR: Either xsec filenames aren't set, graph names aren't set,"
	  << " or you haven't yet computed the ratio graph."
	  << std::endl;
      throw fmwk::FMWKException(msg.str());

      return;
    }

    try{
      util::PlotWriter::GetME()->Write(_my_xsec,class_name().c_str());
      util::PlotWriter::GetME()->Write(_MB_xsec,class_name().c_str());
      util::PlotWriter::GetME()->Write(_xsec_ratio,class_name().c_str());
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kERROR,e.what());
    }
  


    
  }

}//end namespace ubsens

#endif

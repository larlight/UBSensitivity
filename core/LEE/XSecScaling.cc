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
      _xsec_ratio_maximum = util::FindInMapMap().GetParamValue(class_name(),std::string("RatioCutoffMax"),_configMap);
      _xsec_ratio_minimum = util::FindInMapMap().GetParamValue(class_name(),std::string("RatioCutoffMin"),_configMap);
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(fmwk::msg::kEXCEPTION, __FUNCTION__, e.what());
    }
   
    //If the config file has blank lines, use defaults
    if(_my_xsec_input_filename.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _my_xsec_input_filename.";
      fMsg.send(fmwk::msg::kWARNING, __FUNCTION__, msg);
      _my_xsec_input_filename = "/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root";
    }
    if(_my_xsec_TGraph_name.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _my_xsec_TGraph_name.";
      fMsg.send(fmwk::msg::kWARNING, __FUNCTION__, msg);
      _my_xsec_TGraph_name = "genie_total_cc_graph";
    }
    if(_MB_xsec_input_filename.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _MB_xsec_input_filename.";
      fMsg.send(fmwk::msg::kWARNING, __FUNCTION__, msg);
      _MB_xsec_input_filename = "/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root";
    }
    if(_MB_xsec_TGraph_name.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _MB_xsec_TGraph_name.";
      fMsg.send(fmwk::msg::kWARNING, __FUNCTION__, msg);
      _MB_xsec_TGraph_name = "nuance_total_cc_graph";
    }
    if(_xsec_ratio_maximum.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _xsec_ratio_maximum.";
      fMsg.send(fmwk::msg::kWARNING, __FUNCTION__, msg);
      _xsec_ratio_maximum = "99999.";
    }
    if(_xsec_ratio_minimum.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _xsec_ratio_minimum.";
      fMsg.send(fmwk::msg::kWARNING, __FUNCTION__, msg);
      _xsec_ratio_minimum = "0.";
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

    _xsec_ratio = _tgm->DivideTwoGraphs(_my_xsec,_MB_xsec);
    _xsec_ratio->SetName("xsec_ratio");


    //Scale ratio by targets-per-gram ratio... that's included in xsecscaling!
    double scaling_factor = ( _my_ntargetspergram / _MB_ntargetspergram );
    _tgm->ScaleGraph(*(_xsec_ratio),scaling_factor);


    //Some times the ratio BLOWS UP at low energy, so have cut
    //on ratio not being huge (or too tiny, I guess).
    //These cutoff values are included in the .config file used
    //Enforce xsec ratio minimum and maximum here:
    //Note: enforce max/min of ratio AFTER scaling by ntargets-per-gram, by convention
    //(otherwise the max/min should be defined w.r.t. before ntargets-per-gram scaling)
    for(size_t i = 0; i < _xsec_ratio->GetN(); ++i){
      if(_xsec_ratio->GetY()[i] > atof(_xsec_ratio_maximum.c_str())){
	//	std::cout<<"Point ("<<_xsec_ratio->GetX()[i]<<","<<_xsec_ratio->GetY()[i]<<") "
	//		 <<"is GREATER than the maximum of "<<atof(_xsec_ratio_maximum.c_str())
	//		 <<" so I'm setting the point to : ("
	//		 << _xsec_ratio->GetX()[i]<<","<<atof(_xsec_ratio_maximum.c_str())<<")"<<std::endl;
	_xsec_ratio->SetPoint(i,_xsec_ratio->GetX()[i],atof(_xsec_ratio_maximum.c_str()));
      }
      else if(_xsec_ratio->GetY()[i] < atof(_xsec_ratio_minimum.c_str())){
	//	std::cout<<"Point ("<<_xsec_ratio->GetX()[i]<<","<<_xsec_ratio->GetY()[i]<<") "
	//		 <<"is LESS than the minimum of "<<atof(_xsec_ratio_minimum.c_str())
	//		 <<" so I'm setting the point to : ("
	//		 <<_xsec_ratio->GetX()[i]<<","<<atof(_xsec_ratio_minimum.c_str())<<")"<<std::endl;
	_xsec_ratio->SetPoint(i,_xsec_ratio->GetX()[i],atof(_xsec_ratio_minimum.c_str()));
      }
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

  void XSecScaling::Reset(){

      _my_xsec = 0;
      _MB_xsec = 0;
      _xsec_ratio = 0;
      _my_xsec_input_filename = "";
      _my_xsec_TGraph_name = "";
      _MB_xsec_input_filename = "";
      _MB_xsec_TGraph_name = "";
      _my_ntargetspergram = geo::UB_TARGETS_PER_GRAM;
      _MB_ntargetspergram = geo::MINIBOONE_TARGETS_PER_GRAM;
      _xsec_ratio_maximum="99999.";
      _xsec_ratio_minimum="0.";
      _name = "XSecScaling";
  }

  void XSecScaling::PrintConfig(){

    std::cout<<" ---- PRINTING XSECSCALING CONFIGURATION ---- "<<std::endl;
    std::cout<<"my filename: "<<_my_xsec_input_filename.c_str()<<std::endl;
    std::cout<<"my graphname:"<<_my_xsec_TGraph_name.c_str()<<std::endl;
    std::cout<<"MB filename: "<<_MB_xsec_input_filename.c_str()<<std::endl;
    std::cout<<"MB graphname:"<<_MB_xsec_TGraph_name.c_str()<<std::endl;
    
    std::cout<<"My tgt_per_g:"<< _my_ntargetspergram<<std::endl;
    std::cout<<"MB tgt_per_g:"<<_MB_ntargetspergram<<std::endl;

    std::cout<<"ratio max   :"<<_xsec_ratio_maximum.c_str()<<std::endl;
    std::cout<<"ratio min   :"<<_xsec_ratio_minimum.c_str()<<std::endl;
    std::cout<<" ---- PRINTED XSECSCALING CONFIGURATION  ---- "<<std::endl;

  }
}//end namespace ubsens

#endif

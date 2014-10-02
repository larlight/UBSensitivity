#ifndef XSECSCALING_CC
#define XSECSCALING_CC

#include "XSecScaling.hh"

bool XSecScaling::LoadInputGraphs(){

  //temporary... will set by hand later
  _my_xsec_input_filename = "/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root";
  _MB_xsec_input_filename = "/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root";
  _my_xsec_TGraph_name = "genie_total_cc_graph";
  _MB_xsec_TGraph_name = "nuance_total_cc_graph";

  TFile* f_my = new TFile(_my_xsec_input_filename.c_str(),"READ");
  TFile* f_MB = new TFile(_MB_xsec_input_filename.c_str(),"READ");

  if(!f_my){
    std::cerr<<Form("ERROR: File %s does not exist!\n",_my_xsec_input_filename.c_str());
    return false;
  }
  if(!f_MB){
    std::cerr<<Form("ERROR: File %s does not exist!\n",_MB_xsec_input_filename.c_str());
    return false;
  }
  if(!f_my->GetListOfKeys()->Contains(_my_xsec_TGraph_name.c_str())){
    std::cerr<<Form("ERROR: File %s does not contain TGraph %s!\n",_my_xsec_input_filename.c_str(),_my_xsec_TGraph_name.c_str());
    return false;
  }
  if(!f_MB->GetListOfKeys()->Contains(_MB_xsec_TGraph_name.c_str())){
    std::cerr<<Form("ERROR: File %s does not contain TGraph %s!\n",_MB_xsec_input_filename.c_str(),_MB_xsec_TGraph_name.c_str());
    return false;
  }
     
  _my_xsec = (TGraph*)f_my->Get(_my_xsec_TGraph_name.c_str());
  _MB_xsec = (TGraph*)f_my->Get(_my_xsec_TGraph_name.c_str());
  
  return true;
}


void XSecScaling::ComputeXSecRatio(){

  if(!_my_xsec || !_MB_xsec){
    std::cerr<<"ERROR: You need to set the cross section graphs/files first!"<<std::endl;
    return;
  }

  _xsec_ratio->Set(0);

  //ratio graph should have same # of points as input graph with most points
  //for now hard-coding as using the points from the miniboone graph
  for(size_t i = 0; i < _MB_xsec->GetN(); ++i){

    double myx = _MB_xsec->GetX()[i];

    //avoid divide-by-zero errors
    if( !_MB_xsec->GetY()[i] ) continue;

    double myy = _my_xsec->Eval(myx)/_MB_xsec->GetY()[i];

    _xsec_ratio->SetPoint(i,myx,myy);

  }
}


#endif

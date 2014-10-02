#ifndef XSECSCALING_CC
#define XSECSCALING_CC

#include "XSecScaling.hh"

bool XSecScaling::LoadInputGraphs(){

  //temporary... will set by hand later
  _my_xsec_input_filename = "/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root";
  _MB_xsec_input_filename = "/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root";
  _my_xsec_TGraph_name = "genie_total_cc_graph";
  _MB_xsec_TGraph_name = "nuance_total_cc_graph";

  util::TGraphReader::GetME()->SetFileName(_my_xsec_input_filename);
  util::TGraphReader::GetME()->SetGraphName(_my_xsec_TGraph_name);
  _my_xsec = util::TGraphReader::GetME()->GetGraph();
  util::TGraphReader::GetME()->SetFileName(_MB_xsec_input_filename);
  util::TGraphReader::GetME()->SetGraphName(_MB_xsec_TGraph_name);
  _MB_xsec = util::TGraphReader::GetME()->GetGraph();

  return true;
}


void XSecScaling::ComputeXSecRatio(){

  if(!_my_xsec || !_MB_xsec){
    std::cerr<<"ERROR: You need to set the cross section graphs/files first!"<<std::endl;
    return;
  }

  if(!_my_ntargetspergram || !_MB_ntargetspergram){
    std::cerr<<"ERROR: You need to set the n targets per gram for both detectors!"<<std::endl;
    return;
  }

  _xsec_ratio = new TGraph();

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


#endif

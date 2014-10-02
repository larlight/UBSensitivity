#ifndef FLUXSCALING_CC
#define FLUXSCALING_CC

#include "FluxScaling.hh"


bool FluxScaling::LoadInputGraphs(){

  //temporary... will set by hand later
  _my_flux_input_filename = "/Users/davidkaleko/Data/LEE/total_nu_flux_ub_mb.root";
  _MB_flux_input_filename = "/Users/davidkaleko/Data/LEE/total_nu_flux_ub_mb.root";
  _my_flux_TGraph_name = "uB_total_nu_flux";
  _MB_flux_TGraph_name = "MB_total_nu_flux";

  util::TGraphReader::GetME()->SetFileName(_my_flux_input_filename);
  util::TGraphReader::GetME()->SetGraphName(_my_flux_TGraph_name);
  _my_flux = util::TGraphReader::GetME()->GetGraph();
  util::TGraphReader::GetME()->SetFileName(_MB_flux_input_filename);
  util::TGraphReader::GetME()->SetGraphName(_MB_flux_TGraph_name);
  _MB_flux = util::TGraphReader::GetME()->GetGraph();

  return true;
}


void FluxScaling::ComputeFluxRatio(){

  if(!_my_flux || !_MB_flux){
    std::cerr<<"ERROR: You need to set the cross section graphs/files first!"<<std::endl;
    return;
  }

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

#endif

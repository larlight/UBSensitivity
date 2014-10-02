#ifndef TGRAPHREADER_CC
#define TGRAPHREADER_CC

#include "TGraphReader.hh"

TGraphReader* TGraphReader::_me = 0;

TGraph* TGraphReader::GetGraph(){

  //temporary... will set by hand later
  _filename = "/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root";
  _graphname = "nuance_total_cc_graph";
  
  TFile* f = new TFile(_filename.c_str(),"READ");
  
  TGraph* result = NULL;

  if(!f){
    std::cerr<<Form("ERROR: File %s does not exist!\n",_filename.c_str());
    return result;
  }
  if(!f->GetListOfKeys()->Contains(_graphname.c_str())){
    std::cerr<<Form("ERROR: File %s does not contain TGraph %s!\n",_filename.c_str(),_graphname.c_str());
    return result;
  }
     
  result = (TGraph*)f->Get(_graphname.c_str());

  return result;

}

#endif

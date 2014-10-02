#ifndef TGRAPHREADER_CC
#define TGRAPHREADER_CC

#include "TGraphReader.hh"

namespace util{
  
  TGraphReader* TGraphReader::_me = 0;
  
  TGraph* TGraphReader::GetGraph(){
    
    TGraph* result = NULL;

    if(_filename.empty() || _graphname.empty()){
      std::cerr<<"ERROR: TGraphReader needs you to set filename and graph name."<<std::endl;
      return result;
    }
        
    TFile* f = new TFile(_filename.c_str(),"READ");
        
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

}//end namespace util
#endif

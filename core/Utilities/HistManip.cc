#ifndef HISTMANIP_CC
#define HISTMANIP_CC

#include "HistManip.hh"
namespace ubsens{

  namespace util{
    
    bool HistManip::CheckBins(const TH1F * const hist, const std::vector<double> *nbins){
      
      bool debug_me = false;
      
      //Check to make sure each of the bin low boundaries listed in nbins
      //matches with a bin already in hist
      if(debug_me) std::cout<<"CheckBins start"<<std::endl;
      for (Int_t inew = 0; inew < nbins->size(); ++inew){
	if(debug_me) std::cout<<"loop over vector provided. checking "<<nbins->at(inew)<<std::endl;
	//Loop over bins in histogram
	Int_t iold = 0;
	while(true){     
	  if(debug_me) std::cout<<"\tloop over histo provided. bin edge: "<<hist->GetXaxis()->GetBinLowEdge(iold)<<std::endl;
	  //0.000001 is because comparing doubles with "==" sucks.
	  if(nbins->at(inew) - hist->GetXaxis()->GetBinLowEdge(iold) < 0.000001){
	    if(debug_me) std::cout<<"\t\tfound match."<<std::endl;
	    break;
	  }
	  
	  iold++;
	  
	  //+2 is to cover for underflow and overflow bin boundaries
	  if( iold == hist->GetNbinsX()+2 ){
	    std::cout<<"Problem with Check Bins. No match found! Here's debug info:"<<std::endl;
	    std::cout<<"\t Input histogram bins: [";
	    for(int david = 0; david < hist->GetNbinsX()+2; david++)
	      std::cout<<hist->GetXaxis()->GetBinLowEdge(david)<<",";
	    std::cout<<"]"<<std::endl;
	    std::cout<<"\t Input new bins: [";
	    for(size_t david = 0; david < nbins->size(); david++)
	      std::cout<<nbins->at(david)<<",";
	    std::cout<<"]"<<std::endl;
	    std::cout<<"\t\t Unable to rebin because one of the input new bins does not match any of the input histogram bin low edge boundaries."<<std::endl;
	    return false;
	  }
	}
	
      }
      
      return true;
    }
    
    THStack* HistManip::AddTH1FToStack(TH1F * const hist, THStack * const stack){
      
      THStack *result = new THStack();
      
      //Make sure hist binning matches the binning of (any, so 0th) hist in stack
      //(since all hists in the stack have same binning)
      std::vector<double> *histbins = new std::vector<double>;
      for(size_t i = 0; i < hist->GetNbinsX(); i++)
	histbins->push_back(hist->GetXaxis()->GetBinLowEdge(i));
      
      TH1F* blah;
      if((TH1F*)stack->GetHists())
	blah = (TH1F*)stack->GetHists()->At(0);
      else{
	std::cout<<"error, stack provided to AddTH1FToStack is empty"<<std::endl;
	return result;
      }
      std::cout<<"check: stack histos bins are "<<blah->GetNbinsX()<<std::endl;
      
      if(!CheckBins((TH1F*)stack->GetHists()->At(0),histbins)){
	std::cout<<"problem. returning empty stack"<<std::endl;
	return result;
      }
      
      result = stack;
      result->Add(hist);
      return result;
      
    }
    
    
    
    TH1F* HistManip::RebinTH1F(TH1F * const hist, const std::vector<double> *newbins){
      
      //Check to make sure newbins are all integer multiples of oringal hist bins
      //otherwise TH1F::Rebin does funky stuff.
      if( !CheckBins(hist,newbins) ){
	std::cout<<"problem. implement exception here. rebinTH1F didn't pass CheckBins test"<<std::endl;
      }
      
      TH1F *result = hist;
      size_t nbins = newbins->size();
      Double_t xbins[nbins];
      for (Int_t i = 0; i < nbins; i++)
	xbins[i]=newbins->at(i);
      
      return (TH1F*)result->Rebin(nbins-1,"tmp",xbins);
      
    }
    
    THStack* HistManip::RebinStack(const THStack *stack, const std::vector<double> *newbins){
      
      THStack *result = new THStack();
      
      //Loop over the histograms in the stack, check each has compatible bins
      for(size_t i = 0; i < stack->GetHists()->GetSize(); i++){
	if( !CheckBins((const TH1F*)stack->GetHists()->At(i),newbins) ){
	  std::cout<<"problem with a histogram bin in stack. returning null result stack"<<std::endl;
	  std::cout<<"i = "<<i<<std::endl;
	  return result;
	}
	
	result->Add(RebinTH1F((TH1F*)stack->GetHists()->At(i),newbins));
      }
      
      return result;
    }
    
  } //end namespace util
  
}//end namespace ubsens

#endif

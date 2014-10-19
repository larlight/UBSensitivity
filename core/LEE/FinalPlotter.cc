#ifndef FINALPLOTTER_CC
#define FINALPLOTTER_CC

#include "FinalPlotter.hh"
namespace ubsens{

  bool CheckBins(const TH1F *hist, std::vector<double> *nbins){
    /*
    //Check to make sure each of the bin low boundaries listed in nbins
    //matches with a bin already in hist
    std::cout<<"start of checkbins"<<std::endl;
    for (Int_t inew = 0; inew < nbins->size(); ++inew){
      std::cout<<"looping over input std::vector: "<<nbins->at(inew)<<std::endl;
      //loop over bins in histogram
      for (Int_t iold = 0; iold < hist->GetNbinsX(); iold++){
	std::cout<<"\tlooping over histo bins: "<<hist->GetXaxis()->GetBinLowEdge(iold)<<std::endl;
	if(nbins->at(inew) == hist->GetXaxis()->GetBinLowEdge(iold)){
	  std::cout<<"found a match. skipping"<<std::endl;
	  continue;
	}
      }
      std::cout<<"uh oh. didn't find a match"<<std::endl;
      return false;

    }
    */
    return true;
  }

  THStack* AddHistToStack(const TH1 *hist, const THStack *stack){

    THStack *result = new THStack();


    return result;

  }

  /*
  THStack* RebinStack(const THStack *stack, const std::vector<double> *newbins){

    THStack *result = new THStack();
    
    
    return result;

  }
  
  TH1F* RebinTH1F(const TH1F *hist, const std::vector<double> *newbins){

    //check to make sure newbins are all integer multiples of oringal hist bins
    //otherwise TH1F::Rebin does funky stuff.

    //    if( !CheckBins(hist,newbins) ){

    //      std::cout<<"problem"<<std::endl;
      
    //    }
      

    TH1F *result = new TH1F();

    return result;

  }

  */
}// end namespace ubsens
#endif

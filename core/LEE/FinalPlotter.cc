#ifndef FINALPLOTTER_CC
#define FINALPLOTTER_CC

#include "FinalPlotter.hh"
namespace ubsens{

  THStack* AddHistToStack(TH1 *hist, THStack *stack){

    THStack *result = new THStack();


    return result;

  }


  THStack* RebinStack(THStack *stack, size_t somenumberinvolvingbins){

    THStack *result = new THStack();
    
    
    return result;

  }

  TH1F* RebinTH1F(TH1F *hist, size_t somenumberinvolvingbins){

    TH1F *result = new TH1F();

    return result;

  }


}// end namespace ubsens
#endif

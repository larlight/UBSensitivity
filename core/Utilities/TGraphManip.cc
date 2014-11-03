#ifndef TGRAPHMANIP_CC
#define TGRAPHMANIP_CC

#include "TGraphManip.hh"

namespace ubsens{
  namespace util{

    TGraph* TGraphManip::MultiplyTwoGraphs(TGraph* const g1, TGraph* const g2){

      TGraph *result = new TGraph();
      
      TGraph *morepoints;
      TGraph *fewerpoints;
      //resultant graph should have same # of points as input graph with most points
      int point_counter = 0;
      
      if(g1->GetN() > g2->GetN()){
	morepoints = g1;
	fewerpoints= g2;
      }
      else{
	morepoints = g2;
	fewerpoints= g1;
      }

      for(size_t i = 0; i < morepoints->GetN(); ++i){
      
	double myx = morepoints->GetX()[i];
      
	double myy = morepoints->GetY()[i]*fewerpoints->Eval(myx);
      
	result->SetPoint(point_counter,myx,myy);
	point_counter++;
      }
      
      return result;
      
    }

  }//end namespace util
}//end namespace ubsens
#endif

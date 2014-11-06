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


    TGraph* TGraphManip::DivideTwoGraphs(TGraph* const numerator, TGraph* const denominator){

      TGraph *result = new TGraph();
      
      TGraph *morepoints;
      TGraph *fewerpoints;
      //resultant graph should have same # of points as input graph with most points
      int point_counter = 0;
      
      bool morepoints_is_numerator;

      if(numerator->GetN() > denominator->GetN()){
	morepoints = numerator;
	fewerpoints= denominator;
	morepoints_is_numerator = true;
      }
      else{
	morepoints = denominator;
	fewerpoints= numerator;
	morepoints_is_numerator = false;
      }

      double myx, myy;
      for(size_t i = 0; i < morepoints->GetN(); ++i){
      
	myx = morepoints->GetX()[i];
	
	//Avoid divide-by-zero errors by skipping that point
	if(morepoints_is_numerator  && fewerpoints->Eval(myx) == 0)
	  continue;
	if(!morepoints_is_numerator && morepoints->GetY()[i] == 0)
	  continue;

	morepoints_is_numerator ? 
	  ( myy = morepoints->GetY()[i]/fewerpoints->Eval(myx) ) :
	  ( myy = fewerpoints->Eval(myx)/morepoints->GetY()[i] );
      
	result->SetPoint(point_counter,myx,myy);
	point_counter++;
      }
      
      return result;
      
    }

    void TGraphManip::ScaleGraph(TGraph & g1, double scaling_factor){

      for(size_t i = 0; i < g1.GetN(); ++i)
	g1.GetY()[i] *= scaling_factor;
      
    }


  }//end namespace util
}//end namespace ubsens
#endif

#ifndef STRINGPARSER_CC
#define STRINGPARSER_CC

#include "StringParser.hh"

namespace ubsens{
  namespace util{

    const double* StringParser::ParseBinsString(std::string binstring){
      
      double *xbins = new double[5];

      xbins[0]=0.;
      xbins[1]=1.;
      xbins[2]=1.5;
      xbins[3]=1.9;
      xbins[4]=4.;

      return xbins;
    }
  }// end namespace util
}// end namespace ubsens

#endif

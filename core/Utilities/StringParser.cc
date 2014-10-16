#ifndef STRINGPARSER_CC
#define STRINGPARSER_CC

#include "StringParser.hh"

namespace ubsens{
  namespace util{

    const std::vector<double>* StringParser::ParseBinsString(std::string binstring){
      //this assumes string is of format [3, 2,3, 2,1.923 ]
      
      //first cut off the leading "[" and last "]",
      //find leading "[" (should be first character, but let's be sure)
      //find ending "]"

      std::size_t start = binstring.find("[");
      std::size_t end = binstring.find("]");
	
      if( start != std::string::npos && end != std::string::npos)
	binstring = binstring.substr(start+1,end-1);
      else{
	std::ostringstream msg;
	msg
	  << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	  << "ERROR: Reading in string "<<binstring<<" has problems."
	  << " It should be formatted like \"[2, 3.5, 2,23]\", making"
	  << " sure you start and end with square brackets."
	  << std::endl;
	throw ::ubsens::fmwk::FMWKException(msg.str());
      }

      //break apart inner numbers, separated by commas.
      //cast that string as a double
      std::vector<double> *xbins = new std::vector<double>();
    
      std::string delimiter = ",";
      size_t pos = 0;
      std::string token;
    
      while ((pos = binstring.find(delimiter)) != std::string::npos) {
	token = binstring.substr(0,pos);
	binstring.erase(0,pos+delimiter.length());
	xbins->push_back(::atof(token.c_str()));
      }

      xbins->push_back(::atof(binstring.c_str()));

      return xbins;
    }
  }// end namespace util
}// end namespace ubsens

#endif

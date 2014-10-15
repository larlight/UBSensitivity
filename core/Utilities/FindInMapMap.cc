#ifndef FINDINMAPMAP_CC
#define FINDINMAPMAP_CC

#include "FindInMapMap.hh"

namespace ubsens{

  namespace util{
    
    std::string FindInMapMap::GetParamValue(std::string key1,
					    std::string key2,
					    const std::map<std::string,std::map<std::string,std::string>> &_map){


      std::string nullresult = "";
      
      //if map isn't filled with anything, return empty string
      if( !_map.size() ) {
	std::ostringstream msg;
	msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	    << "ERROR: Map you fed me is empty!"
	    <<std::endl;
	throw ::ubsens::fmwk::FMWKException(msg.str());

	return nullresult;
      }
      //loop over outer keys
      for(std::map<std::string,std::map<std::string,std::string> >::const_iterator iter(_map.begin());
	  iter!=_map.end();
	  ++iter){
	
	//if the first key isn't right, skip to the next one and don't loop over this inner map
	if(std::strcmp( (*iter).first.c_str(), key1.c_str() ) != 0) continue;
	
	//now that we have found a first-key match, loop over inner keys
	for(std::map<std::string,std::string>::const_iterator iter2((*iter).second.begin());
	    iter2!=(*iter).second.end();
	    ++iter2){
	  
	  //if the second key is matched, return the value from that key
	  if(std::strcmp( (*iter2).first.c_str(), key2.c_str() ) == 0){
	    // debug couts
	    //	    std::cout<<"Found a match! mod: "<<key1
	    //		     <<", paramname = "<<key2
	    //		     <<", value = "<<(*iter2).second.c_str()
	    //		     <<std::endl;
	    return (*iter2).second.c_str();
	  }
	}
      }
    

      std::ostringstream msg;
      msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	  << "ERROR: Map you fed me doesn't contain keys you fed me!"
	  <<std::endl;
      throw ::ubsens::fmwk::FMWKException(msg.str());
      
      return nullresult;
    }

  }//end namespace util
}//end namespace ubsens
#endif

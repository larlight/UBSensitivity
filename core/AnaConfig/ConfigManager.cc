#ifndef CONFIGMANAGER_CC
#define CONFIGMANAGER_CC

#include "ConfigManager.hh"

namespace ubsens{

  namespace config{

    bool ConfigManager::LoadConfig(std::string filename){
     
      Reset();
      
      _cr.Reset();

      try{
	_cr.SetConfigFile(filename);
	_cr.Read();      
      }
      catch (::ubsens::fmwk::FMWKException &e) {
	fMsg.send(::ubsens::fmwk::msg::kERROR,e.what());
      }
  
      _map = _cr.GetMap();
      
      return true;

    }

    void ConfigManager::SaveConfig(){

      TObjString myconfigstring;

      //loop over config map, save it to a long string, then pass
      //the string to plotWriter to save it to the output file for reference
      //note: use the "option" flag as the name of the string
      std::string tmpstring = "";

      //this is mostly copied from ConfigReader::Dump
      if(!_map.size()){

	//throw exception
      }
      else{

	tmpstring += "Configuration for this run shown below.\n";
	tmpstring += "Date and time: ";
	
	time_t t = time(0);
	struct tm *now = localtime(&t);
	tmpstring += std::to_string(now->tm_year + 1900) +"-"
	  +std::to_string(now->tm_mon + 1)+"-"
	  +std::to_string(now->tm_mday)+" at "
	  +std::to_string(now->tm_hour)+":"
	  +std::to_string(now->tm_min)+":"
	  +std::to_string(now->tm_sec)+"\n";
	
	tmpstring += "Module name\tParameterName\tParameterValue\n";
	tmpstring += "----------------------------------------------------------------\n";
	for(std::map<std::string,std::map<std::string,std::string> >::const_iterator iter(_map.begin());
	    iter!=_map.end();
	    ++iter)
	  for(std::map<std::string,std::string>::const_iterator iter2((*iter).second.begin());
	      iter2!=(*iter).second.end();
	      ++iter2){
	    tmpstring += std::string((*iter).first.c_str()) + "\t";
	    tmpstring += std::string((*iter2).first.c_str()) + "\t";
	    tmpstring += std::string((*iter2).second.c_str()) + "\n";
	  }
	
	tmpstring += "----------------------------------------------------------------\n";
      }
      
      myconfigstring.SetString(tmpstring.c_str());
      ::ubsens::util::PlotWriter::GetME()->
	  Write(&myconfigstring,"ConfigLog","config_log");
    }


    void ConfigManager::Reset(){

      _map.clear();

    }
  }

}
#endif

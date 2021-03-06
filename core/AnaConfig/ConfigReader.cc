#ifndef CONFIGREADER_CC
#define CONFIGREADER_CC

#include "ConfigReader.hh"

namespace ubsens{

  namespace config{

    bool ConfigReader::SetConfigFile(std::string filename){

      //Check if file exists
      std::ifstream blah(filename.c_str());
      if (!blah)
	{
	  std::ostringstream msg;
	  msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	      << "ERROR: Config file does not exist."
	      << std::endl;
	  throw ::ubsens::fmwk::FMWKException(msg.str());
	  return false;
	}
      
      _in_filename = filename;

      return true;
    }

    bool ConfigReader::Read(){

      if( _in_filename == "" ){
	std::string msg = "";
	msg += "Config reader hasn't set filename yet.";
	fMsg.send(::ubsens::fmwk::msg::kERROR,__FUNCTION__,msg);
	return false;
      }

      // Max # of characters allowed in one line
      const int MAX_CHARS_PER_LINE = 512;
      // Max # of columns in each line (separated by DELIMITER)
      const int MAX_TOKENS_PER_LINE = 50;
      // What separates each column
      const char* const DELIMITER = " ";

      std::ifstream fin;
      
      //Open the input configuration file
      fin.open(_in_filename.c_str());
      if (!fin.good()){
	std::string msg = "";
	msg += "Can't find config file.";
	fMsg.send(::ubsens::fmwk::msg::kERROR,__FUNCTION__,msg);
	return false;
      }
      
      std::string block_name = "";

      std::map<std::string,std::string> tmpmap;

      //Read each line of the file
      while (!fin.eof())
	{
	  // Read an entire line into memory
	  char buf[MAX_CHARS_PER_LINE];
	  fin.getline(buf, MAX_CHARS_PER_LINE);
	  
	  // Parse the line into blank-delimted tokens
	  int n = 0;
	  
	  // Array to store memory addresses of the tokens in buf
	  const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
	  
	  // Parse the line
	  token[0] = strtok(buf, DELIMITER); // first token
	
	  // If the line is blank, skip it
	  if(!token[0]) continue;
  
	  //If the line starts with "#" it's a comment. skip it
	  if(std::strncmp(&token[0][0],"#",1) == 0)
	    continue;
	  
	  //If the last character in the first word is a COLON,
	  //then that signifies the start of a new block of configs
	  //for each block, make a std::map of <string,string>,
	  //then insert it into the main map when you get to the next COLON'd word
	  if ( std::strncmp(&token[0][strlen(token[0])-1],":",1) == 0 ) {
	    
	    if(tmpmap.size() && !block_name.empty()){
	      if(IsInModuleList(block_name))
		_map.insert (std::pair<std::string,std::map<std::string,std::string > >(block_name,tmpmap));
	      else{
		//Exception: block header wasn't in module list
		//User neeeds to fix config file, or update ConfigConstants lists
		std::ostringstream msg;
		msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
		    << "ERROR: Module type "<< block_name <<" from config file does not exist."
		    << std::endl;
		throw ::ubsens::fmwk::FMWKException(msg.str());
	      }
	    }
	    
	    tmpmap.clear();
	    block_name = std::string(token[0]).substr(0,std::string(token[0]).size()-1);
	    continue;
	  }
	  
	  //Continue reading next words in the line
	  for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
	    {
	      token[n] = strtok(0, DELIMITER); // subsequent tokens
	      if (!token[n]) break; // no more tokens
	    }
	  
	  
	  
	  /*
	  // debug: print the tokens	  
	  std::cout<<"block_name is "<<block_name<<std::endl;
	  std::cout<<"n = "<<n<<std::endl;
	  //if n==1, this line is a "new block" line (ends in colon)
	  if( n==0 ) //blank line
	  continue;
	  else if ( n == 1 )//one column line
	  std::cout << token[0] << std::endl;
	  else{
	  for (int i = 0; i < n; i++) // n = #of tokens
	  std::cout << "Token[" << i << "] = " << token[i] << std::endl;
	  std::cout << std::endl;
	  }
	  */
	  
	  //Lines with blank params (IE should use default)
	  //Insert empty string as value
	  if( n == 1)
	    tmpmap.insert (std::pair<std::string,std::string>(token[0],std::string("")));
	  //Lines with 2+ words: first word is taken as parameter name,
	  //all subsequent words added together with spaces to make a single string
	  //(this works fine with most 2-word columns, but also allows spaces in parameter
	  //values for things like histogram titles)
	  else if( n == 2 )
	    tmpmap.insert (std::pair<std::string,std::string>(token[0],token[1]));
	  else{
	    std::string paramvalue = "";
	    for(int i = 1; i < n; i++)
	      if (i==n-1) paramvalue += std::string(token[i]);
	      else      paramvalue += std::string(token[i]) + " ";
	    tmpmap.insert (std::pair<std::string,std::string>(token[0],paramvalue));
	  }

	}//Done reading in lines from file
      
      //use block_name to find the key in the map
      //insert the last block's tmpmap into _map
      _map.insert (std::pair<std::string,std::map<std::string,std::string > >(block_name,tmpmap));
      
      //close input stream
      fin.close();

      return true;      

    }

    void ConfigReader::Reset(){

      _in_filename = "";
      _map.clear();

    }
    
    void ConfigReader::Dump(){
      
      if(_map.size()){
	std::string msg = "";
	msg += "Contents of _map shown below.\n";
	msg += "ModuleName ... ParamName ... ParamValue\n";
	
	for(std::map<std::string,std::map<std::string,std::string> >::const_iterator iter(_map.begin());
	    iter!=_map.end();
	    ++iter){
	  for(std::map<std::string,std::string>::const_iterator iter2((*iter).second.begin());
	      iter2!=(*iter).second.end();
	      ++iter2){
	    msg += "\"" + std::string((*iter).first) + "\" ... ";
	    msg += "\"" + std::string((*iter2).first)+ "\" ... ";
	    msg += "\"" + std::string((*iter2).second) + "\"\n";
	  }

	}
	fMsg.send(::ubsens::fmwk::msg::kNORMAL,__FUNCTION__,msg);
      }
      
    }
    
    bool ConfigReader::IsInModuleList(std::string mystring){

      
      const std::string *findResult = 0;
      findResult = std::find ( ::ubsens::config::MODULE_NAME,
			       ::ubsens::config::MODULE_NAME+::ubsens::config::MAX_MODULE_TYPE,
			       mystring );
      if(findResult->empty())
	return false;

      return true;
    }


  }// end namespace config

}// end namespace ubsens
#endif

#ifndef PLOTREADER_CC
#define PLOTREADER_CC

#include "PlotReader.hh"

namespace ubsens{
  namespace util{
    
    PlotReader* PlotReader::_me = 0;
    
    TGraph* PlotReader::GetGraph(){
      
      TGraph* result = NULL;
      
      if(_filename.empty() || _plotname.empty()){
	std::ostringstream msg;
	msg << "<<" << _classname << "::" << __FUNCTION__ << ">> "
	    << "ERROR: PlotReader needs you to set filename and plot name."
	    << std::endl;
	throw UtilException(msg.str());

	return result;
      }
      
      TFile* f = new TFile(_filename.c_str(),"READ");

      //Some basic checks (file exists, object in file exists, correct type)
      if(!f){
	std::ostringstream msg;
	msg
	  << "<<" << _classname << "::" << __FUNCTION__ << ">> "
	  << "ERROR: File "<< _filename << " does not exist!"
	  << std::endl;
	throw UtilException(msg.str());
	
	return result;
      }
      if(!f->GetListOfKeys()->Contains(_plotname.c_str())){
	std::ostringstream msg;
	msg
	  << "<<" << _classname << "::" << __FUNCTION__ << ">> "
	  << "ERROR: File "<< _filename <<" does not contain object "
	  << _plotname << "."
	  << std::endl;
	throw UtilException(msg.str());

	return result;
      }
      if(!strncmp(
	f->GetListOfKeys()->FindObject(_plotname.c_str())->ClassName(), 
	"TGraph",6))
	{
	  std::ostringstream msg;
	  msg
	    << "<<" << _classname << "::" << __FUNCTION__ << ">> "
	    << "ERROR: File "<< _filename <<" contains object "
	    << _plotname << ", but that object is not a TGraph! "
	    << "It is a "
	    << f->GetListOfKeys()->FindObject(_plotname.c_str())->ClassName()
	    << std::endl;
	  throw UtilException(msg.str());
	  
	  return result;
	}
      
      result = (TGraph*)f->Get(_plotname.c_str());
      
      return result;
      
    }
    
    TH2F* PlotReader::GetTH2F(){

      TH2F* result = NULL;

      if(_filename.empty() || _plotname.empty()){
	std::ostringstream msg;
	msg << "<<" << _classname << "::" << __FUNCTION__ << ">> "
	    << "ERROR: PlotReader needs you to set filename and plot name."
	    << std::endl;
	throw UtilException(msg.str());

	return result;
      }
      
      TFile* f = new TFile(_filename.c_str(),"READ");

      //Some basic checks (file exists, object in file exists, correct type)
      if(!f){
	std::ostringstream msg;
	msg
	  << "<<" << _classname << "::" << __FUNCTION__ << ">> "
	  << "ERROR: File "<< _filename << " does not exist!"
	  << std::endl;
	throw UtilException(msg.str());
	
	return result;
      }
      if(!f->GetListOfKeys()->Contains(_plotname.c_str())){
	std::ostringstream msg;
	msg
	  << "<<" << _classname << "::" << __FUNCTION__ << ">> "
	  << "ERROR: File "<< _filename <<" does not contain object "
	  << _plotname << "."
	  << std::endl;
	throw UtilException(msg.str());

	return result;
      }
      if(!strncmp(
	f->GetListOfKeys()->FindObject(_plotname.c_str())->ClassName(), 
	"TGraph",6))
	{
	  std::ostringstream msg;
	  msg
	    << "<<" << _classname << "::" << __FUNCTION__ << ">> "
	    << "ERROR: File "<< _filename <<" contains object "
	    << _plotname << ", but that object is not a TH2F! "
	    << "It is a "
	    << f->GetListOfKeys()->FindObject(_plotname.c_str())->ClassName()
	    << std::endl;
	  throw UtilException(msg.str());
	  
	  return result;
	}
      
      result = (TH2F*)f->Get(_plotname.c_str());
      
      return result;

    }
  }//end namespace util
}//end namespace ubsens
#endif

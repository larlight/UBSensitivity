#ifndef PLOTREADER_CC
#define PLOTREADER_CC

#include "PlotReader.hh"

namespace ubsens{
  namespace util{

    
    PlotReader* PlotReader::_me = 0;
    


    TObject* PlotReader::GetObject(){
      
      TObject* result = NULL;
      
      if(_filename.empty() || _objectname.empty()){
	std::ostringstream msg;
	msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	    << "ERROR: PlotReader needs you to set filename and object name."
	    << std::endl;
	throw ::ubsens::fmwk::FMWKException(msg.str());

	return result;
      }
      
      TFile* f = new TFile(_filename.c_str(),"READ");

      //Some basic checks (file exists, object in file exists, correct type)
      if(!f){
	std::ostringstream msg;
	msg
	  << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	  << "ERROR: File "<< _filename << " does not exist!"
	  << std::endl;
	throw ::ubsens::fmwk::FMWKException(msg.str());
	
	return result;
      }
      if(!f->GetListOfKeys()->Contains(_objectname.c_str())){
	std::ostringstream msg;
	msg
	  << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	  << "ERROR: File "<< _filename <<" does not contain object "
	  << _objectname << "."
	  << std::endl;
	throw ::ubsens::fmwk::FMWKException(msg.str());

	return result;
      }

      // Actually get the object
      result = (TObject*)f->Get(_objectname.c_str());
      
      return result;
      
    }
    
  }//end namespace util
}//end namespace ubsens
#endif

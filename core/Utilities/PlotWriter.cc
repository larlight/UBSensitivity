#ifndef PLOTWRITER_CC
#define PLOTWRITER_CC

#include "PlotWriter.hh"

namespace ubsens{

  namespace util{
    
    PlotWriter* PlotWriter::_me = 0;

    void PlotWriter::Write(TObject *object_to_write,std::string subdir,std::string opt){

      if( _filename == "" ){
	std::ostringstream msg;
	msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	    << "ERROR: PlotWriter needs you to set filename."
	    << std::endl;
	throw ::ubsens::fmwk::FMWKException(msg.str());
      }

      TFile *f = new TFile(_filename.c_str(),"UPDATE");

      //If subdir doesn't exist, make it
      if( !f->GetDirectory(subdir.c_str()) )
	f->mkdir(subdir.c_str());

      f->cd(subdir.c_str());
      object_to_write->Write(opt.c_str());
      f->Close();
      delete f;

    }

  }//end namespace util

}//end namespace ubsens
#endif

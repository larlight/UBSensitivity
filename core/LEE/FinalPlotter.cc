#ifndef FINALPLOTTER_CC
#define FINALPLOTTER_CC

#include "FinalPlotter.hh"
namespace ubsens{
  
  bool FinalPlotter::Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap){
    
    try{
      _background_stackfile = util::FindInMapMap().GetParamValue(class_name(),std::string("BackgroundStackFile"),_configMap);
      _background_stackname = util::FindInMapMap().GetParamValue(class_name(),std::string("BackgroundStackName"),_configMap);
      _background_legendname = util::FindInMapMap().GetParamValue(class_name(),std::string("BackgroundStackLegendName"),_configMap);
      _final_hist_bins_string =  util::FindInMapMap().GetParamValue(class_name(),std::string("FinalStackBins"),_configMap);
    }
    catch (fmwk::FMWKException &e) {
      std::cout<<e.what()<<std::endl;
    }
    
    //If the config file has blank lines, use defaults
    if(_background_stackfile.empty()){
      std::cout<<class_name()<<" is using default value for _background_stackfile."<<std::endl;
      _background_stackfile = "/Users/davidkaleko/Data/LEE/SingleElectronBackgrounds_101614.root";
    }

    if(_background_stackname.empty()){
      std::cout<<class_name()<<" is using default value for _background_stackname."<<std::endl;
      _background_stackname = "NueBackgroundsLepE";
    }

    if(_background_legendname.empty()){
      std::cout<<class_name()<<" is using default value for _background_legendname."<<std::endl;
      _background_legendname = "ElectronBackgroundLegend";
    }
    
    if(_final_hist_bins_string.empty()){
      std::cout<<class_name()<<" is using default value for _final_hist_bins_string."<<std::endl;
      _final_hist_bins_string = "[0.2,0.48,0.76,1.04,1.32,1.6,1.88,2.16,2.44,2.72,3.0]";
    }
    
    return true;
  }

  void FinalPlotter::WritePlots(){

    if(_final_stack)
      util::PlotWriter::GetME()->Write(_final_stack,class_name());
    else
      std::cout<<"Fill the stack (MakeStackedHisto()) before writing!"<<std::endl;

    if(_final_legend)
      util::PlotWriter::GetME()->Write(_final_legend,class_name());
    else
      std::cout<<"Fill the legend (MakeStackedHisto()) before writing!"<<std::endl;
  }


  void FinalPlotter::MakeStackedHisto(){
        
    if(!_final_LEE_histo){
      std::cout<<"Uh oh. Load final LEE histo into Final Plotter first!"<<std::endl;
      return;
    }

    util::PlotReader::GetME()->Reset();
    util::PlotReader::GetME()->SetFileName(_background_stackfile);
    util::PlotReader::GetME()->SetObjectName(_background_stackname);
    _final_stack=(THStack*)util::PlotReader::GetME()->GetObject();

    const std::vector<double> *xbins_vec = util::StringParser().ParseBinsString(_final_hist_bins_string);

    _final_LEE_histo=util::HistManip::RebinTH1F(_final_LEE_histo,xbins_vec);
    _final_stack=util::HistManip::RebinStack(_final_stack,xbins_vec);
    _final_stack=util::HistManip::AddTH1FToStack(_final_LEE_histo,_final_stack);
    _final_stack->SetName("LEE_final_stack");

    //Add the LEE signal to the legend, too
    util::PlotReader::GetME()->Reset();
    util::PlotReader::GetME()->SetFileName(_background_stackfile);
    util::PlotReader::GetME()->SetObjectName(_background_legendname);
    _final_legend = (TLegend*)util::PlotReader::GetME()->GetObject();
    _final_legend->AddEntry(_final_LEE_histo,_final_LEE_histo->GetTitle(),"f");

  }
  
}// end namespace ubsens
#endif

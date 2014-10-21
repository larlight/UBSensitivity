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
      _final_stack_title = util::FindInMapMap().GetParamValue(class_name(),std::string("FinalStackTitle"),_configMap);
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kEXCEPTION, __FUNCTION__, e.what());
    }
    
    //If the config file has blank lines, use defaults
    if(_background_stackfile.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _background_stackfile.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _background_stackfile = "/Users/davidkaleko/Data/LEE/SingleElectronBackgrounds_101614.root";
    }

    if(_background_stackname.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _background_stackname.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _background_stackname = "NueBackgroundsLepE";
    }

    if(_background_legendname.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _background_legendname.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _background_legendname = "ElectronBackgroundLegend";
    }
    
    if(_final_hist_bins_string.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _final_hist_bins_string.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _final_hist_bins_string = "[0.2,0.48,0.76,1.04,1.32,1.6,1.88,2.16,2.44,2.72,3.0]";
    }
    
    if(_final_stack_title.empty()){
      std::string msg = "";
      msg += class_name() + " is using default value for _final_stack_title.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
      _final_stack_title = "DEFAULT STACK TITLE;DEFAULT AXIS;DEFAULT BLAH";
    }
    
    return true;
  }

  void FinalPlotter::WritePlots(){

    if(_final_stack)
      util::PlotWriter::GetME()->Write(_final_stack,class_name());
    else{
      std::string msg = "";
      msg += "Final stack is empty, so I'm not going to save it. ";
      msg += "Fill it with MakeStackedHisto function before attempting to write to file.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
    }

    if(_final_legend)
      util::PlotWriter::GetME()->Write(_final_legend,class_name());
    else{
      std::string msg = "";
      msg += "Final legend is empty, so I'm not going to save it. ";
      msg += "Fill it with MakeStackedHisto function before attempting to write to file.";
      fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__, msg);
    }
   
  }


  void FinalPlotter::MakeStackedHisto(){
        
    if(!_final_LEE_histo){
      std::string msg = "";
      msg += "Uh oh. Load final LEE histo into FinalPlotter before attempting ";
      msg += "to make the final stacked histogram.";
      fMsg.send(::ubsens::fmwk::msg::kERROR, __FUNCTION__, msg);
      return;
    }

    //Make util::HistManip instance so I can call non-static functions within
    util::HistManip hm;

    util::PlotReader::GetME()->Reset();
    util::PlotReader::GetME()->SetFileName(_background_stackfile);
    util::PlotReader::GetME()->SetObjectName(_background_stackname);
    _final_stack=(THStack*)util::PlotReader::GetME()->GetObject();

    const std::vector<double> *xbins_vec = util::StringParser().ParseBinsString(_final_hist_bins_string);

    _final_LEE_histo=hm.RebinTH1F(_final_LEE_histo,xbins_vec);
    _final_LEE_histo->SetFillStyle(3002);
    _final_LEE_histo->SetFillColor(kBlack);
    _final_LEE_histo->SetLineColor(kBlack);
    _final_stack=hm.RebinStack(_final_stack,xbins_vec);
    _final_stack=hm.AddTH1FToStack(_final_LEE_histo,_final_stack);
    _final_stack->SetName("LEE_final_stack");
    _final_stack->SetTitle(_final_stack_title.c_str());
   
    //Add the LEE signal to the legend, too
    util::PlotReader::GetME()->Reset();
    util::PlotReader::GetME()->SetFileName(_background_stackfile);
    util::PlotReader::GetME()->SetObjectName(_background_legendname);
    _final_legend = (TLegend*)util::PlotReader::GetME()->GetObject();
    _final_legend->AddEntry(_final_LEE_histo,_final_LEE_histo->GetTitle(),"lf");
    _final_legend->SetName("LEE_final_legend");
    //Add "INTERNAL" or "PRELIMINARY" tag to final plot?

  }
  
}// end namespace ubsens
#endif

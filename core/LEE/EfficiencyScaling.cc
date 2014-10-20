#ifndef EFFICIENCYSCALING_CC
#define EFFICIENCYSCALING_CC

#include "EfficiencyScaling.hh"
namespace ubsens{

  void EfficiencyScaling::MakeGraph(){

    //for now this is hard-coded as an 80% efficiency graph
    _eff_graph = new TGraph();
    _eff_graph->SetName("eff_graph");
    _eff_graph->SetTitle("Efficiency;Lepton Energy [GeV];Effiency");

    _eff_graph->SetPoint(0,0,0.8);
    _eff_graph->SetPoint(1,3,0.8);

  }

  void EfficiencyScaling::WritePlots(){

    if ( !_eff_graph){
      std::ostringstream msg;
      msg << "<<" << class_name() << "::" << __FUNCTION__ << ">> "
	  << "ERROR: Haven't computed _eff_graph yet!"
	  << std::endl;
      throw fmwk::FMWKException(msg.str());

      return;
    }

    try{
      util::PlotWriter::GetME()->Write(_eff_graph,class_name().c_str());
    }
    catch (fmwk::FMWKException &e) {
      fMsg.send(::ubsens::fmwk::msg::kERROR,e.what());
    }
  }




}// end namespace ubsens
#endif

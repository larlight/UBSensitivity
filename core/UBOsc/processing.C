
{
  gSystem->Load("liblar1Osc.so");
  TString directory = "~/Data/LAr1Ntuples/";
  lar1::NtupleReprocessing ntuple_470m_nu(directory + "combined_ntuple_470m_nu.root");           
  lar1::NtupleReprocessing ntuple_470m_nu_fosc(directory + "combined_ntuple_470m_nu_fosc.root");

  // For each ntuple, do the nue, numu, fosc processing loops.
  // Grouping them by iDet:

  ntuple_470m_nu.Loop("nue",1);
  // ntuple_470m_nu.Loop("numu",1);
  ntuple_470m_nu_fosc.Loop("fosc",1);
  // ntuple_470m_nubar.Loop("nue",1);
  // ntuple_470m_nubar.Loop("numu",1);
  // ntuple_470m_nubar_fosc.Loop("fosc",1);

}

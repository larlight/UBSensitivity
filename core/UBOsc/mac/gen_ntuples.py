from ROOT import *
gSystem.Load("libUBOsc.so")

directory = "~/Data/LAr1Ntuples/"

nu470 = lar1.NtupleReprocessing(directory+"combined_ntuple_470m_nu.root")
nu470fosc = lar1.NtupleReprocessing(directory+"combined_ntuple_470m_nu_fosc.root")

nu470.Loop("nue",1);

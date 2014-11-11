from ROOT import *
import sys
gSystem.Load("libLEE.so")
nlc = ubsens.NuLeptECorrelation()

nlc.SetFilename("/Users/davidkaleko/Data/LEE/combined_ntuple_470m_nu_fosc_CC_nu_lept_energycorrelation.root")
nlc.SetTH2Fname("fosc_isCC_enugen_vs_Elep")

nlc.LoadInputTH2F()

h_onedraw = TH1F("h_onedraw","Nu Energy from 1GeV Lepton Energy: 1 Draw",100,0,6)

h_tendraw = TH1F("h_tendraw","Nu Energy from 1GeV Lepton Energy: 10 Draws",100,0,6)

nlc.SetNDrawsToAvg(1)
for x in xrange(1000):
    h_onedraw.Fill(nlc.NuEFromLeptE(1))

nlc.SetNDrawsToAvg(10)
for x in xrange(1000):
    h_tendraw.Fill(nlc.NuEFromLeptE(1))


h_onedraw.SetLineColor(kRed)
h_tendraw.SetLineColor(kBlue)

l = TLegend(0.5,0.5,0.6,0.6)
l.AddEntry(h_onedraw,"One draw","L")
l.AddEntry(h_tendraw,"Ten draws","L")

h_tendraw.Draw()
h_onedraw.Draw("sames")
l.Draw()

sys.stdin.readline()

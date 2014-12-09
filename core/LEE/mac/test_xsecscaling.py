from ROOT import *
import sys
gSystem.Load("libLEE.so")


x = ubsens.XSecScaling()
#x.SetMyInputFile("/Users/davidkaleko/Desktop/mindy/genie_ar40_nue_totcc_fullrange_lowEfinesample.root")
x.SetMyInputFile("/Users/davidkaleko/Desktop/mindy/genie_CH2_nue_totcc_fullrange_lowEfinesample.root")
#x.SetMBInputFile("/Users/davidkaleko/Desktop/mindy/genie_CH2_nue_totcc_fullrange_lowEfinesample.root")
x.SetMBInputFile("/Users/davidkaleko/Data/LEE/tot_cc_genie_nuance_graphs.root")

#x.SetMyInputGraphName("genie_nue_cctot_Ar_lowEfinesampling")
x.SetMyInputGraphName("genie_nue_cctot_CH2_lowEfinesampling")
#x.SetMBInputGraphName("genie_nue_cctot_CH2_lowEfinesampling")
x.SetMBInputGraphName("nuance_total_cc_graph")

x.SetMyNTargetsPerGram(ubsens.geo.MINIBOONE_TARGETS_PER_GRAM)
x.SetMBNTargetsPerGram(ubsens.geo.MINIBOONE_TARGETS_PER_GRAM)
x.LoadInputGraphs()
x.ComputeXSecRatio()

g = x.GetXSecRatio()

c = TCanvas()
g.Draw("ALP*")

sys.stdin.readline()

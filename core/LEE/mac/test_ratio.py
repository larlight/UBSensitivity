import sys
from ROOT import *
gSystem.Load("libLEE.so")

xs = ubsens.XSecScaling()

#Ratio of nuance on Ar to nuance on CH2
xs.SetMyInputFile("/Users/davidkaleko/Data/LEE/tot_cc_nuance_nuance_numu_graphs.root")
xs.SetMBInputFile("/Users/davidkaleko/Data/LEE/tot_cc_nuance_nuance_numu_graphs.root")
xs.SetMyInputGraphName("nuance_total_cc_Ar_graph")
xs.SetMBInputGraphName("nuance_total_cc_CH2_graph")
xs.LoadInputGraphs()
xs.ComputeXSecRatio()
myg_nuance = xs.GetMyGraph()
mbg_nuance = xs.GetMBGraph()
ratio_nuance_nuance = xs.GetXSecRatio()

print "NUANCE stuff done. myg_nuance, mbg_nuance, ratio_nuance_nuance"

#Ratio of genie on Ar to genie on CH2
xs.Reset()
xs.SetMyInputFile("/Users/davidkaleko/Data/LEE/genie_default_graphs.root")
xs.SetMBInputFile("/Users/davidkaleko/Data/LEE/genie_default_graphs.root")
xs.SetMyInputGraphName("genie_ar40_tot_cc")
xs.SetMBInputGraphName("genie_C12_Plus_TwoH1_tot_cc")
xs.LoadInputGraphs()
xs.ComputeXSecRatio()
myg_genie = xs.GetMyGraph()
mbg_genie = xs.GetMBGraph()
ratio_genie_genie = xs.GetXSecRatio()

print "GENIE stuff done. myg_genie, mbg_genie, ratio_genie_genie"

#Ratio of genie on CH2 to nuance on CH2
xs.Reset()
xs.SetMyInputFile("/Users/davidkaleko/Data/LEE/genie_default_graphs.root")
xs.SetMBInputFile("/Users/davidkaleko/Data/LEE/tot_cc_nuance_nuance_numu_graphs.root")
xs.SetMyInputGraphName("genie_C12_Plus_TwoH1_tot_cc")
xs.SetMBInputGraphName("nuance_total_cc_CH2_graph")
#Set numerator to be CH2 for this one (Default is Ar)
xs.SetMyNTargetsPerGram(ubsens.geo.MINIBOONE_TARGETS_PER_GRAM)
xs.LoadInputGraphs()
xs.ComputeXSecRatio()
myg_both = xs.GetMyGraph()
mbg_both = xs.GetMBGraph()
ratio_genie_nuance_ch2 = xs.GetXSecRatio()

print "COMBO stuff done. myg_both, mbg_both, ratio_genie_nuance_ch2"

#Ratio of genie on Ar to nuance on Ar
xs.Reset()
xs.SetMyInputFile("/Users/davidkaleko/Data/LEE/genie_default_graphs.root")
xs.SetMBInputFile("/Users/davidkaleko/Data/LEE/tot_cc_nuance_nuance_numu_graphs.root")
xs.SetMyInputGraphName("genie_ar40_tot_cc")
xs.SetMBInputGraphName("nuance_total_cc_Ar_graph")
#Set numerator to be CH2 for this one (Default is Ar)
xs.SetMyNTargetsPerGram(ubsens.geo.UB_TARGETS_PER_GRAM)
xs.SetMBNTargetsPerGram(ubsens.geo.UB_TARGETS_PER_GRAM)
xs.LoadInputGraphs()
xs.ComputeXSecRatio()
myg_both2 = xs.GetMyGraph()
mbg_both2 = xs.GetMBGraph()
ratio_genie_nuance_ar = xs.GetXSecRatio()
print "Additional stuff done. ratio_genie_nuance_ar"

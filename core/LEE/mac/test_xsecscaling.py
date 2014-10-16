from ROOT import *
import sys
gSystem.Load("libLEE.so")


x = XSecScaling()
x.LoadInputGraphs()
x.ComputeXSecRatio()

g = x.GetXSecRatio()

c = TCanvas()
g.Draw("ALP*")

sys.stdin.readline()

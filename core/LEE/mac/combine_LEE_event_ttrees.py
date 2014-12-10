from ROOT import *
import numpy as n

print "Writing a tree"



fout = TFile("LEE_event_ttree_UBFV=36.13_LAr1FV=51.45.root","RECREATE")
t = TTree("LEE_event_tree","LEE Event Tree")


fin_ub = TFile("/Users/davidkaleko/UBSensitivity/core/LEE/mac/sbndoc_30cm50cm25cmfidvol_elep_smear.root","READ")
fin_l1 = TFile("/Users/davidkaleko/UBSensitivity/core/LEE/mac/sbndoc_30cm50cm25cmfidvol_elep_LAr1NDFLUX_LAr1NDFVWeight.root","READ")



t_ub = fin_ub.Get("LEEMain/LEE_event_tree")
t_l1 = fin_l1.Get("LEEMain/LEE_event_tree")


e_lep = n.zeros(1, dtype=float)
e_ccqe= n.zeros(1, dtype=float)
w_ub  = n.zeros(1, dtype=float)
w_l1  = n.zeros(1, dtype=float)

t.Branch('E_lep', e_lep,  'E_lep/D')
t.Branch('E_ccqe',e_ccqe,'E_ccqe/D')
t.Branch('wt_ub', w_ub,  'wt_ub/D')
t.Branch('wt,lar1',w_l1, 'wt_lar1/D')

entries_ub = t_ub.GetEntriesFast()
entries_l1 = t_l1.GetEntriesFast()

if entries_ub != entries_l1:
    print "wtf"
    quit()

for x in xrange(entries_ub):
    y = t_ub.GetEntry(x)
    e_lep[0] = t_ub.E_lept
    e_ccqe[0] = t_ub.E_ccqe
    w_ub[0] = t_ub.weight_UBFidVol
    y = t_l1.GetEntry(x)
    w_l1[0] = t_l1.weight_UBFidVol

    t.Fill()

README = TObjString("w_l1 is equal to w_ub with (event-by-event) flux correction ([LAr1 flux / MB flux] used instead of [UB flux / MB flux]) and (constant) fiducial volume correction of (51.45/36.13) [which are the fiducial volumes expected for LAr1 divided by fiducial volume used to select these events in UB]")
fout.cd()
t.Write()
README.Write("README")
fout.Close()

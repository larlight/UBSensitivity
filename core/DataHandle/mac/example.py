import ROOT,sys
from ROOT import *

# Demonstrate how to write data
mgr = ubsens.data.DataManager()
mgr.SetIOMode(ubsens.data.DataManager.WRITE)
mgr.SetOutputFilename("aho.root")
mgr.Open()

mgr.GetWriteableData().AppendTruthShower(ubsens.data.TruthShower())
mgr.GetWriteableData().AppendRecoShower(ubsens.data.RecoShower())
mgr.SaveEntry()
mgr.SaveEntry()

mgr.Close()

# Demonstrate how to read data
mgr.SetIOMode(ubsens.data.DataManager.READ)
mgr.AddInputFilename("aho.root")
mgr.Open()

mgr.NextEntry()
print 'First event...'
print 'Truth shower count:',mgr.GetData().TruthShowerCollection().size()
print 'Reco  shower count:',mgr.GetData().RecoShowerCollection().size()

mgr.NextEntry()
print 'Second event...'
print 'Truth shower count:',mgr.GetData().TruthShowerCollection().size()
print 'Reco  shower count:',mgr.GetData().RecoShowerCollection().size()
mgr.Close()

# Demonstrate how to read & write
mgr.SetIOMode(ubsens.data.DataManager.BOTH)
mgr.AddInputFilename("aho.root")
mgr.SetOutputFilename("boke.root")
mgr.Open()
mgr.NextEntry()
mgr.SaveEntry()
mgr.NextEntry()
mgr.SaveEntry()
mgr.Close()


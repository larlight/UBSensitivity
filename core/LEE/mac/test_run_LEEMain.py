import sys
from ROOT import *

gSystem.Load("libLEE.so")

lm = ubsens.LEEMain()

lm.Initialize()

lm.Run()

lm.Finalize()



sys.exit(0)


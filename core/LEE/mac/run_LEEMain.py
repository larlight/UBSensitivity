import sys
from ROOT import *

if( len(sys.argv) != 2 ):
    print "USAGE ERROR! USAGE: python run_LEEMain.py configuration_file.config"
    quit()

gSystem.Load("libLEE.so")

lm = ubsens.LEEMain()

lm.SetConfigFile(sys.argv[1])
lm.Initialize()

lm.Run()

lm.Finalize()



sys.exit(0)


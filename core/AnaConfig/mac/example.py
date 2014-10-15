import sys
from ROOT import *

try:

    print "PyROOT recognized your class %s" % str(AnaConfig)

except NameError:

    print "Failed importing AnaConfig..."

sys.exit(0)


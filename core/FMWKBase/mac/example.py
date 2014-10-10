import sys
from ROOT import *

try:

    print "PyROOT recognized your class %s" % str(FMWKBase)

except NameError:

    print "Failed importing FMWKBase..."

sys.exit(0)


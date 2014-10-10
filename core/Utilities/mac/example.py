import sys
from ROOT import *

try:

    print "PyROOT recognized your class %s" % str(Utilities)

except NameError:

    print "Failed importing Utilities..."

sys.exit(0)


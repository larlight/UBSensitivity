import sys
from ROOT import *

try:

    print "PyROOT recognized your class %s" % str(DataHandle)

except NameError:

    print "Failed importing DataHandle..."

sys.exit(0)


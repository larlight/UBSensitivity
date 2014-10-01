import sys
from ROOT import *

try:

    print "PyROOT recognized your class %s" % str(UBOsc)

except NameError:

    print "Failed importing UBOsc..."

sys.exit(0)


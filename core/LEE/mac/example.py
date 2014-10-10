import sys
from ROOT import *

try:

    print "PyROOT recognized your class %s" % str(LEE)

except NameError:

    print "Failed importing LEE..."

sys.exit(0)


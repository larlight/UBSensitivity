import ROOT, sys, os
from ROOT import *
import random, math, time

if len(sys.argv) != 6:
    print 
    print "*** Improper usage. ***"
    print "  Usage: python RootHisto_to_TextFileGenInput.py "
    print "\t /path/to/root/file/file.root " #sys.argv[1]
    print "\t name_of_root_2Dhisto "         #sys.argv[2]
    print "\t n_evts_to_generate "           #sys.argv[3]
    print "\t /name/of/output/textfile.txt " #sys.argv[4]
    print "\t pdg_of_singleparticle_to_gen"  #sys.argv[5]
    print 
    sys.exit()

#seed random number generator with system time in ms
random.seed(time.time()*1000.0)

#get input arguments to normal sounding variable names
finname = sys.argv[1]
histname = sys.argv[2]
n_evts_to_generate = int(sys.argv[3])
foutname = sys.argv[4]
pdg = int(sys.argv[5])
if pdg == 11:
    mass = 0.000511
elif pdg == 22:
    mass = 0.
else:
    print "Error! PDG needs to be 11 (electron) or 22 (gamma), or you need to expand this code."
    sys.exit()

#Function to generate random XYZ position inside of the cryostat
#(0,0,0) is at front of cryostat (z), half way up (y), and on the wire plane(x)
#R of cryostat is 1.90 meters
#x goes from R*(1.707) (past cathode plane to cryostat wall) to -R*(0.29289) =-R(1-cos45)
#y goes from -R to R (constrained s.t. x^2+y^2 < R^2)
#z goes uniformly from 0 to 10.79m

#LArSoft and LArLight use cm! Use cm!
def GenXYZPosition():

    R = float(190.)
    zmax = float(1079.)
    #this part assumes (0,0,0) is at front, dead center of cryostat... will shift x later
    #everything here is in cm
    #random theta
    theta = random.uniform(0,2*math.pi)
    #this s parameter is from (http://stackoverflow.com/questions/9203382/generating-random-point-in-a-cylinder)
    s = random.uniform(0,1.)
    #randum radius (radius is 1.93m (1.90 inner) from http://microboone-docdb.fnal.gov:8080/cgi-bin/ShowDocument?docid=903)
    r = math.sqrt(s)*R
    #there are some sqrts involved because http://mathworld.wolfram.com/DiskPointPicking.html
    x = r*math.cos(theta)
    y = r*math.sin(theta)
    #random z location
    z = random.uniform(0,zmax)

    #x is shifted because (0,0,0) in larsoft is on the right side of the detector
    x = x + 0.707*R
    return (x,y,z)

#Function to generate random unit-direction, given the Uz value
def GenXYZDirection(uz):
    #uz is given, do not alter it
    leftover = 1. - uz**2
    frac = random.uniform(0,leftover)
    ux = frac**0.5
    uy = (leftover-frac)**0.5
    #ux and uy are always positive. randomly make them negative
    ux = ux * random.choice([-1,1])
    uy = uy * random.choice([-1,1])
    return(ux,uy,uz)
    

#ROOT input file with the 2D histogram we're drawing from
fin = TFile(finname,"READ")
#copying the histo so we can clos the input file
hist2D = fin.Get(histname)
#so we don't lose histo after closing input file
hist2D.SetDirectory(0)
#close the input file because we don't need it anymore
fin.Close()


##########################################################
# Here is the format of the output file we want
# Taken from TextFileGen_module.cc in LArSoft
#
# In brief each event contains at least two                                                          
# lines.  The first line contains two entries, the event number (which is 
# ignored in ART/LArSoft) and the number of particles in the event.  Each 
# following line containes 15 entries to describe each particle.  The entries 
# are:                 
#            
#  1) status code (should be set to 1 for any particle to be tracked, others 
#     won't be tracked)
#  2) the pdg code for the particle 
#  3) the entry of the first mother for this particle in the event,
#     0 means no mother 
#  4) the entry of the second mother for this particle in the event,
#     0 means no mother     
#  5) the entry of the first daughter for this particle in the event,
#     0 means no mother  
#  6) the entry of the second daughter for this particle in the event, 
#     0 means no mother  
#  7) x component of the particle momentum
#  8) y component of the particle momentum 
#  9) z component of the particle momentum 
# 10) energy of the particle 
# 11) mass of the particle       
# 12) x position of the particle initial position 
# 13) y position of the particle initial position  
# 14) z position of the particle initial position 
# 15) time of the particle production    
#                                          
# For example, if you want to simulate a single muon with a 5 GeV energy
# moving only in the z direction, the entry would be 
#
# 0 1 
# 1 13 0 0 0 0 0. 0. 1.0 5.0011 0.105 1.0 1.0 1.0 0.0 
##########################################################


#open the output txt file for writing (overwriting if already exists)
fout = open(foutname,"w")

current_event_counter = int(0)
Evis = ROOT.Double(0.)
Uz = ROOT.Double(0.)

#debugging histo to see uniform cylinder distribution
#h = TH3D("h","histo3d",100,-1000,5000,100,-3000,3000,100,-1000,12000)

while current_event_counter < n_evts_to_generate:
    #Draw from the histogram to get Uz and Evis
    hist2D.GetRandom2(Evis,Uz)
    #Evis is in MeV in histogram, want GeV for txt file
    EvisMEV = Evis / 1000.
    #Generate random XYZ position inside of cryostat cylinder
    myxyz = GenXYZPosition()
    #Generate random X and Y momentum components given the Uz constraint
    myuxuyuz = GenXYZDirection(Uz)
    #bug fix: momentum vector should NOT be unit vector! px^2+py^2+py^2=E^2
    #multiply each unit vector component by E
    mypxpypz = tuple(x*EvisMEV for x in myuxuyuz)

    #Write to output HEPEVT txt file
    fout.write("0 1\n")
    fout.write("1 %d 0 0 0 0 %f %f %f %f %f %f %f %f 0.0\n" %(pdg,mypxpypz[0],mypxpypz[1],mypxpypz[2],EvisMEV,mass,myxyz[0],myxyz[1],myxyz[2]))

    #debug
    #h.Fill(myxyz[0],myxyz[1],myxyz[2])
    current_event_counter += 1

#debug
#h.Draw()
#sys.stdin.readline()

#close the output txt file
fout.close()

print "Done! Generated file %s." % foutname

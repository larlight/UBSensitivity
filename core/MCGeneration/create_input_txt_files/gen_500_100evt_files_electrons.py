import os, sys

print
print "WARNING! This will overwite files in /a/data/morningside/kaleko/condor_LEE_output/single_electrons/input_txt_files ..."
print "Are you SURE you want to do this? If you've already generated a bunch of MC, this could lose important info..."
print "ctrl+C to get the hell out of here if you don't want to overwrite. Otherwise, enter to continue."
print
sys.stdin.readline()

for i in xrange(500):
    os.system("python RootHisto_to_TextFileGenInput.py /a/home/houston/kaleko/condor/condor_LArLight/LEE_stuff/create_input_txt_files/dist_2D_new.root hist_raw_uz_evis_smooth 100 /a/data/morningside/kaleko/condor_LEE_output/single_electrons/input_txt_files/e_LEE_txtinput_%03d.txt 11" % int(i))

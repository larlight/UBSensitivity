import sys
import os

njobs = int(500)

for ijob in xrange(njobs):

    task_name = "e_LEE_%03d" % ijob
    larlight_out_name = "e_LEE_LArLight_out_%03d.root" % ijob
    larsoft_out_name = "e_LEE_LArSoft_out_%03d.root" % ijob
    text_input_name = "e_LEE_txtinput_%03d.txt" % ijob
    cmd_input_name = "e_LEE_%03d.cmd" % ijob
    fcl_input_name = "e_prodtext_and_scanner_%03d.fcl" % ijob
    input_txt_file = "/a/data/morningside/kaleko/condor_LEE_output/single_electrons/input_txt_files/%s" % text_input_name
    custom_cmd_file = "/a/home/houston/kaleko/condor/condor_LArLight/LEE_stuff/generated_cmd_files/%s" % cmd_input_name
    custom_fcl_file = "/a/home/houston/kaleko/condor/condor_LArLight/LEE_stuff/generated_fcl_files/%s" % fcl_input_name

    #if the input text file exists
    if os.path.isfile(input_txt_file):

        #create a custom cmd file from the templage
        os.system("sed 's/XXXFCLFILENAMEXXX/%s/g' /a/home/houston/kaleko/condor/condor_LArLight/LEE_stuff/larlight_LEE_study_template_electrons.cmd > %s" % (fcl_input_name, custom_cmd_file ))
        #additional edits to the custom cmd file, done "in place" on the already created custom fcl file
        os.system("sed -i 's/XXXINPUTTEXTFILEXXX/%s/g' %s " % (text_input_name,custom_cmd_file) )
        os.system("sed -i 's/XXXTASKNAMEXXX/%s/g' %s " % (task_name,custom_cmd_file) )

        #create a custom fcl file from the template
        os.system("sed 's/XXXLARLIGHTOUTPUTXXX/%s/g' /a/home/houston/kaleko/condor/condor_LArLight/LEE_stuff/prodtext_and_scanner_TEMPLATE.fcl > %s" % (larlight_out_name,custom_fcl_file))
        #additional edits to the custom fcl, done "in place" on the already created custom fcl file
        os.system("sed -i 's/XXXLARSOFTOUTPUTXXX/%s/g' %s " % (larsoft_out_name,custom_fcl_file) )
        os.system("sed -i 's/XXXTEXTINPUTXXX/%s/g' %s " % (text_input_name,custom_fcl_file) )

        #submit the condor job
        os.system("condor_submit %s" % custom_cmd_file)
    else: 
        print "ERROR!!! input_txt_file %s DOES NOT EXIST! Not submitting jobs.... you moron." % input_txt_file
        quit()
        

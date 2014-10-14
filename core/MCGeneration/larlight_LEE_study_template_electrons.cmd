#pick a name for job--can be anything
Task	= XXXTASKNAMEXXX

#number of condor jobs
Jobs 	= 1

InputTextFile = XXXINPUTTEXTFILEXXX
CustomFCLFile = XXXFCLFILENAMEXXX

#data directory is where output log, err, out and job files will go
DataDir	= /a/data/morningside/kaleko/condor_LEE_output/single_electrons
#share directory is where we're submitting from
ShareDir = /a/home/houston/kaleko/condor/condor_LArLight/LEE_stuff
CustomFCLDir = $(ShareDir)/generated_fcl_files
InputTextFileDir = $(DataDir)/input_txt_files 

#some standard settings
universe	= vanilla
#Rank		= Mips
Notification 	= Error
#Requirements    = ( Memory>2000 )
initialdir	= $(DataDir)
should_transfer_files = YES
when_to_transfer_output = ON_EXIT

#which files will condor need in order to run the job from any directory
transfer_input_files = $(ShareDir)/larlight_LEE_study.sh, $(InputTextFileDir)/$(InputTextFile), $(CustomFCLDir)/$(CustomFCLFile)

getenv		= true

#your executable file (contains job command)
executable 	= $(ShareDir)/larlight_LEE_study.sh
output		= $(Task)_$(Process).out
error		= $(Task)_$(Process).err
log		= $(Task)_$(Process).log

Arguments	= $(Task) $(Process) $(CustomFCLFile)

queue $(Jobs)
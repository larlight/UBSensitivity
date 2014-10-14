#!/bin/bash

#input arguments are:
# $1 = Task
# $2 = Process
# $3 = Custom FCL filename

#source /a/share/westside/seligman/microboone/setup_uboone.sh
#in case the larsoft setups change directories, store the current batch directory
export CURRENT_WORKING_DIRECTORY=`pwd`
#source /a/share/morningside/kaleko/KALEKO_SETUP_UBOONE.sh
echo "sourcing seligman stuff"
pwd
source /a/share/westside/seligman/microboone/setup_uboone.sh 
#setup larsoft v02_01_01 -q e5:prof 
echo "setup uboonecode now"
pwd
setup uboonecode v03_02_00 -q e6:prof
echo "sourcing larlight stuff"
pwd
source /a/share/morningside/kaleko/LArLight/config/setup.sh 
#source /a/data/morningside/kaleko/mrb_dev_00/localProducts_larsoft_v02_01_01_e5_prof/setup
echo "sourcing larsoft localproducts setup"
pwd
source /a/data/morningside/kaleko/mrb_dev_00/localProducts_larsoft_v03_02_00_e6_prof/setup
echo "running mrbslp"
pwd
mrbslp
export FHICL_FILE_PATH=$MRB_TOP/srcs/uboonecode/uboone/MCShowerReco/job:$FHICL_FILE_PATH
export FHICL_FILE_PATH=$MRB_TOP/srcs/uboonecode/uboone/DataScanner/job:$FHICL_FILE_PATH
cd $CURRENT_WORKING_DIRECTORY

#fcl file should be transferred into the working directory
export command="lar -c $3"

echo "I am executing the command: $command"
echo "And an ls from this current directory gives:"
ls -ltr
echo "and a cat of the fcl file gives:"
cat $3

eval $command

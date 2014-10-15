from ROOT import *
import sys

if len(sys.argv) != 2:
    print "USAGE: python test_config_reader.py name_of_config_file.config"
    quit()

gSystem.Load("libAnaConfig.so")

cr = ubsens.config.ConfigReader()
cr.SetConfigFile(sys.argv[1])
cr.Read()
cr.Dump()

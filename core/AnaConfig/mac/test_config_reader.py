from ROOT import *
gSystem.Load("libAnaConfig.so")

cr = ubsens.config.ConfigReader()
cr.SetConfigFile("test_config.config")
cr.Read()
cr.Dump()

from ROOT import *
gSystem.Load("libLEE.so")
nlc = ubsens.NuLeptECorrelation()

nlc.SetFilename("/Users/davidkaleko/Data/LEE/combined_ntuple_470m_nu_fosc_CC_nu_lept_energycorrelation.root")
nlc.SetTH2Fname("fosc_isCC_enugen_vs_Elep")

nlc.LoadInputTH2F()

print "With one draw, lepton energy of 1 turns into: %f" \
    % nlc.NuEFromLeptE(1)
print "With one draw, lepton energy of 1 turns into: %f" \
    % nlc.NuEFromLeptE(1)
print "With one draw, lepton energy of 1 turns into: %f" \
    % nlc.NuEFromLeptE(1)
print "With one draw, lepton energy of 1 turns into: %f" \
    % nlc.NuEFromLeptE(1)

print "With 100 draws, lepton energy of 1 turns into: %f" \
    % nlc.NuEFromLeptE(1,100)
print "With 100 draws, lepton energy of 1 turns into: %f" \
    % nlc.NuEFromLeptE(1,100)
print "With 100 draws, lepton energy of 1 turns into: %f" \
    % nlc.NuEFromLeptE(1,100)
print "With 100 draws, lepton energy of 1 turns into: %f" \
    % nlc.NuEFromLeptE(1,100)

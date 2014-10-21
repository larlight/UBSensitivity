/**
 * \file NuLeptECorrelation.hh
 *
 * \ingroup LEE
 * 
 * \brief This class reads in a fullosc file, makes a TH2F showing the
 * correlation between lepton energy and true neutrino energy, then has
 * a function that takes in lepton energy and draws randomly to spit out
 * a true neutrino energy (or vice versa).
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef NULEPTECORRELATION_HH
#define NULEPTECORRELATION_HH

#include <iostream>
#include "LEEBase.hh"
#include "Utilities/PlotReader.hh"
#include "Utilities/PlotWriter.hh"
#include "Utilities/FindInMapMap.hh"

#include "TH2.h"
/**
   \class NuLeptECorrelation
   User defined class NuLeptECorrelation ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens{
  
  class NuLeptECorrelation : public LEEBase {
    
  public:
    
    /// Default constructor
    NuLeptECorrelation()
    {
      _my_fosc_filename = "";
      _my_th2f_name = "";
      _my_th2f = 0;
      _my_tmp_slice = 0;
      _name = "NuLeptECorrelation";
    };

    /// Inherited configure function from LEEBase
    virtual bool Configure(const std::map<std::string,std::map<std::string,std::string>> &_configMap);
    
    /// Inherited writeplots function from LEEBase
    void WritePlots();
    
    /// Default destructor
    virtual ~NuLeptECorrelation(){};
    
    /// NOTE: input TH2F needs to be True neutrino energy (y-axis)
    /// vs. True lepton energy (x-axis). This is normally gotten from
    /// a fosc file. I took the fosc file, made a TH2F, and saved it to
    /// a separate file, for cleanliness.
    bool LoadInputTH2F();

    /// Function that uses the input TH2F to return a true neutrino energy
    /// from an input lepton energy. It takes a slice of the TH2F corresponding
    /// to that lepton energy, then draws a random number from that distribution.
    double NuEFromLeptE(double lept_e);

  private:
    
    std::string _my_fosc_filename;
    std::string _my_th2f_name;
    TH2F *_my_th2f;
    TH1D *_my_tmp_slice;
    
  };
  
}//end namespace ubsens
#endif
/** @} */ // end of doxygen group 


/**
 * \file ConfigConstants.hh
 *
 * \ingroup AnaConfig
 * 
 * \brief Analysis Configuration constants
 *
 * @author davidkaleko
 */

/** \addtogroup AnaConfig

    @{*/

#ifndef CONFIGCONSTANTS_HH
#define CONFIGCONSTANTS_HH

namespace ubsens{

  namespace config{

    enum MODULE_TYPE_t {
      FLUXSCALING,
      NULEPTECORRELATION,
      POTSCALING,
      TONNAGESCALING,
      XSECSCALING,
      PLOTREADER,
      PLOTWRITER,

      MAX_MODULE_TYPE
    };

    const std::string MODULE_NAME[MAX_MODULE_TYPE] = {
      "FluxScaling",
      "NuLeptECorrelation",
      "POTScaling",
      "TonnageScaling",
      "XSecScaling",
      "PlotReader",
      "PlotWriter",
    };

    //    static const std::string UNSET_STRING = "AHFAOAWEFHIOPEQHFQPIEFH";
    
  }// end namespace config
}// end namespace ubsens

#endif

/** @} */ // end of doxygen group Message

/**
 * \file FMWKConstants.hh
 *
 * \ingroup FMWKBase
 * 
 * \brief Framework base constants
 *
 * @author Kazu - Nevis 2013
 */

/** \addtogroup FMWKBase

    @{*/

#ifndef FMWKCONSTANTS_H
#define FMWKCONSTANTS_H

#include <string>
#include <limits>
#include <climits>

namespace ubsens {

  namespace fmwk {
    
    // Useful constants to show "undefined" values
    static const float          INVALID_FLOAT  = std::numeric_limits<float>::max();
    static const double         INVALID_DOUBLE = std::numeric_limits<double>::max();
    static const char           INVALID_CHAR   = std::numeric_limits<char>::max();
    static const short          INVALID_SHORT  = std::numeric_limits<short>::max();
    static const int            INVALID_INT    = std::numeric_limits<int>::max();
    static const unsigned char  INVALID_UCHAR  = std::numeric_limits<unsigned char>::max();
    static const unsigned short INVALID_USHORT = std::numeric_limits<unsigned short>::max();
    static const unsigned int   INVALID_UINT   = std::numeric_limits<unsigned int>::max();
    static const size_t         INVALID_SIZE_T = std::numeric_limits<size_t>::max();

    namespace msg {

      enum VerbosityLevel_t {
	kDEBUG,     ///< DEBUG message level ... hyper verbose
	kINFO,      ///< INFO message level ... annoying-cout level verbosity
	kNORMAL,    ///< NORMAL message level ... not too verbose for normal mode running
	kWARNING,   ///< WARNING message level ... for those who love quiet env.
	kERROR,     ///< ERROR message level ... for those who want to ignore warnings
	kEXCEPTION, ///< EXCEPTION message level ... if you want to run till death
	kVERBOSITY_LEVEL_MAX
      };
      
      const std::string ColorPrefix[kVERBOSITY_LEVEL_MAX] =
	{
	  "\033[94m", ///< blue ... DEBUG   
	  "\033[92m", ///< green ... INFO
	  "\033[95m", ///< magenta ... NORMAL
	  "\033[93m", ///< yellow ... WARNING
	  "\033[91m"  ///< red ... ERROR
	};
      ///< Color coding of message
      
      const std::string StringPrefix[kVERBOSITY_LEVEL_MAX] =
	{
	  "     [DEBUG]  ", ///< DEBUG message prefix
	  "      [INFO]  ", ///< INFO message prefix
	  "    [NORMAL]  ", ///< NORMAL message prefix
	  "   [WARNING]  ", ///< WARNING message prefix 
	  "     [ERROR]  "  ///< ERROR message prefix
	};
      ///< Prefix of message

    }

  } //end namespace fmwk

} //end namespace ubsens

#endif
/** @} */ // end of doxygen group Message

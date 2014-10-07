#ifndef FMWKCONSTANTS_H
#define FMWKCONSTANTS_H

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
  } //end namespace fmwk

} //end namespace ubsens
  

#endif

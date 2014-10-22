/**
 * \file StringParser.hh
 *
 * \ingroup Utilities
 * 
 * \brief Class that takes in strings and has different functions
 * to parse/return different things out of those strings.
 * I.E. take in "[3,4,5]" and return std::vector<double>{3,4,5}
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef STRINGPARSER_HH
#define STRINGPARSER_HH

#include "FMWKBase/FMWKBase.hh"
#include "FMWKBase/FMWKException.hh"
#include <vector>


/**
   \class StringParser
   Class that takes in strings and has different functions
   to parse/return different things out of those strings.
   I.E. take in "[3,4,5]" and return std::vector<double>{3,4,5}
*/
namespace ubsens{
  namespace util{
    
    class StringParser : public ::ubsens::fmwk::FMWKBase {
      
    public:
      
      /// Default constructor
      StringParser(){ _name = "StringParser"; };
      
      /// Default destructor
      virtual ~StringParser(){};
      
      const std::vector<double>* ParseBinsString(std::string binstring);
      
    };
  }// end namespace util
}// end namespace ubsens

#endif
/** @} */ // end of doxygen group 


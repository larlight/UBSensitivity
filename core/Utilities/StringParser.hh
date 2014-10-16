/**
 * \file StringParser.hh
 *
 * \ingroup Utilities
 * 
 * \brief Class def header for a class StringParser
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef STRINGPARSER_HH
#define STRINGPARSER_HH

#include <iostream>

/**
   \class StringParser
   User defined class StringParser ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{
  namespace util{

    class StringParser{
      
    public:
      
      /// Default constructor
      StringParser(){};
      
      /// Default destructor
      virtual ~StringParser(){};
      
      const double* ParseBinsString(std::string binstring);

    };
  }// end namespace util
}// end namespace ubsens
    
#endif
/** @} */ // end of doxygen group 


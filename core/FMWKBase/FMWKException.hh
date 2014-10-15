/**
 * \file FMWKException.hh
 *
 * \ingroup FMWKBase
 * 
 * \brief Class def header for a class FMWKException
 *
 * @author davidkaleko
 */

/** \addtogroup FMWKBase

    @{*/
#ifndef FMWKEXCEPTION_HH
#define FMWKEXCEPTION_HH

#include <iostream>
#include <exception>
#include <sstream>

/**
   \class FMWKException
   User defined class FMWKException ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens{

  namespace fmwk{

    class FMWKException : public std::exception{
      
    public:
      
      FMWKException(std::string msg="") : std::exception(), _msg(msg)
      {}
      
      virtual ~FMWKException() throw(){};
      virtual const char* what() const throw() 
      {return _msg.c_str(); }
      
    private:
      
      std::string _msg;
      
    };
    
  } //end namespace fmwk
}//end namespace ubsens

#endif
/** @} */ // end of doxygen group 


/**
 * \file LEEException.hh
 *
 * \ingroup LEE
 * 
 * \brief Class def header for a class LEEException
 *
 * @author davidkaleko
 */

/** \addtogroup LEE

    @{*/
#ifndef LEEEXCEPTION_HH
#define LEEEXCEPTION_HH

#include <iostream>
#include <exception>

/**
   \class LEEException
   User defined class LEEException ... these comments are used to generate
   doxygen documentation!
*/

namespace ubsens{
  
  class LEEException : public std::exception{
    
  public:
    
    LEEException(std::string msg="") : std::exception(), _msg(msg)
    {}
    
    virtual ~LEEException() throw(){};
    virtual const char* what() const throw() 
    {return _msg.c_str(); }
    
  private:
    
    std::string _msg;
    
  };
  
}//end namespace ubsens

#endif
/** @} */ // end of doxygen group 


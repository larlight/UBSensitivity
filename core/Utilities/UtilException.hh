/**
 * \file UtilException.hh
 *
 * \ingroup Utilities
 * 
 * \brief Class def header for a class UtilException
 *
 * @author davidkaleko
 */

/** \addtogroup Utilities

    @{*/
#ifndef UTILEXCEPTION_HH
#define UTILEXCEPTION_HH

#include <iostream>
#include <exception>

/**
   \class UtilException
   User defined class UtilException ... these comments are used to generate
   doxygen documentation!
 */

namespace ubsens{

  namespace util {
    
    class UtilException : public std::exception{
      
    public:
      
      UtilException(std::string msg="") : std::exception(), _msg(msg)
      {}
      

      virtual ~UtilException() throw(){};
      virtual const char* what() const throw() 
      {return _msg.c_str(); }
      
    private:
      
      std::string _msg;
    };
    
  }//end namespace util

}//end namespace ubsens
#endif
  /** @} */ // end of doxygen group 
  

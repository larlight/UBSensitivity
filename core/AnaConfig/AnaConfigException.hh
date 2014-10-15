/**
 * \file AnaConfigException.hh
 *
 * \ingroup AnaConfig
 * 
 * \brief Class def header for a class AnaConfigException
 *
 * @author davidkaleko
 */

/** \addtogroup AnaConfig

    @{*/
#ifndef ANACONFIGEXCEPTION_HH
#define ANACONFIGEXCEPTION_HH

#include <iostream>
#include <exception>

/**
   \class AnaConfigException
   User defined class AnaConfigException ... these comments are used to generate
   doxygen documentation!
 */


namespace ubsens{
  
  namespace config{
    
    class AnaConfigException : public std::exception{
    
    public:
      
      AnaConfigException(std::string msg="") : std::exception(), _msg(msg)
      {}
      
      virtual ~AnaConfigException() throw(){};
      virtual const char* what() const throw() 
      {return _msg.c_str(); }
      
    private:
      
      std::string _msg;
      
    };
  
  }// end namespace config

}//end namespace ubsens
  

#endif
/** @} */ // end of doxygen group 


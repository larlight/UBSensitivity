/**
 * \file DHException.hh
 *
 * \ingroup DataHandle
 * 
 * \brief Class def header for a class DHException
 *
 * @author kazuhiro
 */

/** \addtogroup DataHandle

    @{*/
#ifndef DHEXCEPTION_HH
#define DHEXCEPTION_HH

#include <string>
#include <exception>

namespace ubsens {

  namespace data {
    /**
       \class DHException
       Exception class used for DataHandle package
    */
    class DHException : public std::exception {
      
    public:

      /// Default constructor
      DHException() : std::exception ()
      { _msg = "thrown for unknown reason!";}
      
      /// Alternative constructor
      DHException(std::string msg) : std::exception ()
      {
	_msg  = "\033[93m";
	_msg += msg.c_str();
	_msg += "\033[00m";
      }

      /// Yet-another alternative constructor
      DHException(std::string origin, std::string msg) : std::exception ()
      {
	_msg  = "\033[95m<<";
	_msg += origin.c_str();
	_msg += "\033[00m>> ";
	_msg += "\033[93m";
	_msg += msg.c_str();
	_msg += "\033[00m";
      }
      
      /// Default destructor
      virtual ~DHException() throw() {}

      /// Implementation of std::exception::what()
      virtual const char* what() const throw() 
      { return _msg.c_str(); }

    private:

      /// message holder
      std::string _msg;
      
    };
  }
}

#endif
/** @} */ // end of doxygen group 


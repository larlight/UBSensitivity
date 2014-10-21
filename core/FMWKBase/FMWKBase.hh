/**
 * \file FMWKBase.hh
 *
 * \ingroup FMWKBase
 * 
 * \brief Base of all base classes! Includes messenger service, and _name string
 *  to be inherited by all classes (and filled in constructors)
 *
 * @author davidkaleko
 */

/** \addtogroup FMWKBase

    @{*/
#ifndef FMWKBASE_HH
#define FMWKBASE_HH

#include <iostream>
#include "Message.hh"

/**
   \class FMWKBase
   Base of all base classes! Includes messenger service, and _name string
   to be inherited by all classes (and filled in constructors)
*/

namespace ubsens{
  
  namespace fmwk{

    class FMWKBase{
      
    public:
      
      /// Default constructor
      FMWKBase(){ _name="FMWKBase"; };
      
      /// Default destructor
      virtual ~FMWKBase(){};
      
      /// Getter for the class name
      inline const std::string class_name() const {return _name;};
      
      //protected means classes can inherit this through "public", but
      //it is not publicly accessible through a instance of LEEBase() class
      //(i think)
    protected:
      
      /// Messenger instance, to be inherited by many LEE classes
      ::ubsens::fmwk::Message fMsg;

      /// Class name (should be filled in each child class's constructor)
      std::string _name;
      
    };
    
  }// end namespace fmwk
  
}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


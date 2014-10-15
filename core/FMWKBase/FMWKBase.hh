/**
 * \file FMWKBase.hh
 *
 * \ingroup FMWKBase
 * 
 * \brief Class def header for a class FMWKBase
 *
 * @author davidkaleko
 */

/** \addtogroup FMWKBase

    @{*/
#ifndef FMWKBASE_HH
#define FMWKBASE_HH

#include <iostream>

/**
   \class FMWKBase
   User defined class FMWKBase ... these comments are used to generate
   doxygen documentation!
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
      
    protected:
      
      std::string _name;
      
      
    };
    
  }// end namespace fmwk
  
}// end namespace ubsens
#endif
/** @} */ // end of doxygen group 


/**
 * \file DataBase.hh
 *
 * \ingroup DataHandle
 * 
 * \brief Class def header for a class DataBase
 *
 * @author davidkaleko
 */

/** \addtogroup DataHandle

    @{*/
#ifndef DATABASE_HH
#define DATABASE_HH

#include "TObject.h" //allows me to use UInt_t...is this the best way?
#include <iostream>

/**
   \class DataBase
   User defined class DataBase ... these comments are used to generate
   doxygen documentation!
 */
namespace ubsens {

  namespace data {

    class DataBase{
      
    public:
      
      /// Default constructor
      DataBase(){};
      
      /// Default destructor
      virtual ~DataBase(){};
      
      /// Method to bring back the default values
      void Reset();

    protected:
      
      UInt_t fEventID;

    };
    
  }//end namespace data
  
}//end namespace ubsens
#endif
/** @} */ // end of doxygen group 


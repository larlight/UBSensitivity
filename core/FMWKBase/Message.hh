/**
 * \file Message.hh
 *
 * \ingroup FMWKBase
 * 
 * \brief Message utility class definition header file.
 *
 * @author Kazu - Nevis 2013
 */

/** \addtogroup FMWKBase

    @{*/

#ifndef MESSAGE_HH
#define MESSAGE_HH

#include <cstdio>
#include <iostream>
#include "FMWKConstants.hh"

namespace ubsens {
  
  namespace fmwk {
    /**
       \class Message
       \brief Utility class used to show formatted message on the screen.
    */
    class Message{
      
    public:

      /// Default constructor ... make it private to limit the duplication of instance
      Message(){};
      
      /// Default destructor
      virtual ~Message(){};
      
      /// Static method to send message out.
      void send(msg::VerbosityLevel_t level, std::string msg);
      
      /// Extra argument "where" is used to indicate function/class name.
      void send(msg::VerbosityLevel_t level, std::string where, std::string msg);
      
    };
  }
}
#endif
  
/** @} */ // end of doxygen group Message

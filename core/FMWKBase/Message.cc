#ifndef MESSAGE_CC
#define MESSAGE_CC

#include "Message.hh"
namespace ubsens {

  namespace fmwk {
    
    void Message::send(msg::VerbosityLevel_t level, std::string msg)
    {
      std::cout 
	<< msg::ColorPrefix[level].c_str()
	<< msg::StringPrefix[level].c_str()
	<< "\033[0m"
	<< msg.c_str()
	<< std::endl;
    }
    
    void Message::send(msg::VerbosityLevel_t level, std::string where, std::string msg)
    {
      std::cout 
	<< msg::ColorPrefix[level].c_str()
	<< msg::StringPrefix[level].c_str()
	<< "\033[0m"
	<< "\033[95m"
	<< "<"
	<< where.c_str()
	<< "> "
	<< "\033[0m"
	<< msg.c_str()
	<< std::endl;
    }
  }
}
#endif

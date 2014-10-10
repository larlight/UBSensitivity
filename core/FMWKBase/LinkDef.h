//
// cint script to generate libraries
// Declaire namespace & classes you defined
// #pragma statement: order matters! Google it ;)
//

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace ubsens+;
#pragma link C++ namespace ubsens::fmwk+;
#pragma link C++ namespace ubsens::fmwk::msg+;
#pragma link C++ enum ubsens::fmwk::msg::VerbosityLevel_t;

#pragma link C++ class ubsens::fmwk::Message+;
//ADD_NEW_CLASS ... do not change this line
#endif

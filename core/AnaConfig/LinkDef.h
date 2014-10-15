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
#pragma link C++ namespace ubsens::config+;

#pragma link C++ class ubsens::config::ConfigReader+;
#pragma link C++ class ubsens::config::ConfigManager+;
//ADD_NEW_CLASS ... do not change this line
#endif




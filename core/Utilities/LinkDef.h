//
// cint script to generate libraries
// Declaire namespace & classes you defined
// #pragma statement: order matters! Google it ;)
//

#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace ubsens::util+;
#pragma link C++ class ubsens::util::Utilities+;
#pragma link C++ class ubsens::util::TGraphReader+;

#pragma link C++ class ubsens::util::PlotWriter+;
//ADD_NEW_CLASS ... do not change this line
#endif


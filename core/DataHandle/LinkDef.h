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
#pragma link C++ namespace ubsens::data+;
#pragma link C++ class ubsens::data::RecoShower+;
#pragma link C++ class std::vector<ubsens::data::RecoShower>+;
#pragma link C++ class ubsens::data::TruthShower+;
#pragma link C++ class std::vector<ubsens::data::TruthShower>+;
#pragma link C++ class ubsens::data::EventRecord+;
#pragma link C++ class ubsens::data::DHException+;
#pragma link C++ class ubsens::data::DataManager+;
//ADD_NEW_CLASS ... do not change this line
#endif








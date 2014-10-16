{
  gSystem->Load("libUtilities.so");
  
  ubsens::util::StringParser sp = ubsens::util::StringParser();
  
  std::string string = "[3,5,6.2]";
  
  const std::vector<double>* answer = sp.ParseBinsString(string);
  
  std::cout<<"Input string was \""<<string<<"\""<<std::endl;
  std::cout<<"Output vector is [";
  for (size_t i = 0; i < answer->size(); i++)
    std::cout<<answer->at(i)<<", ";
  std::cout<<"]"<<std::endl;

  std::string string = "[2345. ,5.52,    9.99, 10,10.1122 ]   ";

  const std::vector<double>* answer = sp.ParseBinsString(string);
  
  std::cout<<"Input string was \""<<string<<"\""<<std::endl;
  std::cout<<"Output vector is [";
  for (size_t i = 0; i < answer->size(); i++)
    std::cout<<answer->at(i)<<", ";
  std::cout<<"]"<<std::endl;

  std::string string = "[2345. ,5.52,    9.99, 10,10.1122    ";

  const std::vector<double>* answer = sp.ParseBinsString(string);
  
  std::cout<<"Input string was \""<<string<<"\""<<std::endl;
  std::cout<<"Output vector is [";
  for (size_t i = 0; i < answer->size(); i++)
    std::cout<<answer->at(i)<<", ";
  std::cout<<"]"<<std::endl;

}

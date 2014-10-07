{
  gSystem->Load("libDataHandle");

  ubsens::data::DataManager mgr;

  mgr.SetIOMode(ubsens::data::DataManager::WRITE);

  mgr.SetOutputFilename("aho.root");

  mgr.Open();

  mgr.SaveEntry();

  mgr.SaveEntry();

  mgr.Close();

  mgr.SetIOMode(ubsens::data::DataManager::READ);

  mgr.AddInputFilename("aho.root");
  
  mgr.Open();

  std::cout<< mgr.GetEntries() << std::endl;

  mgr.Close();
}



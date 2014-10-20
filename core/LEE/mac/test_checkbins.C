{

  gSystem.Load("libLEE");
  fp = ubsens::FinalPlotter();
  
  TH1F *hist = new TH1F("hist","histtitle",5,0,10);
  std::vector<double> *myvec = new std::vector<double>;
  myvec->push_back(0);
  myvec->push_back(4);
  myvec->push_back(6);

  bool good = fp.CheckBins(hist,myvec);
  std::cout<<"Are bins good? "<<good<<std::endl;


  TH1F *hist2 = new TH1F("hist2","histtitle",5,0,10.97523);
  good = fp.CheckBins(hist2,myvec);
  std::cout<<"how about now? "<<good<<std::endl;

  delete hist;
  delete hist2;
  
  exit();
}

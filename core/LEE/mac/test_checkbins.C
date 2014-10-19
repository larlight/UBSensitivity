{

  gSystem.Load("libLEE");
  fp = ubsens::FinalPlotter();
  
  TH1F *hist = new TH1F("hist","histtitle",5,0,10);
  std::vector<double> *myvec = new std::vector<double>;
  myvec->push_back(0);
  myvec->push_back(4);
  myvec->push_back(6);

  std::cout<<"hist is "<<hist<<std::endl;
  std::cout<<"myvec is "<<myvec<<std::endl;

  std::cout<<"here"<<std::endl;

  fp.CheckBins(hist,myvec);

  std::cout<<"here2"<<std::endl;

  
}

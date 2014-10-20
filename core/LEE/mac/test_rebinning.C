{
  gSystem.Load("libLEE");
  ubsens::FinalPlotter fp;
  TH1F* h = new TH1F("h","hist",20,0,5);
  std::vector<double> *myvec = new std::vector<double>();
  myvec->push_back(0);
  myvec->push_back(1.0);
  fp.RebinTH1F(h,myvec);

  exit();
}

#ifndef DATAMANAGER_CC
#define DATAMANAGER_CC

#include "DataManager.hh"

namespace ubsens {

  namespace data {

    DataManager::DataManager() : fData(nullptr),
				 fInTree(nullptr),
				 fOutTree(nullptr),
				 fOutFile(nullptr),
				 fIOMode(DataManager::READ),
				 fInFileName(),
				 fOutFileName("")
    {
      Reset();
    }

    DataManager::~DataManager()
    {
      delete fData;
    }

    void DataManager::Reset()
    {
      if(fInTree)  { delete fInTree;    fInTree = nullptr;  }
      if(fOutFile) { fOutFile->Close(); fOutFile = nullptr; }
      if(!fData)   fData = new EventRecord;
      // Whether fInTree/fOutTree belongs to InFile or OutFile, it should be deleted by this point
      fInTree  = nullptr;
      fOutTree = nullptr;
      fData->Reset();

      fIOMode = DataManager::READ;
      fInFileName.clear();
      fOutFileName = "";
      fTreeIndex = fmwk::INVALID_SIZE_T;
      fInTreeEntries = 0;
      fOutTreeEntries = 0;
    }

    bool DataManager::NextEntry()
    {
      return GetEntry(fTreeIndex+1);
    }

    bool DataManager::GetEntry(size_t index)
    {
      if(index >= GetEntries()) {
	std::cerr << "\033[93m<<" 
		  << __FUNCTION__ 
		  << ">>\033[00m"
		  << " Index " << index 
		  << " is beyond event counts in the TTree ... " << GetEntries()
		  << std::endl;
	return false;
      }

      fInTree->GetEntry(index);
      fTreeIndex = index;
      return true;
    }

    void DataManager::SaveEntry()
    {
      if(!fOutTree)
	throw DHException(__FUNCTION__,"Output TTree does not exist... can't save an entry!");
      fOutTree->Fill();
      ++fOutTreeEntries;
      fData->Reset();
    }

    size_t DataManager::GetEntries()
    {
      if(fInTreeEntries) return fInTreeEntries;
      if(!fInTree) 
	throw DHException(__FUNCTION__,"Input TTree does not exist... can't get an entry!");
      fInTreeEntries = fInTree->GetEntriesFast();
      return fInTreeEntries;
    }

    void DataManager::Open()
    {

      if(fInTree || fOutTree) 
	
	throw DHException(__FUNCTION__,"Call Reset() before (re-)open a file!");

      if(fIOMode == DataManager::WRITE ||
	 fIOMode == DataManager::BOTH ) {
	
	if(fOutFileName.empty()) 
	  throw DHException(__FUNCTION__,"Output file name not specified!");

	fOutFile = TFile::Open(fOutFileName.c_str(),"RECREATE");
	fOutTree = new TTree("ubsens_tree","");
	fOutTree->Branch("event","EventRecord",fData);
      }

      if(fIOMode == DataManager::READ ||
	 fIOMode == DataManager::BOTH ) {

	if(fInFileName.empty()) 
	  throw DHException(__FUNCTION__,"Input file name not specified!");

	fInTree = new TChain("ubsens_tree","");
	for(auto const& f_name : fInFileName)
	  fInTree->AddFile(f_name.c_str());
	
	if(!(fInTree->GetEntries()))
	  throw DHException(__FUNCTION__,"Input file does not contain data tree!");

	fInTree->SetBranchAddress("event",&fData);
	
      }
      // Reset Tree index
      fTreeIndex = fmwk::INVALID_SIZE_T;
           
    }

    void DataManager::Close()
    {
      if(fOutTree) {
	fOutFile->cd();
	fOutTree->Write();
      }
      Reset();
    }

  }

}

#endif

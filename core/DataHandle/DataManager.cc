#ifndef DATAMANAGER_CC
#define DATAMANAGER_CC

#include "DataManager.hh"

namespace ubsens {

  namespace data {

    DataManager::DataManager() : fVerbosity(::ubsens::fmwk::msg::kNORMAL),
				 fData(nullptr),
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
      if(fOutTree)
	delete fOutTree;
      if(fInTree)
	delete fInTree;
      if(fData)
	delete fData;
    }

    void DataManager::Reset()
    {

      if(fVerbosity <= ::ubsens::fmwk::msg::kDEBUG)

	fMsg.send(::ubsens::fmwk::msg::kDEBUG, __FUNCTION__, " called...");

      if(fInTree)  { 

	if(fVerbosity <= ::ubsens::fmwk::msg::kINFO)

	  fMsg.send(::ubsens::fmwk::msg::kINFO, __FUNCTION__,"Removing the input TTree...");

	delete fInTree;    
	fInTree = nullptr;  
      }

      if(fOutFile) { 

	if(fVerbosity <= ::ubsens::fmwk::msg::kWARNING)

	  fMsg.send(::ubsens::fmwk::msg::kWARNING, __FUNCTION__,
		    Form(" %s called before Close(). Closing the output file...",__FUNCTION__));

	Close();
      }

      if(!fData) {

	if(fVerbosity <= ::ubsens::fmwk::msg::kINFO)

	  fMsg.send(::ubsens::fmwk::msg::kINFO, __FUNCTION__,"Removing a local EventRecord instance from the heap...");

	fData = new EventRecord;
      }

      // Whether fInTree/fOutTree belongs to InFile or OutFile, it should be deleted by this point
      fInTree  = nullptr;
      fOutTree = nullptr;

      if(fData){
	//kaleko: sometimes crashes here
	fData->Reset();
      }

      fIOMode = DataManager::READ;
      fInFileName.clear();
      fOutFileName = "";
      fTreeIndex = fmwk::INVALID_SIZE_T;
      fInTreeEntries = 0;
      fOutTreeEntries = 0;
    }

    bool DataManager::NextEntry()
    {
      if(fVerbosity <= ::ubsens::fmwk::msg::kDEBUG)

	fMsg.send(::ubsens::fmwk::msg::kDEBUG, __FUNCTION__, " called...");

      return GetEntry(fTreeIndex+1);
    }

    bool DataManager::GetEntry(size_t index)
    {
      if(fVerbosity <= ::ubsens::fmwk::msg::kDEBUG)

	fMsg.send(::ubsens::fmwk::msg::kDEBUG, __FUNCTION__, " called...");

      if(index > GetEntries()) {

	fMsg.send(::ubsens::fmwk::msg::kINFO, __FUNCTION__, 
		  Form(" Index %zu is beyond event counts in the TTree (%zu)... ",index,GetEntries())
		  );
	return false;
      }

      if(fVerbosity <= ::ubsens::fmwk::msg::kINFO)

	fMsg.send(::ubsens::fmwk::msg::kINFO, __FUNCTION__, " read 1 event from TTree...");

      fInTree->GetEntry(index);
      fTreeIndex = index;
      return true;
    }

    void DataManager::SaveEntry()
    {
      if(fVerbosity <= ::ubsens::fmwk::msg::kDEBUG)

	fMsg.send(::ubsens::fmwk::msg::kDEBUG, __FUNCTION__, " called...");

      if(!fOutTree)
	throw DHException(__FUNCTION__,"Output TTree does not exist... can't save an entry!");
      fOutTree->Fill();
      ++fOutTreeEntries;
      fData->Reset();

      if(fVerbosity <= ::ubsens::fmwk::msg::kINFO)

	fMsg.send(::ubsens::fmwk::msg::kINFO, __FUNCTION__, " saved 1 event to TTree...");
    }

    size_t DataManager::GetEntries()
    {
      if(fVerbosity <= ::ubsens::fmwk::msg::kDEBUG)

	fMsg.send(::ubsens::fmwk::msg::kDEBUG, __FUNCTION__, " called...");

      if(fInTreeEntries) return fInTreeEntries;
      if(!fInTree) 
	throw DHException(__FUNCTION__,"Input TTree does not exist... can't get an entry!");
      fInTreeEntries = fInTree->GetEntriesFast();

      return fInTreeEntries;
    }

    void DataManager::Open()
    {
      if(fVerbosity <= ::ubsens::fmwk::msg::kDEBUG)

	fMsg.send(::ubsens::fmwk::msg::kDEBUG, __FUNCTION__, " called...");

      if(fInTree || fOutTree) 
	
	throw DHException(__FUNCTION__,"Call Reset() before (re-)open a file!");

      if(fIOMode == DataManager::WRITE ||
	 fIOMode == DataManager::BOTH ) {
	
	if(fOutFileName.empty()) 
	  throw DHException(__FUNCTION__,"Output file name not specified!");

	fOutFile = TFile::Open(fOutFileName.c_str(),"RECREATE");
	fOutFile->cd();
	fOutTree = new TTree("ubsens_tree","UBSensitivity Data TTree");
        fOutTree->SetMaxTreeSize    (1024*1024*1024);
	fOutTree->SetMaxVirtualSize (1024*1024*1024);
	fOutTree->Branch("ubsens_branch",fData->GetName(),&fData);
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

	fInTree->SetBranchAddress("ubsens_branch",&fData);
	
      }
      // Reset Tree index
      fTreeIndex = fmwk::INVALID_SIZE_T;
           
    }

    void DataManager::Close()
    {
      if(fVerbosity <= ::ubsens::fmwk::msg::kDEBUG)

	fMsg.send(::ubsens::fmwk::msg::kDEBUG, __FUNCTION__, " called...");

      if(fOutTree) {

	if(fVerbosity <= ::ubsens::fmwk::msg::kNORMAL)
	  
	  fMsg.send(::ubsens::fmwk::msg::kNORMAL, __FUNCTION__,
		    Form("Written the output TTree (%lld events)...",fOutTree->GetEntries()));
	
	fOutFile->cd();
	fOutTree->Write();
	fOutFile->Close();
	fOutFile = nullptr;
	fOutTree = nullptr;
      }
      
      Reset();
    }

  }

}

#endif

/**
 * \file DataManager.hh
 *
 * \ingroup DataHandle
 * 
 * \brief Class def header for a class DataManager
 *
 * @author kazuhiro
 */

/** \addtogroup DataHandle

    @{*/
#ifndef DATAMANAGER_HH
#define DATAMANAGER_HH

#include <iostream>
#include <TFile.h>
#include <TChain.h>
#include "FMWKBase/Message.hh"
#include "EventRecord.hh"

namespace ubsens {
  namespace data {
    /**
       \class DataManager
       Data management class which holds ubsens::data::EventRecord instance and also
       takes care of file I/O.
    */
    class DataManager{

    public:

      enum IO_MODE_t {
	READ,
	WRITE,
	BOTH
      };

    public:
      
      /// Default constructor
      DataManager();
      
      /// Default destructor
      virtual ~DataManager();
      
      /// Getter for a read-only EventRecord instance
      const EventRecord& GetData() const { return *fData; }

      /// Getter for a write-permitted EventRecord instance
      EventRecord& GetWriteableData() { return *fData; }

      /// Verbosity setter
      void VerbosityLevel(::ubsens::fmwk::msg::VerbosityLevel_t level)
      { fVerbosity = level; }
      
      /// Verbosity getter
      ::ubsens::fmwk::msg::VerbosityLevel_t VerbosityLevel() const { return fVerbosity; }

      /// Read specific TTree entry
      bool GetEntry(size_t index);

      /// Move to the next entry in the input TTree;
      bool NextEntry();

      /// IO mode setter
      void SetIOMode(IO_MODE_t mode) { fIOMode = mode; }

      /// Add input file name
      void AddInputFilename(std::string const name) { fInFileName.push_back(name); }

      /// Set output file name
      void SetOutputFilename(std::string const name) { fOutFileName = name; }

      /// Read number of TTree entries
      size_t GetEntries();

      /// Write EventRecord to an output TTree
      void SaveEntry();

      /// Method to reset itself
      void Reset();

      /// Open input/output files
      void Open();

      /// Close input/output files
      void Close();

    private:

      /// Verbosity level
      ::ubsens::fmwk::msg::VerbosityLevel_t fVerbosity;

      /// Messenger instance
      ::ubsens::fmwk::Message fMsg;

      /// Event record
      EventRecord* fData;

      /// Input TTree
      TChain* fInTree;

      /// Output TTree
      TTree* fOutTree;

      /// Output file
      TFile* fOutFile;

      /// IO mode flag
      IO_MODE_t fIOMode;

      /// Input file name
      std::vector<std::string> fInFileName;

      /// Output file name
      std::string fOutFileName;

      /// Current TTree index
      size_t fTreeIndex;

      /// Input TTree entries
      size_t fInTreeEntries;

      /// Output TTree entries
      size_t fOutTreeEntries;

    };
  }
}

#endif
/** @} */ // end of doxygen group 


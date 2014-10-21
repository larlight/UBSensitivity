/**
 * \file EventRecord.hh
 *
 * \ingroup DataHandle
 * 
 * \brief Class to hold event data, which is a collection of all necessary information per event.
 *
 * @author davidkaleko
 */

/** \addtogroup DataHandle

    @{*/
#ifndef EVENTRECORD_HH
#define EVENTRECORD_HH

#include <iostream>
#include <TObject.h>
#include "TruthShower.hh"
#include "RecoShower.hh"
/**
   \class EventRecord
   This is an event data holder class which is a collection of all necessary information per event
 */
namespace ubsens {

  namespace data {

    class EventRecord : public TObject{
      
    public:
      
      /// constructor
      EventRecord();
      
      /// Default destructor
      virtual ~EventRecord(){};
      
      /// Method to clear event data contents
      void Reset();

      //
      // Setters
      //

      /// Adder for truth shower
      void AppendTruthShower(const TruthShower& s) { vTruthShower.push_back(s); }

      /// Adder for reco shower
      void AppendRecoShower(const RecoShower& s) { vRecoShower.push_back(s); }

      //
      // Getters
      //

      /// Access truth shower collection
      const std::vector<ubsens::data::TruthShower>& TruthShowerCollection() const { return vTruthShower; }

      /// Access reco shower collection
      const std::vector<ubsens::data::RecoShower>& RecoShowerCollection() const { return vRecoShower; }

    protected:

      /// Event ID 
      unsigned int fEventID;
      /// Run number
      unsigned int fRunNumber;
      /// Sub run number
      unsigned int fSubRunNumber;

      //
      // Event data collection
      //

      /// Truth shower collection
      std::vector< ::ubsens::data::TruthShower> vTruthShower;

      /// Reco-ed shower collection
      std::vector< ::ubsens::data::RecoShower> vRecoShower;

      ClassDef(EventRecord,1);

    };
    
  }//end namespace data
  
}//end namespace ubsens
#endif
/** @} */ // end of doxygen group 


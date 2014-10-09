#ifndef EVENTRECORD_CC
#define EVENTRECORD_CC

#include "EventRecord.hh"

namespace ubsens {
  namespace data {

    void EventRecord::Reset() 
    {
      // event unique id reset
      fEventID      = ::ubsens::fmwk::INVALID_UINT;
      fRunNumber    = ::ubsens::fmwk::INVALID_UINT;
      fSubRunNumber = ::ubsens::fmwk::INVALID_UINT;

      // data collection reset
      //kaleko: crashes happen here
      //      vTruthShower.clear();
      //      vRecoShower.clear();

    }

  }
}

#endif

#pragma once

namespace Lineside {
  //! Namespace for XML handling items
  namespace xml {
    //! Class to handle initialization of the Xerces library
    /*!
      Any classes which make use of Xerces should privately
      inherit from this class. It takes care of initializing
      the Xerces library.
     */
    class XercesGuard {
    public:
      XercesGuard();
      virtual ~XercesGuard();
    };
  }
}

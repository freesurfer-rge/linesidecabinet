#include <memory>
#include <mutex>

namespace Lineside {
  namespace PiGPIOd {
    //! Class to wrap the pigpiod library
    class LibraryManager {
    public:
      ~LibraryManager();
      
      static std::shared_ptr<LibraryManager> CreateLibraryManager();
    private:
      LibraryManager();

      int id;

      static bool initialised;
      static std::mutex mtx;
    };
  }
}

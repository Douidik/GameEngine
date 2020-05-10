#include "EnginePCH.h"

namespace Util {
    
    class VirtualFile {
      VirtualFile(const std::string& path) {
        mPath = std::filesystem::path(path);
      }

      const char* get()
      {
        return std::filesystem::absolute_path(mPath).c_str();
      }

      std::filesystem::path mPath;
    };

}

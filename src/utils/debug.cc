#include <cassert>
#include <sys/stat.h>
#include "utils/debug.hh"
#include "utils/gettext.hh"
#include "utils/portable.hh"

#include "config.h"
namespace utils
{
  Debug* Debug::instance_ = 0;

  Debug::Debug()
  {
    static const std::string filename = "trace.txt";
    if (!debug_file)
      return;

    struct stat st;
    if (!lstat(filename.c_str(), &st))
      if (!S_ISREG(st.st_mode))
        {
          ERROR() << "Not a regular file." << std::endl;
          return;
        }

    fp_.open(filename.c_str(), std::ios::out);
  }


  Debug::Debug(const Debug&)
  {
    assert(0);
  }

  Debug::~Debug()
  {
    if (!debug_file)
      return;
    fp_.close();
  }

  Debug&
  Debug::operator=(const Debug&)
  {
    assert(0);
    return *this;
  }
};

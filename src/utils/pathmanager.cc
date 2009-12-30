#include <cstdlib>
#include <sys/stat.h>
#include "config.h"
#include "utils/pathmanager.hh"

#include "utils/binreloc.h"
#include "utils/debug.hh"
#include "utils/gettext.hh"
#include "utils/portable.hh"

namespace utils
{
  PathManager* PathManager::instance_ = 0;

  PathManager::PathManager() :
    defaultBinaryDir_ (""),
    defaultDataDir_ (""),
    defaultVariableDir_ (""),
    binaryDir_ (""),
    dataDir_ (""),
    variableDir_ ("")
  {
    BrInitError error;

    if (br_init (&error) == 0 && error != BR_INIT_ERROR_DISABLED)
      {
        WARNING() << _("BinReloc failed to initialize (error code")
                  << error
                  << _(")")
                  << std::endl;
      }

    computePath();
  }

  PathManager::PathManager(const PathManager& pm) :
    binaryDir_ (pm.binaryDir_),
    dataDir_ (pm.dataDir_),
    variableDir_ (pm.variableDir_)
  {
  }

  PathManager::~PathManager()
  {
  }

  PathManager&
  PathManager::operator=(const PathManager&)
  {
    return *this;
  }

  const std::string&
  PathManager::getBinaryDir() const
  {
    return binaryDir_;
  }

  const std::string&
  PathManager::getDataDir() const
  {
    return dataDir_;
  }

  const std::string&
  PathManager::getVariableDir() const
  {
    return variableDir_;
  }

  // Caution: binReloc strings must be freed (and are malloc'ed).
  void
  PathManager::computePath()
  {
#ifdef DEFAULT_BINARY_DIR
    defaultBinaryDir_ = DEFAULT_BINARY_DIR;
#endif /* !DEFAULT_BINARY_DIR */

#ifdef DEFAULT_DATA_DIR
    defaultDataDir_ = DEFAULT_DATA_DIR;
#else
    defaultDataDir_ = "data";
#endif /* !DEFAULT_DATA_DIR */

#ifdef DEFAULT_VARIABLE_DIR
    defaultVariableDir_ = DEFAULT_VARIABLE_DIR;
#else
    defaultVariableDir_ = "data";
#endif /* !DEFAULT_VARIABLE_DIR */

    char* binarydir = br_find_bin_dir(defaultBinaryDir_.c_str());
    binaryDir_ = binarydir;
    free(binarydir);

    char* datadir = br_find_data_dir(defaultDataDir_.c_str());
    dataDir_ = datadir;
    free(datadir);

#ifdef WIN32
    char* variabledir = defaultVariableDir_.c_str();
    variableDir_ = variabledir;
#else
    variableDir_ = defaultVariableDir_;

    struct stat st;
    if (!lstat("/var/games/" PACKAGE, &st))
      {
        if (!S_ISDIR(st.st_mode))
          WARNING() << "Not a directory." << std::endl;
        else
          variableDir_ = "/var/games/twg-bomberman";
      }
#endif /* !WIN32 */
  }
}; // End of namespace utils

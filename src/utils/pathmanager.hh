#ifndef UTILS_PATHMANAGER_HH_
# define UTILS_PATHMANAGER_HH_
# include <string>

namespace utils
{
  class PathManager
  {
  public:
    static PathManager* get_instance()
    {
      if (!instance_)
        instance_ = new PathManager();
      return instance_;
    }

    static void kill()
    {
      if (instance_)
        delete instance_;
    }

    static std::string getBinaryFilename(const char* filename)
    {
      PathManager* pm = get_instance();

      std::string result(pm->getBinaryDir());
      result += filename;
      return result;
    }

    static std::string getDataFilename(const char* filename)
    {
      PathManager* pm = get_instance();

      std::string result(pm->getDataDir());
      result += filename;
      return result;
    }

    static std::string getVariableFilename(const char* filename)
    {
      PathManager* pm = get_instance();

      std::string result(pm->getVariableDir());
      result += filename;
      return result;
    }

    ~PathManager();

    const std::string& getBinaryDir() const;
    const std::string& getDataDir() const;
    const std::string& getVariableDir() const;

    void computePath();
  private:
    PathManager();
    PathManager(const PathManager&);

    PathManager& operator=(const PathManager&);

    static PathManager* instance_;

    std::string defaultBinaryDir_;
    std::string defaultDataDir_;
    std::string defaultVariableDir_;

    std::string binaryDir_;
    std::string dataDir_;
    std::string variableDir_;
  };

}; // End of namespace utils


#endif /* !UTILS_PATHMANAGER_HH_ */

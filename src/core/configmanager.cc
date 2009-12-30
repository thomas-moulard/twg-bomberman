/*!
 * \file  core/application.cc
 *
 * @brief Implémentation de \c core::ConfigManager.
 */
#include <cassert>
#include <fstream>
#include "core/configmanager.hh"
#include "utils/debug.hh"
#include "utils/gettext.hh"
#include "utils/pathmanager.hh"

namespace core
{
  ConfigManager* ConfigManager::instance_ = 0;

  ConfigManager::ConfigManager() :
    configurationFile_ (
                 utils::PathManager::getVariableFilename("/config.xml")),
    file_ ()
  {
  }

  void ConfigManager::loadConfigurationFile()
  {
    if (file_.LoadFile())
      return;

    if (!isReadable(configurationFile_))
      buildDefaultConfigurationFile();

    file_ = TiXmlDocument(configurationFile_.c_str());

    if (!file_.LoadFile())
      {
        ERROR() << _("Failed to load the configuratin file.")
                << std::endl;
        return;
      }

    TiXmlElement* root = file_.FirstChildElement();
    if (!root->Value() || std::string(root->Value())
        != std::string("configuration"))
      {
        ERROR () <<
          _("Error while loading the configuration file. Root element: ")
                 << root->Value()
                 << std::endl;
      }

    if (!root->Attribute("version") ||
        std::string(root->Attribute("version")) != std::string("1.0"))
      {
        ERROR() << _("Invalid version of the configuration file")
                << " ``"
                << root->Attribute("version")
                << "''."
                << std::endl;
      }
  }

  const char* ConfigManager::queryConfigurationFile(const char* ns,
                                                    const char* cl,
                                                    const char* attr)
  {
    loadConfigurationFile();
    TiXmlHandle docHandle(&file_);
    TiXmlElement* child =
      docHandle.FirstChild("configuration").FirstChild(ns).FirstChild(cl).FirstChild("attribute").Element();

    while (!!child)
      {
        if (std::string(child->Value()) == std::string("attribute")
            && child->Attribute("name")
            && std::string(child->Attribute("name")) == std::string(attr))
          return child->Attribute("value");
        child = child->NextSiblingElement();
      }

    W() << _("The query")
        << " ``" << ns << "/" << cl << "/" << attr << "'' "
        << _("has failed.")
        << std::endl;
    return 0;
  }

  int ConfigManager::getIntFromConfigurationFile(const char* ns,
                                                 const char* cl,
                                                 const char* attr)
  {
    const char* val = this->queryConfigurationFile(ns, cl, attr);
    int res = 0;
    std::istringstream i(val);
    i >> res;
    return res;
  }

  std::string ConfigManager::buildArray(const char* arrayName,
                                        const char* key) const
  {
    std::stringstream res;
    res << arrayName << "[" << key << "]";
    return res.str();
  }

  std::string ConfigManager::buildArray(const char* arrayName, int key) const
  {
    std::stringstream res;
    res << arrayName << "[" << key << "]";
    return res.str();
  }

  ConfigManager::ConfigManager(const ConfigManager&)
  {
    assert(0);
  }

  ConfigManager::~ConfigManager()
  {
  }

  ConfigManager&
  ConfigManager::operator=(const ConfigManager&)
  {
    assert(0);
    return *this;
  }

  bool
  ConfigManager::isReadable(const std::string& s) const
  {
    std::ifstream f(s.c_str(), std::ios_base::in);
    return f.good();
  }

  void
  ConfigManager::buildDefaultConfigurationFile() const
  {
    std::ofstream f(configurationFile_.c_str(), std::ios_base::trunc);
    if (!f.good())
      {
        ERROR() << _("Can not write the default configuration file.")
                << std::endl;
        return;
      }
    f << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n\
\n\
<configuration version=\"1.0\">\n\
   <core>\n\
      <Application>\n\
         <attribute name=\"skipIntro_\" value=\"true\"              />\n\
      </Application>\n\
\n\
      <InputManager>\n\
         <attribute name=\"playerKeys_[0][0]\" value=\"SDLK_UP\"    />\n\
         <attribute name=\"playerKeys_[0][1]\" value=\"SDLK_DOWN\"  />\n\
         <attribute name=\"playerKeys_[0][2]\" value=\"SDLK_LEFT\"  />\n\
         <attribute name=\"playerKeys_[0][3]\" value=\"SDLK_RIGHT\" />\n\
         <attribute name=\"playerKeys_[0][4]\" value=\"SDLK_SPACE\" />\n\
\n\
         <attribute name=\"playerKeys_[1][0]\" value=\"SDLK_z\"     />\n\
         <attribute name=\"playerKeys_[1][1]\" value=\"SDLK_s\"     />\n\
         <attribute name=\"playerKeys_[1][2]\" value=\"SDLK_q\"     />\n\
         <attribute name=\"playerKeys_[1][3]\" value=\"SDLK_d\"     />\n\
         <attribute name=\"playerKeys_[1][4]\" value=\"SDLK_f\"     />\n\
\n\
         <attribute name=\"playerKeys_[2][0]\" value=\"SDLK_KP8\"   />\n\
         <attribute name=\"playerKeys_[2][1]\" value=\"SDLK_KP5\"   />\n\
         <attribute name=\"playerKeys_[2][2]\" value=\"SDLK_KP4\"   />\n\
         <attribute name=\"playerKeys_[2][3]\" value=\"SDLK_KP6\"   />\n\
         <attribute name=\"playerKeys_[2][4]\" value=\"SDLK_KP0\"   />\n\
\n\
         <attribute name=\"playerKeys_[3][0]\" value=\"SDLK_u\"     />\n\
         <attribute name=\"playerKeys_[3][1]\" value=\"SDLK_j\"     />\n\
         <attribute name=\"playerKeys_[3][2]\" value=\"SDLK_h\"     />\n\
         <attribute name=\"playerKeys_[3][3]\" value=\"SDLK_k\"     />\n\
         <attribute name=\"playerKeys_[3][4]\" value=\"SDLK_l\"     />\n\
      </InputManager>\n\
   </core>\n\
\n\
   <game>\n\
      <BattleScene>\n\
         <attribute name=\"skipCount_\" value=\"true\"              />\n\
\n\
         <!-- 120000 ms = 2 min //-->\n\
         <attribute name=\"defaultBattleLength\" value=\"120000\"   />\n\
\n\
         <!-- 60000 ms = 1 min //-->\n\
         <attribute name=\"outOfTimeDelay\" value=\"60000\"         />\n\
      </BattleScene>\n\
\n\
      <BattleOptionsScene>\n\
         <attribute name=\"skip_\" value=\"false\"   />\n\
      </BattleOptionsScene>\n\
\n\
      <EndOfBattleScene>\n\
         <attribute name=\"skip_\" value=\"true\"    />\n\
      </EndOfBattleScene>\n\
\n\
      <Player>\n\
         <attribute name=\"name[0]\" value=\"Kat 1\"  />\n\
         <attribute name=\"name[1]\" value=\"Kat 2\"  />\n\
         <attribute name=\"name[2]\" value=\"Kat 3\"  />\n\
         <attribute name=\"name[3]\" value=\"Kat 4\"  />\n\
\n\
         <attribute name=\"sprite_offset_x\" value=\"7\"    />\n\
         <attribute name=\"sprite_offset_w\" value=\"20\"   />\n\
         <attribute name=\"sprite_offset_y\" value=\"18\"   />\n\
         <attribute name=\"sprite_offset_h\" value=\"14\"   />\n\
      </Player>\n\
   </game>\n\
\n\
   <graphic>\n\
      <GraphicManager>\n\
         <attribute name=\"showdebug\" value=\"true\" />\n\
      </GraphicManager>\n\
   </graphic>\n\
\n\
   <sound>\n\
   </sound>\n\
\n\
   <utils>\n\
   </utils>\n\
</configuration>\n\
";
    f.close();
    NOTICE() <<
      _("A default configuration file has been generated with success.")
             << std::endl;
  }
};

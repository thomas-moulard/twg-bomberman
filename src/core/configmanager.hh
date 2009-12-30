/*!
 * \file  core/configmanager.hh
 *
 * @brief Déclaration de \c core::ConfigManager.
 */

 /*!
 *  \class   ConfigManager
 *
 *  @brief   Le \c ConfigManager est chargé de gérer toute la
 *           configuration du jeu (nombre de joueurs, nom par défaut...)
 *  @author  Thomas Moulard <thomas.moulard@gmail.com>
 *  @author  Aurélien Vallée <vallee.aurelien@gmail.com>
 *  @version 1.0
 *  @date    07-24-2006
 *  @bug     none
 *  @warning none
 */

#ifndef CORE_CONFIGMANAGER_HH_
# define CORE_CONFIGMANAGER_HH_
# include <cstdio>
# include <string>
# include <sstream>

# include <tinyxml.h>

# include "game/battlescene.hh"


namespace core
{
  class ConfigManager
  {
  public:
    static ConfigManager* get_instance()
    {
      if (!instance_)
                instance_ = new ConfigManager();
      return instance_;
    }

    static void kill()
    {
      if (instance_)
      delete instance_;
    }

    /*!
     *  \fn         ConfigManager()
     *
     *  @brief      Constructeur par défaut de la classe.
     */
    ConfigManager();

    /*!
     *  \fn         ConfigManager(const ConfigManager&)
     *
     *  @brief      Constructeur par copie de la classe.
     */
    ConfigManager(const ConfigManager&);

    /*!
     *  \fn         ~ConfigManager()
     *
     *  @brief      Destructeur par défaut de la classe.
     */
    ~ConfigManager();

    /*!
     *  \fn         ConfigManager& operator=(const ConfigManager&)
     *
     *  @brief      Surcharge de l'opérateur = (assignation).
     *              Cet opérateur est équivalent au constructeur
     *              par copie de la classe.
     */
    ConfigManager& operator=(const ConfigManager&);

    /*!
     *  \fn         void loadConfigurationFile()
     *
     *  @brief      Cette fonction est appelée lors du chargement de
     *              l'application, elle lit le fichier de configuration du
     *              jeu.
     */
    void loadConfigurationFile();

    /*!
     *  \fn         void writeConfiguration()
     *
     *  @brief      Cette fonction est appelée lors de la sortie de
     *              l'application, elle enregistre la configuration du
     *              jeu.
     */
    void writeConfigurationFile();

    const char* queryConfigurationFile(const char* ns, const char* cl, const char* attr);

    int getIntFromConfigurationFile(const char* ns, const char* cl, const char* attr);

    std::string buildArray(const char*, const char*) const;
    std::string buildArray(const char*, int) const;

    bool isReadable(const std::string& s) const;
    void buildDefaultConfigurationFile() const;
  private:
    static ConfigManager* instance_;

    const std::string configurationFile_;
    TiXmlDocument file_;
  };
};

#endif /* !CORE_CONFIGMANAGER_HH_ */
